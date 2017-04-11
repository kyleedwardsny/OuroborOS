#include <ouroboros/string.h>

const char *ou_strchr(const char *str, int character)
{
	while (*str) {
		if (*str == character) {
			return str;
		}
		str++;
	}

	return NULL;
}
