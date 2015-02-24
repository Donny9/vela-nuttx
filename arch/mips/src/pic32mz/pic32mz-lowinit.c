/****************************************************************************
 * arch/mips/src/pic32/pic32mz-lowinit.c
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

#include <assert.h>

#include <arch/pic32mz/cp0.h>
#include <arch/board/board.h>

#include "up_internal.h"
#include "up_arch.h"

#include "chip/pic32mz-prefetch.h"

#include "pic32mz-lowconsole.h"
#include "pic32mz-lowinit.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/
/* Maximum Frequencies ******************************************************/

#define MAX_FLASH_ECC_HZ   66000000 /* Maximum FLASH speed (Hz) with ECC */
#define MAX_FLASH_NOECC_HZ 83000000 /* Maximum FLASH speed (Hz) without ECC */
#define MAX_PBCLOCK        80000000 /* Max peripheral bus speed (Hz) */

/* Sanity checks ************************************************************/

/* Make sure that the selected clock parameters are sane */

#define CALC_SYSCLOCK  (((BOARD_PLL_INPUT / BOARD_PLL_IDIV) * BOARD_PLL_MULT) / BOARD_PLL_ODIV)
#if CALC_SYSCLOCK != BOARD_CPU_CLOCK
#  error "Bad BOARD_CPU_CLOCK calculcation in board.h"
#endif

#define CALC_PBCLOCK  (CALC_SYSCLOCK / BOARD_PBDIV)
#if CALC_PBCLOCK != BOARD_PBCLOCK
#  error "Bad BOARD_PBCLOCK calculcation in board.h"
#endif

#if CALC_PBCLOCK > MAX_PBCLOCK
#  error "PBCLOCK exceeds maximum value"
#endif

/****************************************************************************
 * Private Types
 ****************************************************************************/

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Global Variables
 ****************************************************************************/

/****************************************************************************
 * Private Variables
 ****************************************************************************/

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: pic32mz_prefetch
 *
 * Description:
 *   Configure the prefetch module setting:
 *
 *   1. The optimal number of FLASH wait states.
 *   2. Enable prefetch on CPU instructions and data
 *
 * Assumptions:
 *   Interrupts are disabled.
 *
 ****************************************************************************/

static inline void pic32mz_prefetch(void)
{
  unsigned int nwaits;
  unsigned int residual;
  uint32_t regval;
  

  /* Configure pre-fetch cache FLASH wait states (assuming ECC is enabled) */

  residual = BOARD_CPU_CLOCK;
  nwaits   = 0;

  while (residual > MAX_FLASH_ECC_HZ)
    {
      nwaits++;
      residual -= MAX_FLASH_ECC_HZ;
    }

  DEBUGASSERT(nwaits < 8);

  /* Set the FLASH wait states and enabled prefetch on CPU instructions and
   * data.
   */

  regval = (PREFETCH_PRECON_PREFEN_CPUID | PREFETCH_PRECON_PFMWS(nwaits));
  putreg32(regval, PIC32MZ_PREFETCH_PRECON);
}

/****************************************************************************
 * Name: pic32mz_k0cache
 *
 * Description:
 *   Enable caching in KSEG0.
 *
 * Assumptions:
 *   Interrupts are disabled.
 *
 ****************************************************************************/

static inline void pic32mz_k0cache(void)
{
  register uint32_t regval;

  /* Enable cache on KSEG 0 in the CP0 CONFIG register*/

  asm("\tmfc0 %0,$16,0\n" :  "=r"(regval));
  regval &= ~CP0_CONFIG_K23_MASK;
  regval |= CP0_CONFIG_K23_CACHEABLE;
  asm("\tmtc0 %0,$16,0\n" : : "r" (regval));

  UNUSED(regval);
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: pic32mz_lowinit
 *
 * Description:
 *   This performs basic low-level initialization of the system.
 *
 * Assumptions:
 *   Interrupts have not yet been enabled.
 *
 ****************************************************************************/

void pic32mz_lowinit(void)
{
  /* Initialize FLASH wait states */

  pic32mz_prefetch();

  /* Enable caching in KSEG0 */

  pic32mz_k0cache();;

  /* Initialize a console (probably a serial console) */

  pic32mz_consoleinit();

  /* Perform early serial initialization (so that we will have debug output
   * available as soon as possible).
   */

#ifdef USE_EARLYSERIALINIT
  up_earlyserialinit();
#endif

  /* Perform board-level initialization */

  pic32mz_boardinitialize();
}
