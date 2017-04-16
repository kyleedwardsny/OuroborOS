project(fit LANGUAGES)
cmake_minimum_required(VERSION 3.5)

include(OuCommon)

configure_file(ikernel.itsi.in ikernel.itsi)
configure_file(fdt.itsi.in fdt.itsi)

add_itb(image.itb image.its)
add_custom_target(itb ALL DEPENDS image.itb)
