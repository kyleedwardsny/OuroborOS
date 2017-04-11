#include <ouroboros/stdio.h>

int _ou_fprintf(ou_ssize_t (*write_cb)(void *cb_data, const void *data, size_t len), void *cb_data, const char *format, ...)
{
	va_list args;
	int retval;

	va_start(args, format);
	retval = _ou_vfprintf(write_cb, cb_data, format, args);
	va_end(args);

	return retval;
}
