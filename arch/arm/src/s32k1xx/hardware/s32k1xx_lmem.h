/************************************************************************************
 * arch/arm/src/s32k1xx/hardware/s32k1xx_lmem.h
 *
 *   Copyright (C) 2019 Gregory Nutt. All rights reserved.
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
 ************************************************************************************/

#ifndef __ARCH_ARM_SRC_S32K1XX_HARDWARE_S32K1XX_LMEM_H
#define __ARCH_ARM_SRC_S32K1XX_HARDWARE_S32K1XX_LMEM_H

/************************************************************************************
 * Included Files
 ************************************************************************************/

#include <nuttx/config.h>
#include <hardware/s32k1xx_memorymap.h>

#ifdef CONFIG_S32K1XX_HAVE_LMEM

/************************************************************************************
 * Pre-processor Definitions
 ************************************************************************************/

/* LMEM Register Offsets ************************************************************/

#define S32K1XX_LMEM_PCCCR_OFFSET   0x0000  /* Cache control register */
#define S32K1XX_LMEM_PCCLCR_OFFSET  0x0004  /* Cache line control register */
#define S32K1XX_LMEM_PCCSAR_OFFSET  0x0008  /* Cache search address register */
#define S32K1XX_LMEM_PCCCVR_OFFSET  0x000c  /* Cache read/write value register */
#define S32K1XX_LMEM_PCCRMR_OFFSET  0x0020  /* Cache regions mode register */

/* LMEM Register Addresses **********************************************************/

#define S32K1XX_LMEM_PCCCR          (S32K1XX_LMEM_BASE + S32K1XX_LMEM_PCCCR_OFFSET)
#define S32K1XX_LMEM_PCCLCR         (S32K1XX_LMEM_BASE + S32K1XX_LMEM_PCCLCR_OFFSET)
#define S32K1XX_LMEM_PCCSAR         (S32K1XX_LMEM_BASE + S32K1XX_LMEM_PCCSAR_OFFSET)
#define S32K1XX_LMEM_PCCCVR         (S32K1XX_LMEM_BASE + S32K1XX_LMEM_PCCCVR_OFFSET)
#define S32K1XX_LMEM_PCCRMR         (S32K1XX_LMEM_BASE + S32K1XX_LMEM_PCCRMR_OFFSET)

/* LMEM Register Bitfield Definitions ***********************************************/

/* Cache control register */

#define LMEM_PCCCR_ENCACHE          (1 << 0)  /* Bit 0:  Cache enable */
#define LMEM_PCCCR_PCCR2            (1 << 2)  /* Bit 2:  Forces all to write through */
#define LMEM_PCCCR_PCCR3            (1 << 3)  /* Bit 3:  No allocation on cache misses */
#define LMEM_PCCCR_INVW0            (1 << 24) /* Bit 24: Invalidate Way 0 */
#define LMEM_PCCCR_PUSHW0           (1 << 25) /* Bit 25: Push Way 0 */
#define LMEM_PCCCR_INVW1            (1 << 26) /* Bit 26: Invalidate Way 1 */
#define LMEM_PCCCR_PUSHW1           (1 << 27) /* Bit 27: Push Way 1 */
#define LMEM_PCCCR_GO               (1 << 31) /* Bit 31: Initiate Cache Command */

/* Cache line control register */

#define LMEM_PCCLCR_LGO             (1 << 0)  /* Bit 0:  Initiate Cache Line Command */
#define LMEM_PCCLCR_CACHEADDR_SHIFT (2)       /* Bits 2-13: Cache address */
#define LMEM_PCCLCR_CACHEADDR_MASK  (0x7ff << LMEM_PCCLCR_CACHEADDR_SHIFT)
#  define LMEM_PCCLCR_CACHEADDR(n)  ((uint32_t)(n) << LMEM_PCCLCR_CACHEADDR_SHIFT)
#define LMEM_PCCLCR_WSEL            (1 << 14) /* Bit 14: Way select */
#  define LMEM_PCCLCR_WSEL_WAY0     (0)       /*         Way0 */
#  define LMEM_PCCLCR_WSEL_WAY1     (1 << 14) /*         Way1 */
#define LMEM_PCCLCR_TDSEL           (1 << 16) /* Bit 16: Tag/Data Select */
#  define LMEM_PCCLCR_TDSEL_DATA    (0)       /*         Data */
#  define LMEM_PCCLCR_TDSEL_TAG     (1 << 16) /*         Tag */
#define LMEM_PCCLCR_LCIVB           (1 << 20) /* Bit 20: Line Command Initial Valid Bit */
#define LMEM_PCCLCR_LCWAY           (1 << 22) /* Bit 22: Line Command Way */
#  define LMEM_PCCLCR_LCWAY_WAY0    (0)       /*         Way0 */
#  define LMEM_PCCLCR_LCWAY_WAY1    (1 << 22) /*         Way1 */
#define LMEM_PCCLCR_LCMD_SHIFT      (24)      /* Bits  24-25: Line Command */
#define LMEM_PCCLCR_LCMD_MASK       (3 << LMEM_PCCLCR_LCMD_SHIFT)
#  define LMEM_PCCLCR_LCMD_SEARCH   (0 << LMEM_PCCLCR_LCMD_SHIFT) /* Search and read or write */
#  define LMEM_PCCLCR_LCMD_INVLD    (1 << LMEM_PCCLCR_LCMD_SHIFT) /* Invalidate */
#  define LMEM_PCCLCR_LCMD_PUSH     (2 << LMEM_PCCLCR_LCMD_SHIFT) /* Push */
#  define LMEM_PCCLCR_LCMD_CLEAR    (3 << LMEM_PCCLCR_LCMD_SHIFT) /* Clear */
#define LMEM_PCCLCR_LADSEL          (1 << 26) /* Bit 26: Line Address Select */
#  define LMEM_PCCLCR_LADSEL_CACHE  (0)       /*         Cache address */
#  define LMEM_PCCLCR_LADSEL_PHYS   (1 << 26) /*         Physical address */
#define LMEM_PCCLCR_LACC            (1 << 27) /* Bit 27: Line access type */
#  define LMEM_PCCLCR_LACC_READ     (0)       /*         Read */
#  define LMEM_PCCLCR_LACC_WRITE    (1 << 27) /*         Write */

/* Cache search address register */

#define LMEM_PCCSAR_LGO             (1 << 0)  /* Bit 0:  Initiate Cache Line Command */
#define LMEM_PCCSAR_PHYADDR_MASK    (0xfffffffc) /* Bits 2-31: Physical Address (Bits 2-31) */

/* Cache read/write value register (32-bit data) */

/* Cache regions mode register */

#define LMEM_REGION_NONCACHEABLE    0         /* 0, 1:  Non-cacheable */
#define LMEM_REGION_WRITE_THROUGH   2         /* 2: Write-through */
#define LMEM_REGION_WRITE_BACK      3         /* 3: Write-back */

#define LMEM_PCCRMR_REGION_SHIFT(n) ((15 - (n)) << 1)  /* Region n mode, n=0-15 */
#define LMEM_PCCRMR_REGION_MASK(n)  (3 << LMEM_PCCRMR_REGION_SHIFT(n))
#  define LMEM_PCCRMR_REGION(n,m)   ((uint32_t)(m) << LMEM_PCCRMR_REGION_SHIFT(n))

#endif /* CONFIG_S32K1XX_HAVE_LMEM */
#endif /* __ARCH_ARM_SRC_S32K1XX_HARDWARE_S32K1XX_LMEM_H */
