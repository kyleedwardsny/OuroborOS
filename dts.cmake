set(DTS_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dts")
set(DTS_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/dts")

macro(dtc OUTFILE INFILE)
	add_custom_command(
		OUTPUT "${OUTFILE}"
		COMMAND "${DTC}"
			-O dtb
			-o "${OUTFILE}"
			"${INFILE}"
		DEPENDS "${INFILE}"
	)
endmacro()

set(DTS_NAMES "qemu_mips")

file(MAKE_DIRECTORY "${DTS_BINARY_DIR}")

foreach(f ${DTS_NAMES})
	set(DTS_INFILE "${DTS_SOURCE_DIR}/${f}.dts")
	set(DTS_OUTFILE "${DTS_BINARY_DIR}/${f}.dtb")

	list(APPEND DTS_INFILES "${DTS_INFILE}")
	list(APPEND DTS_OUTFILES "${DTS_OUTFILE}")

	dtc("${DTS_OUTFILE}" "${DTS_INFILE}")
endforeach()

add_custom_target(dtb DEPENDS ${DTS_OUTFILES})
