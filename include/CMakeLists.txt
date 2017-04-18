project(include LANGUAGES)
cmake_minimum_required(VERSION 3.5)

configure_file(ouroboros/genconfig.h.in ouroboros/genconfig.h)

set(ARCH_DIR "ouroboros/arch")
set(ARCH_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${ARCH_DIR}")
set(ARCH_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/${ARCH_DIR}")

file(MAKE_DIRECTORY "${ARCH_BINARY_DIR}")

execute_process(COMMAND
	"${CMAKE_COMMAND}"
	-E create_symlink
	"${ARCH_SOURCE_DIR}/mips"
	"${ARCH_BINARY_DIR}/current"
	RESULT_VARIABLE _result
	OUTPUT_QUIET
	ERROR_QUIET
)

if (_result)
	message(FATAL_ERROR "Failed to create include/arch/current symlink")
endif()
