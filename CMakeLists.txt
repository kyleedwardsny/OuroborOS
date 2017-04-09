project(ouroboros C)
cmake_minimum_required(VERSION 3.5)

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

CHECK_TYPE_SIZE("char" SIZE_CHAR)
CHECK_TYPE_SIZE("unsigned char" SIZE_UCHAR)
CHECK_TYPE_SIZE("short" SIZE_SHORT)
CHECK_TYPE_SIZE("unsigned short" SIZE_USHORT)
CHECK_TYPE_SIZE("int" SIZE_INT)
CHECK_TYPE_SIZE("unsigned int" SIZE_UINT)
CHECK_TYPE_SIZE("long" SIZE_LONG)
CHECK_TYPE_SIZE("unsigned long" SIZE_ULONG)
CHECK_TYPE_SIZE("long long" SIZE_LONGLONG)
CHECK_TYPE_SIZE("unsigned long long" SIZE_ULONGLONG)

macro(TRY_SET_TYPE EXPECTED_SIZE ACTUAL_SIZE TYPE VARIABLE)
	if (NOT DEFINED ${VARIABLE})
		if (${ACTUAL_SIZE} EQUAL ${EXPECTED_SIZE})
			set(${VARIABLE} "${TYPE}")
		endif()
	endif()
endmacro()

macro(ENSURE_SET_TYPE VARIABLE)
	if (NOT DEFINED ${VARIABLE})
		message(FATAL_ERROR "Type for ${VARIABLE} is not set")
	endif()
endmacro()

TRY_SET_TYPE(1 ${SIZE_CHAR} "char" INT8_TYPE)
ENSURE_SET_TYPE(INT8_TYPE)

TRY_SET_TYPE(1 ${SIZE_UCHAR} "unsigned char" UINT8_TYPE)
ENSURE_SET_TYPE(UINT8_TYPE)

TRY_SET_TYPE(2 ${SIZE_SHORT} "short" INT16_TYPE)
TRY_SET_TYPE(2 ${SIZE_INT} "int" INT16_TYPE)
ENSURE_SET_TYPE(INT16_TYPE)

TRY_SET_TYPE(2 ${SIZE_USHORT} "unsigned short" UINT16_TYPE)
TRY_SET_TYPE(2 ${SIZE_UINT} "unsigned int" UINT16_TYPE)
ENSURE_SET_TYPE(UINT16_TYPE)

TRY_SET_TYPE(4 ${SIZE_INT} "int" INT32_TYPE)
TRY_SET_TYPE(4 ${SIZE_LONG} "long" INT32_TYPE)
ENSURE_SET_TYPE(INT32_TYPE)

TRY_SET_TYPE(4 ${SIZE_UINT} "unsigned int" UINT32_TYPE)
TRY_SET_TYPE(4 ${SIZE_ULONG} "unsigned long" UINT32_TYPE)
ENSURE_SET_TYPE(UINT32_TYPE)

TRY_SET_TYPE(8 ${SIZE_LONG} "long" INT64_TYPE)
TRY_SET_TYPE(8 ${SIZE_LONGLONG} "long long" INT64_TYPE)
ENSURE_SET_TYPE(INT64_TYPE)

TRY_SET_TYPE(8 ${SIZE_ULONG} "unsigned long" UINT64_TYPE)
TRY_SET_TYPE(8 ${SIZE_ULONGLONG} "unsigned long long" UINT64_TYPE)
ENSURE_SET_TYPE(UINT64_TYPE)

configure_file("include/ouroboros/stdint.h.in" "include/ouroboros/stdint.h")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_BINARY_DIR}/include")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ffreestanding -G0")

find_program(MKIMAGE mkimage DOC "U-Boot uImage creator")

set(IMAGE_ITB "${CMAKE_CURRENT_BINARY_DIR}/image.itb")
set(IMAGE_ITS "${CMAKE_CURRENT_SOURCE_DIR}/image.its")
set(KERNEL_FIT "${CMAKE_CURRENT_BINARY_DIR}/kernel/fit")

add_custom_command(
	OUTPUT "${IMAGE_ITB}"
	COMMAND "${MKIMAGE}"
		-f "${IMAGE_ITS}"
		-D "-i ${KERNEL_FIT} -O dtb"
		"${IMAGE_ITB}"
	DEPENDS "${IMAGE_ITS}" "${KERNEL_FIT}/kernel.itsi" kernel-bin
)
add_custom_target(itb ALL DEPENDS "${IMAGE_ITB}")

add_subdirectory("libou")
add_subdirectory("kernel")
