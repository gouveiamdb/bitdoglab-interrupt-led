# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================

set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(matrix_led C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable primeiro!
add_executable(matrix_led matrix_led.c)

# Agora sim, gera o código do programa PIO
pico_generate_pio_header(matrix_led ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio)

pico_set_program_name(matrix_led "matrix_led")
pico_set_program_version(matrix_led "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(matrix_led 1)
pico_enable_stdio_usb(matrix_led 1)

# Add the standard library and PIO library to the build
target_link_libraries(matrix_led
    pico_stdlib
    hardware_pio
)

# Add the standard include files to the build
target_include_directories(matrix_led PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${PICO_SDK_PATH}/src/rp2_common/hardware_pio/include
    ${PICO_SDK_PATH}/src/rp2040/hardware_regs/include
    ${PICO_SDK_PATH}/src/common/pico_stdlib/include
    ${PICO_SDK_PATH}/src/rp2_common/hardware_gpio/include
    ${PICO_SDK_PATH}/src/common/pico_base/include
    ${PICO_SDK_PATH}/src/boards/include
    ${PICO_SDK_PATH}/src/rp2_common/pico_platform/include
)

pico_add_extra_outputs(matrix_led)