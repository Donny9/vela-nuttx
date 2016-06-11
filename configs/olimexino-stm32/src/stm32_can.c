/************************************************************************************
 * configs/olimexino-stm32/src/stm32_can.c
 *
 *   Copyright (C) 2015 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *           David Sidrane <david_s5@nscdg.com>
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

/************************************************************************************
 * Included Files
 ************************************************************************************/

#include <nuttx/config.h>

#include <errno.h>
#include <debug.h>

#include <nuttx/can.h>
#include <arch/board/board.h>

#include "chip.h"
#include "up_arch.h"

#include "olimexino-stm32.h"

#include "stm32.h"
#include "stm32_can.h"

#if defined(CONFIG_CAN) && (defined(CONFIG_STM32_CAN1) || defined(CONFIG_STM32_CAN2))

/************************************************************************************
 * Pre-processor Definitions
 ************************************************************************************/
/* Configuration ********************************************************************/
/* The STM32F107VC supports CAN1 and CAN2 */

#define CAN_PORT 1

/* Debug ***************************************************************************/
/* Non-standard debug that may be enabled just for testing CAN */

#ifdef CONFIG_DEBUG_CAN
#  define candbg    dbg
#  define caninfo   info
#  define canlldbg  lldbg
#  define canllinfo llinfo
#else
#  define candbg(x...)
#  define caninfo(x...)
#  define canlldbg(x...)
#  define canllinfo(x...)
#endif

/************************************************************************************
 * Private Functions
 ************************************************************************************/

/************************************************************************************
 * Public Functions
 ************************************************************************************/

/************************************************************************************
 * Name: board_can_initialize
 *
 * Description:
 *   All STM32 architectures must provide the following interface to work with
 *   examples/can.
 *
 ************************************************************************************/

int board_can_initialize(void)
{
  static bool initialized = false;
  struct can_dev_s *can;
  int ret;

  /* Check if we have already initialized */

  if (!initialized)
    {
      /* Call stm32_caninitialize() to get an instance of the CAN interface */

      can = stm32_caninitialize(CAN_PORT);
      if (can == NULL)
        {
          candbg("ERROR:  Failed to get CAN interface\n");
          return -ENODEV;
        }

      /* Register the CAN driver at "/dev/can0" */

      ret = can_register("/dev/can0", can);
      if (ret < 0)
        {
          candbg("ERROR: can_register failed: %d\n", ret);
          return ret;
        }

      /* Now we are initialized */

      initialized = true;
    }

  return OK;
}

#endif /* CONFIG_CAN && CONFIG_STM32_CAN1 */
