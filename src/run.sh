# ------------------- shell setting -------------------

#!/bin/bash
set -e

# ------------------- declare variable -------------------
TARGET_SOURCE_DIR=${1}
SOURCE_DIR=~/src
BUILD_DIR=~/build

# ------------------- declare function -------------------

## Colorful echo
function echo-e() {
    echo -e "\033[31m[`date`]\033[0m ${1}"
}
function echo-i() {
    echo -e "\033[32m[`date`]\033[0m ${1}"
}
function echo-w() {
    echo -e "\033[33m[`date`]\033[0m ${1}"
}

# ------------------- Execute script -------------------

if [ -d ${TARGET_SOURCE_DIR} ]; then
    # Remove old build directory and create new one.
    if [ -d ${BUILD_DIR}/${TARGET_SOURCE_DIR} ];
    then
        rm -rf ${BUILD_DIR}/${TARGET_SOURCE_DIR}
    fi
    mkdir -p ${BUILD_DIR}/${TARGET_SOURCE_DIR}
    # Build source code, if CMakeLists exist then use camke, else will use c++.
    if [ -e ${TARGET_SOURCE_DIR}/CMakeLists.txt ];
    then
        echo-i "Build with cmake"
        cmake -S ./${TARGET_SOURCE_DIR} -B ${BUILD_DIR}/${TARGET_SOURCE_DIR}
        make -C ${BUILD_DIR}/${TARGET_SOURCE_DIR}
    else
        echo-i "Build with c++"
        c++ ${1}/*.cpp -o ${BUILD_DIR}/${TARGET_SOURCE_DIR}/example
    fi
    # Execute target executable file.
    echo-i "Execute example"
    if [ -e ${BUILD_DIR}/${TARGET_SOURCE_DIR}/example ];
    then
        printf "\n----------\n"
        ${BUILD_DIR}/${TARGET_SOURCE_DIR}/example
        printf "\n----------\n"
    elif [ -e ${BUILD_DIR}/${TARGET_SOURCE_DIR}/example.sh ];
    then
        printf "\n----------\n"
        source ${BUILD_DIR}/${TARGET_SOURCE_DIR}/example.sh
        printf "\n----------\n"
    else
        echo-e "Executable example file not in /build/${TARGET_SOURCE_DIR} directory."
    fi
else
    echo-e "Target source code path is not exist."
fi
