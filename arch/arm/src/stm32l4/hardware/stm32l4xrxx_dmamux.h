/****************************************************************************
 * arch/arm/src/stm32l4/hardware/stm32l4xrxx_dmamux.h
 *
 *   Copyright (C) 2019 Gregory Nutt. All rights reserved.
 *   Author: Jussi Kivilinna <jussi.kivilinna@haltian.com>
 *
 * Based on STM32H7 DMAMUX:
 *   Author: Mateusz Szafoni <raiden00@railab.me>
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

#ifndef __ARCH_ARM_SRC_STM32L4_HARDWARE_STM32L4XRXX_DMAMUX_H
#define __ARCH_ARM_SRC_STM32L4_HARDWARE_STM32L4XRXX_DMAMUX_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include "chip.h"
#include "stm32l4xrxx_dma.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define DMAMUX1 0

/* Register Offsets *********************************************************/

#define STM32L4_DMAMUX_CXCR_OFFSET(x)  (0x0000+0x0004*(x)) /* DMAMUX1 request line multiplexer channel x configuration register */
#define STM32L4_DMAMUX_C0CR_OFFSET     STM32L4_DMAMUX_CXCR_OFFSET(0)
#define STM32L4_DMAMUX_C1CR_OFFSET     STM32L4_DMAMUX_CXCR_OFFSET(1)
#define STM32L4_DMAMUX_C2CR_OFFSET     STM32L4_DMAMUX_CXCR_OFFSET(2)
#define STM32L4_DMAMUX_C3CR_OFFSET     STM32L4_DMAMUX_CXCR_OFFSET(3)
#define STM32L4_DMAMUX_C4CR_OFFSET     STM32L4_DMAMUX_CXCR_OFFSET(4)
#define STM32L4_DMAMUX_C5CR_OFFSET     STM32L4_DMAMUX_CXCR_OFFSET(5)
#define STM32L4_DMAMUX_C6CR_OFFSET     STM32L4_DMAMUX_CXCR_OFFSET(6)
#define STM32L4_DMAMUX_C7CR_OFFSET     STM32L4_DMAMUX_CXCR_OFFSET(7)
#define STM32L4_DMAMUX_C8CR_OFFSET     STM32L4_DMAMUX_CXCR_OFFSET(8)
#define STM32L4_DMAMUX_C9CR_OFFSET     STM32L4_DMAMUX_CXCR_OFFSET(9)
#define STM32L4_DMAMUX_C10CR_OFFSET    STM32L4_DMAMUX_CXCR_OFFSET(10)
#define STM32L4_DMAMUX_C11CR_OFFSET    STM32L4_DMAMUX_CXCR_OFFSET(11)
#define STM32L4_DMAMUX_C12CR_OFFSET    STM32L4_DMAMUX_CXCR_OFFSET(12)
#define STM32L4_DMAMUX_C13CR_OFFSET    STM32L4_DMAMUX_CXCR_OFFSET(13)
                                              /* 0x034-0x07C: Reserved */
#define STM32L4_DMAMUX_CSR_OFFSET      0x0080 /* DMAMUX1 request line multiplexer interrupt channel status register */
#define STM32L4_DMAMUX_CFR_OFFSET      0x0084 /* DMAMUX1 request line multiplexer interrupt clear flag register */
                                              /* 0x088-0x0FC: Reserved */

#define STM32L4_DMAMUX_RGXCR_OFFSET(x) (0x0100+0x004*(x)) /* DMAMUX1 request generator channel x configuration register */
#define STM32L4_DMAMUX_RG0CR_OFFSET    STM32L4_DMAMUX_RGXCR_OFFSET(0)
#define STM32L4_DMAMUX_RG1CR_OFFSET    STM32L4_DMAMUX_RGXCR_OFFSET(1)
#define STM32L4_DMAMUX_RG2CR_OFFSET    STM32L4_DMAMUX_RGXCR_OFFSET(2)
#define STM32L4_DMAMUX_RG3CR_OFFSET    STM32L4_DMAMUX_RGXCR_OFFSET(3)
#define STM32L4_DMAMUX_RGSR_OFFSET     0x0140 /* DMAMUX1 request generator interrupt status register */
#define STM32L4_DMAMUX_RGCFR_OFFSET    0x0144 /* DMAMUX1 request generator interrupt clear flag register */
                                              /* 0x148-0x3FC: Reserved */

/* Register Addresses *******************************************************/

#define STM32L4_DMAMUX1_CXCR(x)  (STM32L4_DMAMUX1_BASE+STM32L4_DMAMUX_CXCR_OFFSET(x))
#define STM32L4_DMAMUX1_C0CR     (STM32L4_DMAMUX1_BASE+STM32L4_DMAMUX_C0CR_OFFSET)
#define STM32L4_DMAMUX1_C1CR     (STM32L4_DMAMUX1_BASE+STM32L4_DMAMUX_C1CR_OFFSET)
#define STM32L4_DMAMUX1_C2CR     (STM32L4_DMAMUX1_BASE+STM32L4_DMAMUX_C2CR_OFFSET)
#define STM32L4_DMAMUX1_C3CR     (STM32L4_DMAMUX1_BASE+STM32L4_DMAMUX_C3CR_OFFSET)
#define STM32L4_DMAMUX1_C4CR     (STM32L4_DMAMUX1_BASE+STM32L4_DMAMUX_C4CR_OFFSET)
#define STM32L4_DMAMUX1_C5CR     (STM32L4_DMAMUX1_BASE+STM32L4_DMAMUX_C5CR_OFFSET)
#define STM32L4_DMAMUX1_C6CR     (STM32L4_DMAMUX1_BASE+STM32L4_DMAMUX_C6CR_OFFSET)
#define STM32L4_DMAMUX1_C7CR     (STM32L4_DMAMUX1_BASE+STM32L4_DMAMUX_C7CR_OFFSET)
#define STM32L4_DMAMUX1_C8CR     (STM32L4_DMAMUX1_BASE+STM32L4_DMAMUX_C8CR_OFFSET)
#define STM32L4_DMAMUX1_C9CR     (STM32L4_DMAMUX1_BASE+STM32L4_DMAMUX_C9CR_OFFSET)
#define STM32L4_DMAMUX1_C10CR    (STM32L4_DMAMUX1_BASE+STM32L4_DMAMUX_C10CR_OFFSET)
#define STM32L4_DMAMUX1_C11CR    (STM32L4_DMAMUX1_BASE+STM32L4_DMAMUX_C11CR_OFFSET)
#define STM32L4_DMAMUX1_C12CR    (STM32L4_DMAMUX1_BASE+STM32L4_DMAMUX_C12CR_OFFSET)
#define STM32L4_DMAMUX1_C13CR    (STM32L4_DMAMUX1_BASE+STM32L4_DMAMUX_C12CR_OFFSET)

#define STM32L4_DMAMUX1_CSR      (STM32L4_DMAMUX1_BASE+STM32L4_DMAMUX_CSR_OFFSET)
#define STM32L4_DMAMUX1_CFR      (STM32L4_DMAMUX1_BASE+STM32L4_DMAMUX_CFR_OFFSET)

#define STM32L4_DMAMUX1_RGXCR(x) (STM32L4_DMAMUX1_BASE+STM32L4_DMAMUX_RGXCR_OFFSET(x))
#define STM32L4_DMAMUX1_RG0CR    (STM32L4_DMAMUX1_BASE+STM32L4_DMAMUX_RG0CR_OFFSET)
#define STM32L4_DMAMUX1_RG1CR    (STM32L4_DMAMUX1_BASE+STM32L4_DMAMUX_RG1CR_OFFSET)
#define STM32L4_DMAMUX1_RG2CR    (STM32L4_DMAMUX1_BASE+STM32L4_DMAMUX_RG2CR_OFFSET)
#define STM32L4_DMAMUX1_RG3CR    (STM32L4_DMAMUX1_BASE+STM32L4_DMAMUX_RG3CR_OFFSET)

#define STM32L4_DMAMUX1_RGSR     (STM32L4_DMAMUX1_BASE+STM32L4_DMAMUX_RGSR_OFFSET)
#define STM32L4_DMAMUX1_RGCFR    (STM32L4_DMAMUX1_BASE+STM32L4_DMAMUX_RGCFR_OFFSET)

/* Register Bitfield Definitions ********************************************/

/* DMAMUX1 request line multiplexer channel x configuration register */

#define DMAMUX_CCR_DMAREQID_SHIFT (0)  /* Bits 0-6: DMA request identification */
#define DMAMUX_CCR_DMAREQID_MASK  (0x7f << DMAMUX_CCR_DMAREQID_SHIFT)
#define DMAMUX_CCR_SOIE           (8)  /* Bit 8: Synchronization overrun interrupt enable */
#define DMAMUX_CCR_EGE            (9)  /* Bit 9: Event generation enable */
#define DMAMUX_CCR_SE             (16) /* Bit 16: Synchronization enable */
#define DMAMUX_CCR_SPOL_SHIFT     (17) /* Bits 17-18: Synchronization polarity */
#define DMAMUX_CCR_SPOL_MASK      (3 << DMAMUX_CCR_SPOL_SHIFT)
#define DMAMUX_CCR_NBREQ_SHIFT    (19) /* Bits 19-23: Number of DMA request - 1 to forward */
#define DMAMUX_CCR_NBREQ_MASK     (0x1f << DMAMUX_CCR_NBREQ_SHIFT)
#define DMAMUX_CCR_SYNCID_SHIFT   (24) /* Bits 24-28: Synchronization identification */
#define DMAMUX_CCR_SYNCID_MASK    (0x1f << DMAMUX_CCR_SYNCID_SHIFT)

/* DMAMUX1 request line multiplexer interrupt channel status register */

#define DMAMUX_CSR_SOF(x)         (1 << (x)) /* Synchronization overrun event flag */

/* DMAMUX1 request line multiplexer interrupt clear flag register */

#define DMAMUX_CFR_CSOF(x)        (1 << (x)) /* Clear synchronization overrun event flag */

/* DMAMUX1 request generator channel x configuration register */

#define DMAMUX_RGCR_SIGID_SHIFT   (0)  /* Bits 0-4: Signal identifiaction */
#define DMAMUX_RGCR_SIGID_MASK    (0x1f << DMAMUX_RGCR_SIGID_SHIFT)
#define DMAMUX_RGCR_OIE           (8)  /* Bit 8: Trigger overrun interrupt enable */
#define DMAMUX_RGCR_GE            (16) /* Bit 16: DMA request generator channel X enable*/
#define DMAMUX_RGCR_GPOL_SHIFT    (17) /* Bits 17-18: DMA request generator trigger polarity */
#define DMAMUX_RGCR_GPOL_MASK     (7 << DMAMUX_RGCR_GPOL_SHIFT)
#define DMAMUX_RGCR_GNBREQ_SHIFT  (17) /* Bits 19-23: Number of DMA requests to be generated -1 */
#define DMAMUX_RGCR_GNBREQL_MASK  (7 << DMAMUX_RGCR_GNBREQ_SHIFT)

/* DMAMUX1 request generator interrupt status register */

#define DMAMUX_RGSR_OF(x)         (1 << (x)) /* Trigger overrun event flag */

/* DMAMUX1 request generator interrupt clear flag register */

#define DMAMUX_RGCFR_COF(x)       (1 << (x)) /* Clear trigger overrun event flag */

/* DMA channel mapping
 *
 * D.CCCCCCC
 * C - DMAMUX1 request
 * D - DMA controller (DMA1, DMA2)
 */

#define DMAMAP_MAP(d,c)           ((((d) & 0x01) << 7) | ((c) & 0x7f))
#define DMAMAP_CONTROLLER(m)      (((m) >> 7) & 0x01)
#define DMAMAP_REQUEST(m)         (((m) >> 0) & 0x7f)

/* DMAMUX1 mapping **********************************************************/

/* NOTE: DMAMUX1 channels 0 to 6 are connected to DMA1 channels 1 to 7.
 *       DMAMUX1 channels 7 to 13 are connected to DMA2 channels 1 to 7.
 */

#define DMAMUX1_REQ_GEN0       (1)
#define DMAMUX1_REQ_GEN1       (2)
#define DMAMUX1_REQ_GEN2       (3)
#define DMAMUX1_REQ_GEN3       (4)
#define DMAMUX1_ADC1           (5)
#define DMAMUX1_DAC1           (6)
#define DMAMUX1_DAC2           (7)
#define DMAMUX1_TIM6_UP        (8)
#define DMAMUX1_TIM7_UP        (9)
#define DMAMUX1_SPI1_RX        (10)
#define DMAMUX1_SPI1_TX        (11)
#define DMAMUX1_SPI2_RX        (12)
#define DMAMUX1_SPI2_TX        (13)
#define DMAMUX1_SPI3_RX        (14)
#define DMAMUX1_SPI3_TX        (15)
#define DMAMUX1_I2C1_RX        (16)
#define DMAMUX1_I2C1_TX        (17)
#define DMAMUX1_I2C2_RX        (18)
#define DMAMUX1_I2C2_TX        (19)
#define DMAMUX1_I2C3_RX        (20)
#define DMAMUX1_I2C3_TX        (21)
#define DMAMUX1_I2C4_RX        (22)
#define DMAMUX1_I2C4_TX        (23)
#define DMAMUX1_USART1_RX      (24)
#define DMAMUX1_USART1_TX      (25)
#define DMAMUX1_USART2_RX      (26)
#define DMAMUX1_USART2_TX      (27)
#define DMAMUX1_USART3_RX      (28)
#define DMAMUX1_USART3_TX      (29)
#define DMAMUX1_UART4_RX       (30)
#define DMAMUX1_UART4_TX       (31)
#define DMAMUX1_UART5_RX       (32)
#define DMAMUX1_UART5_TX       (33)
#define DMAMUX1_LPUART1_RX     (34)
#define DMAMUX1_LPUART1_TX     (35)
#define DMAMUX1_SAI1_A         (36)
#define DMAMUX1_SAI1_B         (37)
#define DMAMUX1_SAI2_A         (38)
#define DMAMUX1_SAI2_B         (39)
#define DMAMUX1_OCTOSPI1       (40)
#define DMAMUX1_OCTOSPI2       (41)
#define DMAMUX1_TIM1_CH1       (42)
#define DMAMUX1_TIM1_CH2       (43)
#define DMAMUX1_TIM1_CH3       (44)
#define DMAMUX1_TIM1_CH4       (45)
#define DMAMUX1_TIM1_UP        (46)
#define DMAMUX1_TIM1_TRIG      (47)
#define DMAMUX1_TIM1_COM       (48)
#define DMAMUX1_TIM8_CH1       (49)
#define DMAMUX1_TIM8_CH2       (50)
#define DMAMUX1_TIM8_CH3       (51)
#define DMAMUX1_TIM8_CH4       (52)
#define DMAMUX1_TIM8_UP        (53)
#define DMAMUX1_TIM8_TRIG      (54)
#define DMAMUX1_TIM8_COM       (55)
#define DMAMUX1_TIM2_CH1       (56)
#define DMAMUX1_TIM2_CH2       (57)
#define DMAMUX1_TIM2_CH3       (58)
#define DMAMUX1_TIM2_CH4       (59)
#define DMAMUX1_TIM2_UP        (60)
#define DMAMUX1_TIM3_CH1       (61)
#define DMAMUX1_TIM3_CH2       (62)
#define DMAMUX1_TIM3_CH3       (63)
#define DMAMUX1_TIM3_CH4       (64)
#define DMAMUX1_TIM3_UP        (65)
#define DMAMUX1_TIM3_TRIG      (66)
#define DMAMUX1_TIM4_CH1       (67)
#define DMAMUX1_TIM4_CH2       (68)
#define DMAMUX1_TIM4_CH3       (69)
#define DMAMUX1_TIM4_CH4       (70)
#define DMAMUX1_TIM4_UP        (71)
#define DMAMUX1_TIM5_CH1       (72)
#define DMAMUX1_TIM5_CH2       (73)
#define DMAMUX1_TIM5_CH3       (74)
#define DMAMUX1_TIM5_CH4       (75)
#define DMAMUX1_TIM5_UP        (76)
#define DMAMUX1_TIM5_TRIG      (77)
#define DMAMUX1_TIM15_CH1      (78)
#define DMAMUX1_TIM15_UP       (79)
#define DMAMUX1_TIM15_TRIG     (80)
#define DMAMUX1_TIM15_COM      (81)
#define DMAMUX1_TIM16_CH1      (82)
#define DMAMUX1_TIM16_UP       (83)
#define DMAMUX1_TIM17_CH1      (84)
#define DMAMUX1_TIM17_UP       (85)
#define DMAMUX1_DFSDM1_0       (86)
#define DMAMUX1_DFSDM1_1       (87)
#define DMAMUX1_DFSDM1_2       (88)
#define DMAMUX1_DFSDM1_3       (89)
#define DMAMUX1_DCMI           (90)
#define DMAMUX1_AES_IN         (91)
#define DMAMUX1_AES_OUT        (92)
#define DMAMUX1_HASH_IN        (93)
/* DMAMUX1 94-127: Reserved */

/* DMAMAP for DMA1 and DMA2 (DMAMUX1) ***************************************/

#define DMAMAP_REQ_GEN0_0      DMAMAP_MAP(DMA1, DMAMUX1_REQ_GEN0)
#define DMAMAP_REQ_GEN0_1      DMAMAP_MAP(DMA2, DMAMUX1_REQ_GEN0)
#define DMAMAP_REQ_GEN1_0      DMAMAP_MAP(DMA1, DMAMUX1_REQ_GEN1)
#define DMAMAP_REQ_GEN1_1      DMAMAP_MAP(DMA2, DMAMUX1_REQ_GEN1)
#define DMAMAP_REQ_GEN2_0      DMAMAP_MAP(DMA1, DMAMUX1_REQ_GEN2)
#define DMAMAP_REQ_GEN2_1      DMAMAP_MAP(DMA2, DMAMUX1_REQ_GEN2)
#define DMAMAP_REQ_GEN3_0      DMAMAP_MAP(DMA1, DMAMUX1_REQ_GEN3)
#define DMAMAP_REQ_GEN3_1      DMAMAP_MAP(DMA2, DMAMUX1_REQ_GEN3)
#define DMAMAP_ADC1_0          DMAMAP_MAP(DMA1, DMAMUX1_ADC1)
#define DMAMAP_ADC1_1          DMAMAP_MAP(DMA2, DMAMUX1_ADC1)
#define DMAMAP_DAC1_0          DMAMAP_MAP(DMA1, DMAMUX1_DAC1)
#define DMAMAP_DAC1_1          DMAMAP_MAP(DMA2, DMAMUX1_DAC1)
#define DMAMAP_DAC2_0          DMAMAP_MAP(DMA1, DMAMUX1_DAC2)
#define DMAMAP_DAC2_1          DMAMAP_MAP(DMA2, DMAMUX1_DAC2)
#define DMAMAP_TIM6_UP_0       DMAMAP_MAP(DMA1, DMAMUX1_TIM6_UP)
#define DMAMAP_TIM6_UP_1       DMAMAP_MAP(DMA2, DMAMUX1_TIM6_UP)
#define DMAMAP_TIM7_UP_0       DMAMAP_MAP(DMA1, DMAMUX1_TIM7_UP)
#define DMAMAP_TIM7_UP_1       DMAMAP_MAP(DMA2, DMAMUX1_TIM7_UP)
#define DMAMAP_SPI1_RX_0       DMAMAP_MAP(DMA1, DMAMUX1_SPI1_RX)
#define DMAMAP_SPI1_RX_1       DMAMAP_MAP(DMA2, DMAMUX1_SPI1_RX)
#define DMAMAP_SPI1_TX_0       DMAMAP_MAP(DMA1, DMAMUX1_SPI1_TX)
#define DMAMAP_SPI1_TX_1       DMAMAP_MAP(DMA2, DMAMUX1_SPI1_TX)
#define DMAMAP_SPI2_RX_0       DMAMAP_MAP(DMA1, DMAMUX1_SPI2_RX)
#define DMAMAP_SPI2_RX_1       DMAMAP_MAP(DMA2, DMAMUX1_SPI2_RX)
#define DMAMAP_SPI2_TX_0       DMAMAP_MAP(DMA1, DMAMUX1_SPI2_TX)
#define DMAMAP_SPI2_TX_1       DMAMAP_MAP(DMA2, DMAMUX1_SPI2_TX)
#define DMAMAP_SPI3_RX_0       DMAMAP_MAP(DMA1, DMAMUX1_SPI3_RX)
#define DMAMAP_SPI3_RX_1       DMAMAP_MAP(DMA2, DMAMUX1_SPI3_RX)
#define DMAMAP_SPI3_TX_0       DMAMAP_MAP(DMA1, DMAMUX1_SPI3_TX)
#define DMAMAP_SPI3_TX_1       DMAMAP_MAP(DMA2, DMAMUX1_SPI3_TX)
#define DMAMAP_I2C1_RX_0       DMAMAP_MAP(DMA1, DMAMUX1_I2C1_RX)
#define DMAMAP_I2C1_RX_1       DMAMAP_MAP(DMA2, DMAMUX1_I2C1_RX)
#define DMAMAP_I2C1_TX_0       DMAMAP_MAP(DMA1, DMAMUX1_I2C1_TX)
#define DMAMAP_I2C1_TX_1       DMAMAP_MAP(DMA2, DMAMUX1_I2C1_TX)
#define DMAMAP_I2C2_RX_0       DMAMAP_MAP(DMA1, DMAMUX1_I2C2_RX)
#define DMAMAP_I2C2_RX_1       DMAMAP_MAP(DMA2, DMAMUX1_I2C2_RX)
#define DMAMAP_I2C2_TX_0       DMAMAP_MAP(DMA1, DMAMUX1_I2C2_TX)
#define DMAMAP_I2C2_TX_1       DMAMAP_MAP(DMA2, DMAMUX1_I2C2_TX)
#define DMAMAP_I2C3_RX_0       DMAMAP_MAP(DMA1, DMAMUX1_I2C3_RX)
#define DMAMAP_I2C3_RX_1       DMAMAP_MAP(DMA2, DMAMUX1_I2C3_RX)
#define DMAMAP_I2C3_TX_0       DMAMAP_MAP(DMA1, DMAMUX1_I2C3_TX)
#define DMAMAP_I2C3_TX_1       DMAMAP_MAP(DMA2, DMAMUX1_I2C3_TX)
#define DMAMAP_I2C4_RX_0       DMAMAP_MAP(DMA1, DMAMUX1_I2C4_RX)
#define DMAMAP_I2C4_RX_1       DMAMAP_MAP(DMA2, DMAMUX1_I2C4_RX)
#define DMAMAP_I2C4_TX_0       DMAMAP_MAP(DMA1, DMAMUX1_I2C4_TX)
#define DMAMAP_I2C4_TX_1       DMAMAP_MAP(DMA2, DMAMUX1_I2C4_TX)
#define DMAMAP_USART1_RX_0     DMAMAP_MAP(DMA1, DMAMUX1_USART1_RX)
#define DMAMAP_USART1_RX_1     DMAMAP_MAP(DMA2, DMAMUX1_USART1_RX)
#define DMAMAP_USART1_TX_0     DMAMAP_MAP(DMA1, DMAMUX1_USART1_TX)
#define DMAMAP_USART1_TX_1     DMAMAP_MAP(DMA2, DMAMUX1_USART1_TX)
#define DMAMAP_USART2_RX_0     DMAMAP_MAP(DMA1, DMAMUX1_USART2_RX)
#define DMAMAP_USART2_RX_1     DMAMAP_MAP(DMA2, DMAMUX1_USART2_RX)
#define DMAMAP_USART2_TX_0     DMAMAP_MAP(DMA1, DMAMUX1_USART2_TX)
#define DMAMAP_USART2_TX_1     DMAMAP_MAP(DMA2, DMAMUX1_USART2_TX)
#define DMAMAP_USART3_RX_0     DMAMAP_MAP(DMA1, DMAMUX1_USART3_RX)
#define DMAMAP_USART3_RX_1     DMAMAP_MAP(DMA2, DMAMUX1_USART3_RX)
#define DMAMAP_USART3_TX_0     DMAMAP_MAP(DMA1, DMAMUX1_USART3_TX)
#define DMAMAP_USART3_TX_1     DMAMAP_MAP(DMA2, DMAMUX1_USART3_TX)
#define DMAMAP_UART4_RX_0      DMAMAP_MAP(DMA1, DMAMUX1_UART4_RX)
#define DMAMAP_UART4_RX_1      DMAMAP_MAP(DMA2, DMAMUX1_UART4_RX)
#define DMAMAP_UART4_TX_0      DMAMAP_MAP(DMA1, DMAMUX1_UART4_TX)
#define DMAMAP_UART4_TX_1      DMAMAP_MAP(DMA2, DMAMUX1_UART4_TX)
#define DMAMAP_UART5_RX_0      DMAMAP_MAP(DMA1, DMAMUX1_UART5_RX)
#define DMAMAP_UART5_RX_1      DMAMAP_MAP(DMA2, DMAMUX1_UART5_RX)
#define DMAMAP_UART5_TX_0      DMAMAP_MAP(DMA1, DMAMUX1_UART5_TX)
#define DMAMAP_UART5_TX_1      DMAMAP_MAP(DMA2, DMAMUX1_UART5_TX)
#define DMAMAP_LPUART1_RX_0    DMAMAP_MAP(DMA1, DMAMUX1_LPUART1_RX)
#define DMAMAP_LPUART1_RX_1    DMAMAP_MAP(DMA2, DMAMUX1_LPUART1_RX)
#define DMAMAP_LPUART1_TX_0    DMAMAP_MAP(DMA1, DMAMUX1_LPUART1_TX)
#define DMAMAP_LPUART1_TX_1    DMAMAP_MAP(DMA2, DMAMUX1_LPUART1_TX)
#define DMAMAP_SAI1_A_0        DMAMAP_MAP(DMA1, DMAMUX1_SAI1_A)
#define DMAMAP_SAI1_A_1        DMAMAP_MAP(DMA2, DMAMUX1_SAI1_A)
#define DMAMAP_SAI1_B_0        DMAMAP_MAP(DMA1, DMAMUX1_SAI1_B)
#define DMAMAP_SAI1_B_1        DMAMAP_MAP(DMA2, DMAMUX1_SAI1_B)
#define DMAMAP_SAI2_A_0        DMAMAP_MAP(DMA1, DMAMUX1_SAI2_A)
#define DMAMAP_SAI2_A_1        DMAMAP_MAP(DMA2, DMAMUX1_SAI2_A)
#define DMAMAP_SAI2_B_0        DMAMAP_MAP(DMA1, DMAMUX1_SAI2_B)
#define DMAMAP_SAI2_B_1        DMAMAP_MAP(DMA2, DMAMUX1_SAI2_B)
#define DMAMAP_OCTOSPI1_0      DMAMAP_MAP(DMA1, DMAMUX1_OCTOSPI1)
#define DMAMAP_OCTOSPI1_1      DMAMAP_MAP(DMA2, DMAMUX1_OCTOSPI1)
#define DMAMAP_OCTOSPI2_0      DMAMAP_MAP(DMA1, DMAMUX1_OCTOSPI2)
#define DMAMAP_OCTOSPI2_1      DMAMAP_MAP(DMA2, DMAMUX1_OCTOSPI2)
#define DMAMAP_TIM1_CH1_0      DMAMAP_MAP(DMA1, DMAMUX1_TIM1_CH1)
#define DMAMAP_TIM1_CH1_1      DMAMAP_MAP(DMA2, DMAMUX1_TIM1_CH1)
#define DMAMAP_TIM1_CH2_0      DMAMAP_MAP(DMA1, DMAMUX1_TIM1_CH2)
#define DMAMAP_TIM1_CH2_1      DMAMAP_MAP(DMA2, DMAMUX1_TIM1_CH2)
#define DMAMAP_TIM1_CH3_0      DMAMAP_MAP(DMA1, DMAMUX1_TIM1_CH3)
#define DMAMAP_TIM1_CH3_1      DMAMAP_MAP(DMA2, DMAMUX1_TIM1_CH3)
#define DMAMAP_TIM1_CH4_0      DMAMAP_MAP(DMA1, DMAMUX1_TIM1_CH4)
#define DMAMAP_TIM1_CH4_1      DMAMAP_MAP(DMA2, DMAMUX1_TIM1_CH4)
#define DMAMAP_TIM1_UP_0       DMAMAP_MAP(DMA1, DMAMUX1_TIM1_UP)
#define DMAMAP_TIM1_UP_1       DMAMAP_MAP(DMA2, DMAMUX1_TIM1_UP)
#define DMAMAP_TIM1_TRIG_0     DMAMAP_MAP(DMA1, DMAMUX1_TIM1_TRIG)
#define DMAMAP_TIM1_TRIG_1     DMAMAP_MAP(DMA2, DMAMUX1_TIM1_TRIG)
#define DMAMAP_TIM1_COM_0      DMAMAP_MAP(DMA1, DMAMUX1_TIM1_COM)
#define DMAMAP_TIM1_COM_1      DMAMAP_MAP(DMA2, DMAMUX1_TIM1_COM)
#define DMAMAP_TIM8_CH1_0      DMAMAP_MAP(DMA1, DMAMUX1_TIM8_CH1)
#define DMAMAP_TIM8_CH1_1      DMAMAP_MAP(DMA2, DMAMUX1_TIM8_CH1)
#define DMAMAP_TIM8_CH2_0      DMAMAP_MAP(DMA1, DMAMUX1_TIM8_CH2)
#define DMAMAP_TIM8_CH2_1      DMAMAP_MAP(DMA2, DMAMUX1_TIM8_CH2)
#define DMAMAP_TIM8_CH3_0      DMAMAP_MAP(DMA1, DMAMUX1_TIM8_CH3)
#define DMAMAP_TIM8_CH3_1      DMAMAP_MAP(DMA2, DMAMUX1_TIM8_CH3)
#define DMAMAP_TIM8_CH4_0      DMAMAP_MAP(DMA1, DMAMUX1_TIM8_CH4)
#define DMAMAP_TIM8_CH4_1      DMAMAP_MAP(DMA2, DMAMUX1_TIM8_CH4)
#define DMAMAP_TIM8_UP_0       DMAMAP_MAP(DMA1, DMAMUX1_TIM8_UP)
#define DMAMAP_TIM8_UP_1       DMAMAP_MAP(DMA2, DMAMUX1_TIM8_UP)
#define DMAMAP_TIM8_TRIG_0     DMAMAP_MAP(DMA1, DMAMUX1_TIM8_TRIG)
#define DMAMAP_TIM8_TRIG_1     DMAMAP_MAP(DMA2, DMAMUX1_TIM8_TRIG)
#define DMAMAP_TIM8_COM_0      DMAMAP_MAP(DMA1, DMAMUX1_TIM8_COM)
#define DMAMAP_TIM8_COM_1      DMAMAP_MAP(DMA2, DMAMUX1_TIM8_COM)
#define DMAMAP_TIM2_CH1_0      DMAMAP_MAP(DMA1, DMAMUX1_TIM2_CH1)
#define DMAMAP_TIM2_CH1_1      DMAMAP_MAP(DMA2, DMAMUX1_TIM2_CH1)
#define DMAMAP_TIM2_CH2_0      DMAMAP_MAP(DMA1, DMAMUX1_TIM2_CH2)
#define DMAMAP_TIM2_CH2_1      DMAMAP_MAP(DMA2, DMAMUX1_TIM2_CH2)
#define DMAMAP_TIM2_CH3_0      DMAMAP_MAP(DMA1, DMAMUX1_TIM2_CH3)
#define DMAMAP_TIM2_CH3_1      DMAMAP_MAP(DMA2, DMAMUX1_TIM2_CH3)
#define DMAMAP_TIM2_CH4_0      DMAMAP_MAP(DMA1, DMAMUX1_TIM2_CH4)
#define DMAMAP_TIM2_CH4_1      DMAMAP_MAP(DMA2, DMAMUX1_TIM2_CH4)
#define DMAMAP_TIM2_UP_0       DMAMAP_MAP(DMA1, DMAMUX1_TIM2_UP)
#define DMAMAP_TIM2_UP_1       DMAMAP_MAP(DMA2, DMAMUX1_TIM2_UP)
#define DMAMAP_TIM3_CH1_0      DMAMAP_MAP(DMA1, DMAMUX1_TIM3_CH1)
#define DMAMAP_TIM3_CH1_1      DMAMAP_MAP(DMA2, DMAMUX1_TIM3_CH1)
#define DMAMAP_TIM3_CH2_0      DMAMAP_MAP(DMA1, DMAMUX1_TIM3_CH2)
#define DMAMAP_TIM3_CH2_1      DMAMAP_MAP(DMA2, DMAMUX1_TIM3_CH2)
#define DMAMAP_TIM3_CH3_0      DMAMAP_MAP(DMA1, DMAMUX1_TIM3_CH3)
#define DMAMAP_TIM3_CH3_1      DMAMAP_MAP(DMA2, DMAMUX1_TIM3_CH3)
#define DMAMAP_TIM3_CH4_0      DMAMAP_MAP(DMA1, DMAMUX1_TIM3_CH4)
#define DMAMAP_TIM3_CH4_1      DMAMAP_MAP(DMA2, DMAMUX1_TIM3_CH4)
#define DMAMAP_TIM3_UP_0       DMAMAP_MAP(DMA1, DMAMUX1_TIM3_UP)
#define DMAMAP_TIM3_UP_1       DMAMAP_MAP(DMA2, DMAMUX1_TIM3_UP)
#define DMAMAP_TIM3_TRIG_0     DMAMAP_MAP(DMA1, DMAMUX1_TIM3_TRIG)
#define DMAMAP_TIM3_TRIG_1     DMAMAP_MAP(DMA2, DMAMUX1_TIM3_TRIG)
#define DMAMAP_TIM4_CH1_0      DMAMAP_MAP(DMA1, DMAMUX1_TIM4_CH1)
#define DMAMAP_TIM4_CH1_1      DMAMAP_MAP(DMA2, DMAMUX1_TIM4_CH1)
#define DMAMAP_TIM4_CH2_0      DMAMAP_MAP(DMA1, DMAMUX1_TIM4_CH2)
#define DMAMAP_TIM4_CH2_1      DMAMAP_MAP(DMA2, DMAMUX1_TIM4_CH2)
#define DMAMAP_TIM4_CH3_0      DMAMAP_MAP(DMA1, DMAMUX1_TIM4_CH3)
#define DMAMAP_TIM4_CH3_1      DMAMAP_MAP(DMA2, DMAMUX1_TIM4_CH3)
#define DMAMAP_TIM4_CH4_0      DMAMAP_MAP(DMA1, DMAMUX1_TIM4_CH4)
#define DMAMAP_TIM4_CH4_1      DMAMAP_MAP(DMA2, DMAMUX1_TIM4_CH4)
#define DMAMAP_TIM4_UP_0       DMAMAP_MAP(DMA1, DMAMUX1_TIM4_UP)
#define DMAMAP_TIM4_UP_1       DMAMAP_MAP(DMA2, DMAMUX1_TIM4_UP)
#define DMAMAP_TIM5_CH1_0      DMAMAP_MAP(DMA1, DMAMUX1_TIM5_CH1)
#define DMAMAP_TIM5_CH1_1      DMAMAP_MAP(DMA2, DMAMUX1_TIM5_CH1)
#define DMAMAP_TIM5_CH2_0      DMAMAP_MAP(DMA1, DMAMUX1_TIM5_CH2)
#define DMAMAP_TIM5_CH2_1      DMAMAP_MAP(DMA2, DMAMUX1_TIM5_CH2)
#define DMAMAP_TIM5_CH3_0      DMAMAP_MAP(DMA1, DMAMUX1_TIM5_CH3)
#define DMAMAP_TIM5_CH3_1      DMAMAP_MAP(DMA2, DMAMUX1_TIM5_CH3)
#define DMAMAP_TIM5_CH4_0      DMAMAP_MAP(DMA1, DMAMUX1_TIM5_CH4)
#define DMAMAP_TIM5_CH4_1      DMAMAP_MAP(DMA2, DMAMUX1_TIM5_CH4)
#define DMAMAP_TIM5_UP_0       DMAMAP_MAP(DMA1, DMAMUX1_TIM5_UP)
#define DMAMAP_TIM5_UP_1       DMAMAP_MAP(DMA2, DMAMUX1_TIM5_UP)
#define DMAMAP_TIM5_TRIG_0     DMAMAP_MAP(DMA1, DMAMUX1_TIM5_TRIG)
#define DMAMAP_TIM5_TRIG_1     DMAMAP_MAP(DMA2, DMAMUX1_TIM5_TRIG)
#define DMAMAP_TIM15_CH1_0     DMAMAP_MAP(DMA1, DMAMUX1_TIM15_CH1)
#define DMAMAP_TIM15_CH1_1     DMAMAP_MAP(DMA2, DMAMUX1_TIM15_CH1)
#define DMAMAP_TIM15_UP_0      DMAMAP_MAP(DMA1, DMAMUX1_TIM15_UP)
#define DMAMAP_TIM15_UP_1      DMAMAP_MAP(DMA2, DMAMUX1_TIM15_UP)
#define DMAMAP_TIM15_TRIG_0    DMAMAP_MAP(DMA1, DMAMUX1_TIM15_TRIG)
#define DMAMAP_TIM15_TRIG_1    DMAMAP_MAP(DMA2, DMAMUX1_TIM15_TRIG)
#define DMAMAP_TIM15_COM_0     DMAMAP_MAP(DMA1, DMAMUX1_TIM15_COM)
#define DMAMAP_TIM15_COM_1     DMAMAP_MAP(DMA2, DMAMUX1_TIM15_COM)
#define DMAMAP_TIM16_CH1_0     DMAMAP_MAP(DMA1, DMAMUX1_TIM16_CH1)
#define DMAMAP_TIM16_CH1_1     DMAMAP_MAP(DMA2, DMAMUX1_TIM16_CH1)
#define DMAMAP_TIM16_UP_0      DMAMAP_MAP(DMA1, DMAMUX1_TIM16_UP)
#define DMAMAP_TIM16_UP_1      DMAMAP_MAP(DMA2, DMAMUX1_TIM16_UP)
#define DMAMAP_TIM17_CH1_0     DMAMAP_MAP(DMA1, DMAMUX1_TIM17_CH1)
#define DMAMAP_TIM17_CH1_1     DMAMAP_MAP(DMA2, DMAMUX1_TIM17_CH1)
#define DMAMAP_TIM17_UP_0      DMAMAP_MAP(DMA1, DMAMUX1_TIM17_UP)
#define DMAMAP_TIM17_UP_1      DMAMAP_MAP(DMA2, DMAMUX1_TIM17_UP)
#define DMAMAP_DFSDM0_0        DMAMAP_MAP(DMA1, DMAMUX1_DFSDM1_0)
#define DMAMAP_DFSDM0_1        DMAMAP_MAP(DMA2, DMAMUX1_DFSDM1_0)
#define DMAMAP_DFSDM1_0        DMAMAP_MAP(DMA1, DMAMUX1_DFSDM1_1)
#define DMAMAP_DFSDM1_1        DMAMAP_MAP(DMA2, DMAMUX1_DFSDM1_1)
#define DMAMAP_DFSDM2_0        DMAMAP_MAP(DMA1, DMAMUX1_DFSDM1_2)
#define DMAMAP_DFSDM2_1        DMAMAP_MAP(DMA2, DMAMUX1_DFSDM1_2)
#define DMAMAP_DFSDM3_0        DMAMAP_MAP(DMA1, DMAMUX1_DFSDM1_3)
#define DMAMAP_DFSDM3_1        DMAMAP_MAP(DMA2, DMAMUX1_DFSDM1_3)
#define DMAMAP_DCMI_0          DMAMAP_MAP(DMA1, DMAMUX1_DCMI)
#define DMAMAP_DCMI_1          DMAMAP_MAP(DMA2, DMAMUX1_DCMI)
#define DMAMAP_AES_IN_0        DMAMAP_MAP(DMA1, DMAMUX1_AES_IN)
#define DMAMAP_AES_IN_1        DMAMAP_MAP(DMA2, DMAMUX1_AES_IN)
#define DMAMAP_AES_OUT_0       DMAMAP_MAP(DMA1, DMAMUX1_AES_OUT)
#define DMAMAP_AES_OUT_1       DMAMAP_MAP(DMA2, DMAMUX1_AES_OUT)
#define DMAMAP_HASH_IN_0       DMAMAP_MAP(DMA1, DMAMUX1_HASH_IN)
#define DMAMAP_HASH_IN_1       DMAMAP_MAP(DMA2, DMAMUX1_HASH_IN)

#endif /* __ARCH_ARM_SRC_STM32L4_HARDWARE_STM32L4XRXX_DMAMUX_H */
