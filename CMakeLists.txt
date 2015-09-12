cmake_minimum_required(VERSION 3.2)
project(teensy)

set(ENV{PATH} "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games")
set(PLATFORMIO_CMD "/usr/local/bin/platformio")

include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoteensy/cores/teensy3")
include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoteensy/cores/teensy3/avr")
include_directories("$ENV{HOME}/.platformio/packages/framework-arduinoteensy/cores/teensy3/util")
include_directories("$ENV{HOME}/.platformio/packages/toolchain-gccarmnoneeabi/arm-none-eabi/include")
include_directories("$ENV{HOME}/.platformio/packages/toolchain-gccarmnoneeabi/lib/gcc/arm-none-eabi/4.8.3/include")
include_directories("$ENV{HOME}/.platformio/packages/toolchain-gccarmnoneeabi/lib/gcc/arm-none-eabi/4.8.3/include-fixed")

add_definitions(-DF_CPU=48000000L)
add_definitions(-DUSB_SERIAL)
add_definitions(-DLAYOUT_US_ENGLISH)
add_definitions(-D__MKL26Z64__)
add_definitions(-DARDUINO=10600)
add_definitions(-DTEENSYDUINO=124)
add_definitions(-DPLATFORMIO=020302)

add_custom_target(
    PLATFORMIO_BUILD ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_UPLOAD ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target upload
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_CLEAN ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target clean
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)