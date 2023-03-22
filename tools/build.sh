#!/usr/bin/env bash
# tools/build.sh
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

function cleanup()
{
  # keep the mapping but change to the link since:
  # 1.root can't access mount point created by normal user
  # 2.debugger could find the source code without manual setting
  fusermount -u ${MOUNTDIR}
  rmdir ${MOUNTDIR}
  ln -s ${ROOTDIR} ${MOUNTDIR}
}

function mount_unionfs()
{
  echo -e "Mount command line:"
  echo -e "  unionfs-fuse -o cow ${OUTDIR}=RW:${ROOTDIR}=RO ${MOUNTDIR}"

  rm -f ${MOUNTDIR}
  mkdir -p ${MOUNTDIR}
  unionfs-fuse -o cow ${OUTDIR}=RW:${ROOTDIR}=RO ${MOUNTDIR}
}

function setup_toolchain()
{
  if [ "`uname`" == "Darwin" ]; then
    export MACOSX_DEPLOYMENT_TARGET=11
    echo -e "Note: macOS users need to manually deploy toolchains. Skipping prebuilts setup."
    return
  fi

  ARCH=(\
      "xtensa" \
      "arm" \
      "arm64" \
      "risc-v" \
      "tc32" )

  TOOLCHAIN=(\
            "gcc" \
            "clang" )

  if [ "$XTENSAD_LICENSE_FILE" == "" ]; then
    export XTENSAD_LICENSE_FILE=28000@0.0.0.0
  fi
  export WASI_SDK_PATH=${ROOTDIR}/prebuilts/clang/linux/wasm
  export PATH=${WASI_SDK_PATH}:$PATH
  export PYTHONPATH=${PYTHONPATH}:${ROOTDIR}/prebuilts/tools/python/dist-packages/pyelftools
  export PYTHONPATH=${PYTHONPATH}:${ROOTDIR}/prebuilts/tools/python/dist-packages/cxxfilt

  for (( i = 0; i < ${#ARCH[*]}; i++)); do
    for (( j = 0; j < ${#TOOLCHAIN[*]}; j++)); do
      export PATH=${ROOTDIR}/prebuilts/${TOOLCHAIN[$j]}/linux/${ARCH[$i]}/bin:$PATH
    done
  done

  # Arm Compiler
  export PATH=${ROOTDIR}/prebuilts/clang/linux/armclang/bin:$PATH

  if [ ! -n "${ARM_PRODUCT_DEF}" ]; then
    export ARM_PRODUCT_DEF=${ROOTDIR}/prebuilts/clang/linux/armclang/mappings/eval.elmap
  fi
  if [ ! -n "${LM_LICENSE_FILE}" ]; then
    export LM_LICENSE_FILE=${HOME}/.arm/ds/licenses/DS000-EV-31030.lic
  fi
  if [ ! -n "${ARMLMD_LICENSE_FILE}" ]; then
    export ARMLMD_LICENSE_FILE=${HOME}/.arm/ds/licenses/DS000-EV-31030.lic
  fi

  # Generate compile database file compile_commands.json
  if type bear >/dev/null 2>&1; then
    bear="bear -a -o compile_commands.json "
  fi

  # Add compile cache
  CCACHE_DIR=${ROOTDIR}/prebuilts/tools/ccache
  export PATH="${CCACHE_DIR}:$PATH"

  # AIDL Tool
  export PATH=${ROOTDIR}/prebuilts/tools/aidl:$PATH
}

function build_board()
{
  echo -e "Build command line:"
  echo -e "  ${TOOLSDIR}/configure.sh -e $1"
  echo -e "  make -C ${NUTTXDIR} EXTRAFLAGS="$EXTRA_FLAGS" ${@:2}"
  echo -e "  make -C ${NUTTXDIR} savedefconfig"

  if [ ! -f "${ROOTDIR}/prebuilts/kconfig-frontends/bin/kconfig-conf" ] &&
     [ ! -x "$(command -v kconfig-conf)" ]; then
    pushd ${ROOTDIR}/prebuilts/kconfig-frontends
    ./configure --prefix=${ROOTDIR}/prebuilts/kconfig-frontends 1>/dev/null
    touch aclocal.m4 Makefile.in
    make install 1>/dev/null
    popd
  fi
  export PATH=${ROOTDIR}/prebuilts/kconfig-frontends/bin:$PATH

  setup_toolchain

  if ! ${TOOLSDIR}/configure.sh -e $1; then
    echo "Error: ############# config ${1} fail ##############"
    exit 1
  fi

  if ! ${bear} make -C ${NUTTXDIR} EXTRAFLAGS="$EXTRA_FLAGS" ${@:2}; then
    echo "Error: ############# build ${1} fail ##############"
    exit 2
  fi

  if [ "${2}" == "distclean" ]; then
    return;
  fi

   if ! make -C ${NUTTXDIR} savedefconfig; then
    echo "Error: ############# save ${1} fail ##############"
    exit 3
  fi
  if [ ! -d $1 ]; then
    cp ${NUTTXDIR}/defconfig ${ROOTDIR}/nuttx/boards/*/*/${1/[:|\/]//configs/}
  else
    cp ${NUTTXDIR}/defconfig $1
  fi
}


if [ $# == 0 ]; then
  echo "Usage: $0 [-m] <board-name>:<config-name> [-e <extraflags>] [make options]"
  echo ""
  echo "Where:"
  echo "  -m: out of tree build. Or default in tree build without it."
  echo "  -e: pass extra c/c++ flags such as -Werror via make command line"
  exit 1
fi

ROOTDIR=$(dirname $(readlink -f ${0}))
ROOTDIR=$(realpath ${ROOTDIR}/../..)

CONFIGPATH=$2

if [ $1 == "-m" ]; then
  # out of tree build
  confparams=(${CONFIGPATH//:/ })
  configdir=${confparams[1]}

  if [ -z "${configdir}" ]; then
    # handle cases where the end is a "/"
    if [ "${CONFIGPATH:(-1)}" = "/" ]; then
      CONFIGPATH=${CONFIGPATH:0:-1}
    fi
    boarddir=`echo ${CONFIGPATH} | rev | cut -d'/' -f3 | rev`
    configdir=`echo ${CONFIGPATH} | rev | cut -d'/' -f1 | rev`
  else
    boarddir=${confparams[0]}
  fi

  OUTDIR=${ROOTDIR}/out/${boarddir}/${configdir}
  MOUNTDIR=${OUTDIR}/.unionfs
  NUTTXDIR=${MOUNTDIR}/nuttx

  trap cleanup EXIT
  mount_unionfs
  shift
else
  # in tree build
  OUTDIR=${ROOTDIR}
  NUTTXDIR=${ROOTDIR}/nuttx
fi

TOOLSDIR=${NUTTXDIR}/tools
board_config=$1
shift

EXTRA_FLAGS="-Wno-cpp"
if [ $1 == "-e" ]; then
  shift
  EXTRA_FLAGS+=" $1"
  echo "extraflags: $EXTRA_FLAGS"
  shift
fi

if [ -d ${ROOTDIR}/${board_config} ]; then
  build_board ${ROOTDIR}/${board_config} $*
else
  build_board ${board_config} $*
fi

