#include <ouroboros/stdio.h>
#include <ouroboros/string.h>

static ou_ssize_t write_str(void *cb_data, const void *data, size_t len)
{
	ou_memcpy(*(char **) cb_data, data, len);
	(*(char **) cb_data) += len;
	return len;
}

int ou_vsprintf(char *str, const char *format, va_list args)
{
	int result;

	result = _ou_vfprintf(write_str, &str, format, args);
	if (result > 0) {
		str[result] = '\0';
	}

	return result;
}
