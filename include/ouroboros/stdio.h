#ifndef OUROBOROS_STDIO_H
#define OUROBOROS_STDIO_H

#include <stdarg.h>
#include <stddef.h>

#include <ouroboros/unistd.h>

#ifdef __GNUC__
#define GCC_FORMAT_PRINTF(s, f)	__attribute__((format (printf, s, f)))
#else
#define GCC_FORMAT_PRINTF(s, f)
#endif

int ou_sprintf(char *str, const char *format, ...) GCC_FORMAT_PRINTF(2, 3);

int ou_vsprintf(char *str, const char *format, va_list args) GCC_FORMAT_PRINTF(2, 0);

int _ou_fprintf(ou_ssize_t (*write_cb)(void *cb_data, const void *data, ou_size_t len), void *cb_data, const char *format, ...) GCC_FORMAT_PRINTF(3, 4);

int _ou_vfprintf(ou_ssize_t (*write_cb)(void *cb_data, const void *data, ou_size_t len), void *cb_data, const char *format, va_list args) GCC_FORMAT_PRINTF(3, 0);

#endif /* OUROBOROS_STDIO_H */
