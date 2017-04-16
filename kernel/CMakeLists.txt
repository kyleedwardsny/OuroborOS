project(ouroboros-kernel C ASM)
cmake_minimum_required(VERSION 3.5)

include(OuCommon)

set(KERNEL_LOAD_ADDR 0x80010000)

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

add_sources(kernel.elf
	eat_self.c
	main.c
)

add_subdirectory("arch")

finish_executable(kernel.elf)
set_property(TARGET kernel.elf APPEND_STRING PROPERTY LINK_FLAGS " -nostdlib")
target_link_libraries(kernel.elf fdt ou gcc)
