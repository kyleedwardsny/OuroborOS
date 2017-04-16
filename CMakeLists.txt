project(ouroboros C)
cmake_minimum_required(VERSION 3.5)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

macro(check_gnu LANG VARIABLE)
	if (NOT DEFINED ${VARIABLE})
		message(STATUS "Check ${LANG} compiler is GNU")
		if ("${CMAKE_${LANG}_COMPILER_ID}" STREQUAL "GNU")
			set(TMP 1)
		else()
			set(TMP 0)
		endif()
		set(${VARIABLE} ${TMP} CACHE INTERNAL "Result of CHECK_GNU(${LANG})")
		message(STATUS "Check ${LANG} compiler is GNU - done")
	endif()
endmacro()

check_gnu(C CC_IS_GNU)
if (NOT CC_IS_GNU)
	message(FATAL_ERROR "C compiler must be GCC")
endif()

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_BINARY_DIR}/include")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ffreestanding -G0")

find_program(MKIMAGE mkimage DOC "U-Boot uImage creator")
find_program(DTC dtc DOC "Device tree compiler")

include("config.cmake")

add_subdirectory("libou")
add_subdirectory("libfdt")
add_subdirectory("kernel")
add_subdirectory("fit")
add_subdirectory("fdt")
