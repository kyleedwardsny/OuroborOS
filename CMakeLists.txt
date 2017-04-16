project(ouroboros C)
cmake_minimum_required(VERSION 3.5)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

include(CheckTypeSize)

macro(CHECK_GNU LANG VARIABLE)
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

CHECK_GNU(C CC_IS_GNU)
if (NOT CC_IS_GNU)
	message(FATAL_ERROR "C compiler must be GCC")
endif()

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_BINARY_DIR}/include")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ffreestanding -G0")

find_program(MKIMAGE mkimage DOC "U-Boot uImage creator")
find_program(DTC dtc DOC "Device tree compiler")

set(IMAGE_ITB "${CMAKE_CURRENT_BINARY_DIR}/image.itb")
set(IMAGE_ITS "${CMAKE_CURRENT_SOURCE_DIR}/image.its")
set(KERNEL_FIT "${CMAKE_CURRENT_BINARY_DIR}/kernel/fit")

add_custom_command(
	OUTPUT "${IMAGE_ITB}"
	COMMAND "${MKIMAGE}"
		-f "${IMAGE_ITS}"
		-D "-i ${KERNEL_FIT} -i ${CMAKE_CURRENT_BINARY_DIR} -O dtb"
		"${IMAGE_ITB}"
	DEPENDS "${IMAGE_ITS}" "${KERNEL_FIT}/kernel.itsi" kernel-bin "${CMAKE_CURRENT_BINARY_DIR}/kernel/kernel.bin" dtb "${CMAKE_CURRENT_BINARY_DIR}/dts/qemu_mips.dtb"
)
add_custom_target(itb ALL DEPENDS "${IMAGE_ITB}")

include("dts.cmake")

add_subdirectory("libou")
add_subdirectory("libfdt")
add_subdirectory("kernel")
