cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(displaytemp C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(${PROJECT_NAME}
    main.c
    i2c_util.c
    adt7410.c
    so1602a.c
)

target_link_libraries(${PROJECT_NAME}
    pico_stdlib
    hardware_i2c
)

pico_add_extra_outputs(${PROJECT_NAME})
pico_enable_stdio_usb(${PROJECT_NAME} ON)
pico_enable_stdio_uart(${PROJECT_NAME} OFF)
