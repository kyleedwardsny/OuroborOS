project(ouroboros-ldinitrd C ASM)
cmake_minimum_required(VERSION 3.5)

include(OuCommon)

set(LDINITRD_BIN "${CMAKE_CURRENT_BINARY_DIR}/ldinitrd.bin")

add_custom_command(
	OUTPUT "${LDINITRD_BIN}"
	COMMAND "${CMAKE_OBJCOPY}"
		-O binary
		$<TARGET_FILE:ldinitrd.elf>
		"${LDINITRD_BIN}"
	DEPENDS ldinitrd.elf
)
add_custom_target(ldinitrd-bin DEPENDS "${LDINITRD_BIN}")

add_subdirectory("arch")

finish_executable(ldinitrd.elf)
set_property(TARGET ldinitrd.elf APPEND_STRING PROPERTY LINK_FLAGS " -nostdlib")
target_link_libraries(ldinitrd.elf ou gcc)
