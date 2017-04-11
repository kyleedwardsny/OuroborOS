#include <ouroboros/stdio.h>

int ou_sprintf(char *str, const char *format, ...)
{
	int retval;
	va_list args;

	va_start(args, format);
	retval = ou_vsprintf(str, format, args);
	va_end(args);

	return retval;
}
