#include <ouroboros/string.h>

ou_size_t ou_strnlen(const char *str, ou_size_t len)
{
	const char *end = str;
	while (end < str + len && *end) {
		end++;
	}

	return end - str;
}
