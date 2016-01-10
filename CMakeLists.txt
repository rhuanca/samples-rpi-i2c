cmake_minimum_required(VERSION 3.3)
project(samples_rpi_i2c)

# rpi cross compiler
SET(CMAKE_SYSTEM_NAME Linux)
SET(ARM_TOOL_CHAIN $ENV{HOME}/dev/rpi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64)
SET(CMAKE_C_COMPILER   ${ARM_TOOL_CHAIN}/bin/arm-linux-gnueabihf-gcc)
SET(CMAKE_CXX_COMPILER ${ARM_TOOL_CHAIN}/bin/arm-linux-gnueabihf-g++)

# rpi target environment
SET(CMAKE_FIND_ROOT_PATH  ${ARM_TOOL_CHAIN}/arm-linux-gnueabihf/libc)

set(SOURCE_FILES main.c rpi.c)
add_executable(samples_rpi_i2c ${SOURCE_FILES})