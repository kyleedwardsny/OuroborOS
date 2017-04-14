project(libfdt LANGUAGES C)
cmake_minimum_required(VERSION 3.5)

add_library(fdt fdt.c fdt_ro.c fdt_wip.c fdt_sw.c fdt_rw.c fdt_strerror.c fdt_empty_tree.c fdt_addresses.c fdt_overlay.c)
