/****************************************************************************
 * arch/arm/src/cxd32xx/cxd32_config.h
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

#ifndef __ARCH_ARM_SRC_CXD32XX_CXD32_CONFIG_H
#define __ARCH_ARM_SRC_CXD32XX_CXD32_CONFIG_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Required configuration settings */

/* Are any UARTs enabled? */

#undef HAVE_UART
#if defined(CONFIG_CXD32_UART0)
#  define HAVE_UART 1
#endif

/* Is there a serial console? There should be at most one defined.  It could
 * be on any UARTn, n=0,1,2,3 - OR - there might not be any serial console at
 * all.
 */

#if defined(CONFIG_UART0_SERIAL_CONSOLE)
#  define HAVE_CONSOLE 1
#endif

/****************************************************************************
 * Public Types
 ****************************************************************************/

/****************************************************************************
 * Public Data
 ****************************************************************************/

#endif /* __ARCH_ARM_SRC_CXD32XX_CXD32_CONFIG_H */
