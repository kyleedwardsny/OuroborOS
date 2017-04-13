project(ouroboros-kernel C ASM)
cmake_minimum_required(VERSION 3.5)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${CMAKE_CURRENT_SOURCE_DIR}/kernel.ld -nostdlib")

set(KERNEL_LOAD_ADDR 0x80010000)

configure_file(config.ld.in config.ld)
configure_file(fit/kernel.itsi.in fit/kernel.itsi)

set(KERNEL_BIN "${CMAKE_CURRENT_BINARY_DIR}/kernel.bin")

add_custom_command(
	OUTPUT "${KERNEL_BIN}"
	COMMAND "${CMAKE_OBJCOPY}"
		-O binary
		$<TARGET_FILE:kernel.elf>
		"${KERNEL_BIN}"
	DEPENDS $<TARGET_FILE:kernel.elf>
)
add_custom_target(kernel-bin DEPENDS "${KERNEL_BIN}")

add_executable(kernel.elf head.S main.c eat_self.c)
target_link_libraries(kernel.elf ou ou_fdt gcc)
set_property(TARGET kernel.elf APPEND PROPERTY LINK_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/kernel.ld")
