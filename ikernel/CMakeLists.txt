project(ouroboros-ikernel C ASM)
cmake_minimum_required(VERSION 3.5)

include(OuCommon)

set(IKERNEL_BIN "${CMAKE_CURRENT_BINARY_DIR}/ikernel.bin")

add_custom_command(
	OUTPUT "${IKERNEL_BIN}"
	COMMAND "${CMAKE_OBJCOPY}"
		-O binary
		$<TARGET_FILE:ikernel.elf>
		"${IKERNEL_BIN}"
	DEPENDS ikernel.elf
)
add_custom_target(ikernel-bin DEPENDS "${IKERNEL_BIN}")

add_sources(ikernel.elf
	eat_self.c
	main.c
)

add_subdirectory("arch")
add_subdirectory("include")

finish_executable(ikernel.elf)
set_property(TARGET ikernel.elf APPEND_STRING PROPERTY LINK_FLAGS " -nostdlib")
target_link_libraries(ikernel.elf fdt ou gcc)
target_include_directories(ikernel.elf PRIVATE include)
