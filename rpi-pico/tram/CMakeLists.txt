set(PROJECT main)

cmake_minimum_required(VERSION 3.13)
set(PICO_BOARD pico_w)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(${PROJECT} C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(${PROJECT}
  ${PROJECT}.c
)

target_link_libraries(${PROJECT}
  pico_stdlib
  pico_cyw43_arch_lwip_threadsafe_background
)

target_include_directories(${PROJECT}
  PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
)

pico_enable_stdio_usb(${PROJECT} 1)
pico_enable_stdio_uart(${PROJECT} 0)

pico_add_extra_outputs(${PROJECT})
