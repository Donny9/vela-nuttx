############################################################################
# tools/KernelLibs.mk
#
# SPDX-License-Identifier: Apache-2.0
#
# Licensed to the Apache Software Foundation (ASF) under one or more
# contributor license agreements.  See the NOTICE file distributed with
# this work for additional information regarding copyright ownership.  The
# ASF licenses this file to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance with the
# License.  You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
# License for the specific language governing permissions and limitations
# under the License.
#
############################################################################

# NUTTXLIBS is the list of NuttX libraries that is passed to the
#   processor-specific Makefile to build the final NuttX target.
# USERLIBS is the list of libraries used to build the final user-space
#   application
# EXPORTLIBS is the list of libraries that should be exported by
#   'make export' is

NUTTXLIBS = staging$(DELIM)libsched$(LIBEXT)
USERLIBS =

# Driver support.

NUTTXLIBS += staging$(DELIM)libdrivers$(LIBEXT)

# External code support

ifeq ($(EXTERNALDIR),external)
  NUTTXLIBS += staging$(DELIM)libexternal$(LIBEXT)
endif

# Add libraries for board support

NUTTXLIBS += staging$(DELIM)libboards$(LIBEXT)

# Add libraries for syscall support.  The C library will be needed by
# both the kernel- and user-space builds.

NUTTXLIBS += staging$(DELIM)libstubs$(LIBEXT) staging$(DELIM)libkc$(LIBEXT)
NUTTXLIBS += staging$(DELIM)libkmm$(LIBEXT) staging$(DELIM)libkarch$(LIBEXT)
USERLIBS  += staging$(DELIM)libproxies$(LIBEXT) staging$(DELIM)libc$(LIBEXT)
USERLIBS  += staging$(DELIM)libmm$(LIBEXT) staging$(DELIM)libarch$(LIBEXT)

# Add toolchain library support

ifeq ($(CONFIG_BUILTIN_TOOLCHAIN),)
NUTTXLIBS += staging$(DELIM)libkbuiltin$(LIBEXT)
USERLIBS += staging$(DELIM)libbuiltin$(LIBEXT)
endif

# Add libraries for math support.

ifeq ($(CONFIG_LIBM_TOOLCHAIN)$(CONFIG_LIBM_NONE),)
NUTTXLIBS += staging$(DELIM)libkm$(LIBEXT)
USERLIBS  += staging$(DELIM)libm$(LIBEXT)
endif

# Add library for system call instrumentation if needed

ifeq ($(CONFIG_SCHED_INSTRUMENTATION_SYSCALL),y)
NUTTXLIBS += staging$(DELIM)libwraps$(LIBEXT)
endif

# Add libraries for C++ support.  CXX, CXXFLAGS, and COMPILEXX must
# be defined in Make.defs for this to work!

ifeq ($(CONFIG_HAVE_CXX),y)
USERLIBS += staging$(DELIM)libxx$(LIBEXT)
endif

# Add libraries for network support

ifeq ($(CONFIG_NET),y)
NUTTXLIBS += staging$(DELIM)libnet$(LIBEXT)
endif

# Add libraries for Crypto API support

ifeq ($(CONFIG_CRYPTO),y)
NUTTXLIBS += staging$(DELIM)libcrypto$(LIBEXT)
endif

# Add libraries for file system support

NUTTXLIBS += staging$(DELIM)libfs$(LIBEXT) staging$(DELIM)libbinfmt$(LIBEXT)

# Add libraries for the NX graphics sub-system

ifeq ($(CONFIG_NX),y)
NUTTXLIBS += staging$(DELIM)libgraphics$(LIBEXT)
NUTTXLIBS += staging$(DELIM)libknx$(LIBEXT)
USERLIBS  += staging$(DELIM)libnx$(LIBEXT)
else ifeq ($(CONFIG_NXFONTS),y)
NUTTXLIBS += staging$(DELIM)libknx$(LIBEXT)
USERLIBS  += staging$(DELIM)libnx$(LIBEXT)
endif

# Add libraries for the Audio sub-system

ifeq ($(CONFIG_AUDIO),y)
NUTTXLIBS += staging$(DELIM)libaudio$(LIBEXT)
endif

# Add libraries for the Video sub-system

ifeq ($(CONFIG_VIDEO),y)
NUTTXLIBS += staging$(DELIM)libvideo$(LIBEXT)
endif

# Add libraries for the Wireless sub-system

ifeq ($(CONFIG_WIRELESS),y)
NUTTXLIBS += staging$(DELIM)libwireless$(LIBEXT)
endif

# Add DSP library

ifeq ($(CONFIG_LIBDSP),y)
NUTTXLIBS += staging$(DELIM)libdsp$(LIBEXT)
endif

ifeq ($(CONFIG_OPENAMP),y)
NUTTXLIBS += staging$(DELIM)libopenamp$(LIBEXT)
endif

# Add libraries for board common support

ifeq ($(CONFIG_ARCH_BOARD_COMMON),y)
NUTTXLIBS += staging$(DELIM)libboard$(LIBEXT)
endif

# Export only the user libraries

EXPORTLIBS = $(USERLIBS)
