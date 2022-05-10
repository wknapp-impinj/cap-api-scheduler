#!/usr/bin/env bash
set -eu

BUILD_DIR=../build

# cd to script directory
cd $(dirname $(realpath $0))

# relocate the SDK (okay to call repeatedly)
export TOOLCHAIN_ROOT=${ETK_ROOT_PATH}/arm-toolchain # also used by toolchain file

cd ${TOOLCHAIN_ROOT}
./relocate-sdk.sh
cd -

# clean build?
if [[ ${1-} == "clean" ]]; then
  rm -rf $BUILD_DIR
fi

echo $(realpath cmake/armv7l.toolchain)

cmake \
    -DCMAKE_TOOLCHAIN_FILE=$(realpath cmake/armv7l.toolchain) \
    -DCMAKE_BUILD_TYPE=Release \
    -B $BUILD_DIR

cmake --build $BUILD_DIR --target generate_cap
