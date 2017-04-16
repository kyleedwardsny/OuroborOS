project(libfdt LANGUAGES C)
cmake_minimum_required(VERSION 3.5)

include(OuCommon)

ADD_SOURCES(
	fdt.c
	fdt_addresses.c
	fdt_empty_tree.c
	fdt_overlay.c
	fdt_ro.c
	fdt_rw.c
	fdt_strerror.c
	fdt_sw.c
	fdt_wip.c
)

add_library(fdt ${CURRENT_SOURCES})
