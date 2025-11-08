#!/bin/bash
set -x
NAME="baseball"
BUILD_DIR="build"
OUTPUT_DIR="coverage"
BINARY="./${BUILD_DIR}/${NAME}"
COV_FILE="${OUTPUT_DIR}/${NAME}"
COMMAND="./${BUILD_DIR}/${NAME} -f astros.csv -n $2"
cmake -D CMAKE_CXX_COMPILER=$1 src/ -G Ninja -B ${BUILD_DIR}
ninja -C ${BUILD_DIR}
rm -rf ${OUTPUT_DIR}
mkdir ${OUTPUT_DIR}

if [ "$1" = "g++" ]; then
    eval $COMMAND
    lcov --capture --directory ${BUILD_DIR} --output-file ${COV_FILE}.info --ignore-errors inconsistent
    lcov --remove ${COV_FILE}.info '/usr/include/*' --output-file ${COV_FILE}.info
    genhtml ${COV_FILE}.info --output-directory ${OUTPUT_DIR}
elif [ "$1" = "clang++" ]; then
    export LLVM_PROFILE_FILE="${COV_FILE}.profraw"
    eval $COMMAND
    llvm-profdata merge -sparse ${COV_FILE}.profraw -o ${COV_FILE}.profdata
    llvm-cov report ${BINARY} -instr-profile=${COV_FILE}.profdata
    llvm-cov show ${BINARY} -instr-profile=${COV_FILE}.profdata -format=html -o ${OUTPUT_DIR}
else
    echo "Usage: ./compileAndRun.sh <compiler> <test_number>"
    exit 1
fi
