project(libou LANGUAGES C)
cmake_minimum_required(VERSION 3.5)

include(OuCommon)

ADD_SOURCES(
	_fprintf.c
	memchr.c
	memcmp.c
	memcpy.c
	memmove.c
	memrcpy.c
	sprintf.c
	strcpy.c
	strlen.c
	strnlen.c
	sprintf.c
	_vfprintf.c
	vsprintf.c
)

add_library(ou ${CURRENT_SOURCES})
