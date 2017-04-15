project(libou LANGUAGES C)
cmake_minimum_required(VERSION 3.5)

add_library(ou strcpy.c strlen.c strnlen.c _fprintf.c _vfprintf.c sprintf.c vsprintf.c strchr.c memcpy.c memcmp.c memmove.c memrcpy.c memchr.c)
