/****************************************************************************
 * sched/module/mod_procfs.c
 *
 *   Copyright (C) 2015 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <sys/stat.h>

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <errno.h>
#include <debug.h>

#include <nuttx/kmalloc.h>
#include <nuttx/module.h>
#include <nuttx/fs/fs.h>
#include <nuttx/fs/procfs.h>

#include "module.h"

#if !defined(CONFIG_DISABLE_MOUNTPOINT) && defined(CONFIG_FS_PROCFS) && \
    !defined(CONFIG_FS_PROCFS_EXCLUDE_MODULE)

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Determines the size of an intermediate buffer that must be large enough
 * to handle the longest line generated by this logic.
 */

#define MOD_LINELEN 64

/****************************************************************************
 * Private Types
 ****************************************************************************/

/* This structure describes one open "file" */

struct modprocfs_file_s
{
  struct procfs_file_s base;         /* Base open file structure */

  /* Read helpers */

  FAR char *buffer;                  /* User buffer pointer */
  size_t buflen;                     /* Size of the user buffer */
  size_t remaining;                  /* Space remaining in user buffer */
  size_t totalsize;                  /* Total size returned by read() */
  off_t offset;                      /* Offset skip on output */
  char line[MOD_LINELEN];            /* Buffer for line formatting */
};

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/* File system methods */

static int     modprocfs_open(FAR struct file *filep, FAR const char *relpath,
                 int oflags, mode_t mode);
static int     modprocfs_close(FAR struct file *filep);
static ssize_t modprocfs_read(FAR struct file *filep, FAR char *buffer,
                 size_t buflen);
static int     modprocfs_dup(FAR const struct file *oldp,
                 FAR struct file *newp);
static int     modprocfs_stat(FAR const char *relpath, FAR struct stat *buf);

/****************************************************************************
 * Public Data
 ****************************************************************************/

/* See include/nutts/fs/procfs.h
 * We use the old-fashioned kind of initializers so that this will compile
 * with any compiler.
 */

const struct procfs_operations module_operations =
{
  modprocfs_open,       /* open */
  modprocfs_close,      /* close */
  modprocfs_read,       /* read */
  NULL,                 /* write */
  modprocfs_dup,        /* dup */

  NULL,                 /* opendir */
  NULL,                 /* closedir */
  NULL,                 /* readdir */
  NULL,                 /* rewinddir */

  modprocfs_stat        /* stat */
};

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: modprocfs_callback
 ****************************************************************************/

static int modprocfs_callback(FAR struct module_s *modp, FAR void *arg)
{
  FAR struct modprocfs_file_s *priv;
  size_t linesize;
  size_t copysize;

  DEBUGASSERT(modp != NULL && arg != NULL);
  priv = (FAR struct modprocfs_file_s *)arg;

  linesize = snprintf(priv->line, MOD_LINELEN, "%s,%p,%p,%p,%p,%lu,%p,%lu\n",
                      modp->modulename, modp->initializer,
                      modp->uninitializer, modp->arg,
                      modp->alloc, (unsigned long)modp->textsize,
                      (FAR uint8_t *)modp->alloc + modp->textsize,
                      (unsigned long)modp->datasize);
  copysize = procfs_memcpy(priv->line, linesize, priv->buffer,
                           priv->remaining, &priv->offset);
  priv->totalsize += copysize;
  priv->buffer    += copysize;
  priv->remaining -= copysize;

  return (priv->totalsize >= priv->buflen) ? 1 : 0;
}

/****************************************************************************
 * Name: modprocfs_open
 ****************************************************************************/

static int modprocfs_open(FAR struct file *filep, FAR const char *relpath,
                          int oflags, mode_t mode)
{
  FAR struct modprocfs_file_s *priv;

  finfo("Open '%s'\n", relpath);

  /* PROCFS is read-only.  Any attempt to open with any kind of write
   * access is not permitted.
   *
   * REVISIT:  Write-able proc files could be quite useful.
   */

  if (((oflags & O_WRONLY) != 0 || (oflags & O_RDONLY) == 0))
    {
      fdbg("ERROR: Only O_RDONLY supported\n");
      return -EACCES;
    }

  /* Allocate the open file structure */

  priv = (FAR struct modprocfs_file_s *)kmm_zalloc(sizeof(struct modprocfs_file_s));
  if (!priv)
    {
      fdbg("ERROR: Failed to allocate file attributes\n");
      return -ENOMEM;
    }

  /* Save the open file structure as the open-specific state in
   * filep->f_priv.
   */

  filep->f_priv = (FAR void *)priv;
  return OK;
}

/****************************************************************************
 * Name: modprocfs_close
 ****************************************************************************/

static int modprocfs_close(FAR struct file *filep)
{
  FAR struct modprocfs_file_s *priv;

  /* Recover our private data from the struct file instance */

  priv = (FAR struct modprocfs_file_s *)filep->f_priv;
  DEBUGASSERT(priv);

  /* Release the file attributes structure */

  kmm_free(priv);
  filep->f_priv = NULL;
  return OK;
}

/****************************************************************************
 * Name: modprocfs_read
 ****************************************************************************/

static ssize_t modprocfs_read(FAR struct file *filep, FAR char *buffer,
                              size_t buflen)
{
  FAR struct modprocfs_file_s *priv;
  int ret;

  finfo("buffer=%p buflen=%lu\n", buffer, (unsigned long)buflen);

  /* Recover our private data from the struct file instance */

  priv = (FAR struct modprocfs_file_s *)filep->f_priv;
  DEBUGASSERT(priv);

  /* Traverse all installed modules */

  priv->remaining = buflen;
  priv->totalsize = 0;
  priv->buffer    = buffer;
  priv->buflen    = buflen;
  priv->offset    = filep->f_pos;

  ret = mod_registry_foreach(modprocfs_callback, priv);
  if (ret >= 0)
    {
      filep->f_pos += priv->totalsize;
      return priv->totalsize;
    }

  return ret;
}

/****************************************************************************
 * Name: modprocfs_dup
 *
 * Description:
 *   Duplicate open file data in the new file structure.
 *
 ****************************************************************************/

static int modprocfs_dup(FAR const struct file *oldp, FAR struct file *newp)
{
  FAR struct modprocfs_file_s *oldpriv;
  FAR struct modprocfs_file_s *newpriv;

  finfo("Dup %p->%p\n", oldp, newp);

  /* Recover our private data from the old struct file instance */

  oldpriv = (FAR struct modprocfs_file_s *)oldp->f_priv;
  DEBUGASSERT(oldpriv);

  /* Allocate a new container to hold the task and attribute selection */

  newpriv = (FAR struct modprocfs_file_s *)kmm_zalloc(sizeof(struct modprocfs_file_s));
  if (!newpriv)
    {
      fdbg("ERROR: Failed to allocate file attributes\n");
      return -ENOMEM;
    }

  /* The copy the file attribtes from the old attributes to the new */

  memcpy(newpriv, oldpriv, sizeof(struct modprocfs_file_s));

  /* Save the new attributes in the new file structure */

  newp->f_priv = (FAR void *)newpriv;
  return OK;
}

/****************************************************************************
 * Name: modprocfs_stat
 *
 * Description: Return information about a file or directory
 *
 ****************************************************************************/

static int modprocfs_stat(FAR const char *relpath, FAR struct stat *buf)
{
  memset(buf, 0, sizeof(struct stat));
  buf->st_mode    = S_IFREG | S_IROTH | S_IRGRP | S_IRUSR;
  return OK;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

#endif /* !CONFIG_DISABLE_MOUNTPOINT && CONFIG_FS_PROCFS &&
        * !CONFIG_FS_PROCFS_EXCLUDE_MODULE */
