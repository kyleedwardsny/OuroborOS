project(fdt LANGUAGES)
cmake_minimum_required(VERSION 3.5)

set(DTS_NAMES "qemu_mips")

foreach(_f ${DTS_NAMES})
	set(DTS_INFILE "${_f}.dts")
	set(DTS_OUTFILE "${_f}.dtb")

	list(APPEND DTS_INFILES "${DTS_INFILE}")
	list(APPEND DTS_OUTFILES "${DTS_OUTFILE}")

	add_dtb("${DTS_OUTFILE}" "${DTS_INFILE}")
endforeach()

add_custom_target(dtb DEPENDS ${DTS_OUTFILES})
