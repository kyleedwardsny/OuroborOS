#ifndef OUROBOROS_STDIO_H
#define OUROBOROS_STDIO_H

#include <stdarg.h>
#include <stddef.h>

#include <ouroboros/unistd.h>

int ou_sprintf(char *str, const char *format, ...);

int ou_vsprintf(char *str, const char *format, va_list args);

int _ou_fprintf(ou_ssize_t (*write_cb)(void *cb_data, const void *data, size_t len), void *cb_data, const char *format, ...);

int _ou_vfprintf(ou_ssize_t (*write_cb)(void *cb_data, const void *data, size_t len), void *cb_data, const char *format, va_list args);

#endif /* OUROBOROS_STDIO_H */
