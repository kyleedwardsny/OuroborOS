project(fit LANGUAGES)
cmake_minimum_required(VERSION 3.5)

include(OuCommon)

configure_file(ikernel.itsi.in ikernel.itsi)
configure_file(fdt.itsi.in fdt.itsi)

add_itb(image.itb image.its "${CMAKE_CURRENT_BINARY_DIR}/ikernel.itsi" "${CMAKE_CURRENT_BINARY_DIR}/fdt.itsi" kernel-bin dtb)
add_custom_target(itb ALL DEPENDS image.itb)
