project(ouroboros-kernel C ASM)
cmake_minimum_required(VERSION 3.5)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -nostdlib -nostdinc")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${CMAKE_CURRENT_SOURCE_DIR}/kernel.ld -Wl,--build-id=none")

add_executable(kernel.elf head.S main.c)
set_property(TARGET kernel.elf APPEND PROPERTY LINK_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/kernel.ld")
