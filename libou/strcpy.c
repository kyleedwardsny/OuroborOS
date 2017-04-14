#include <ouroboros/string.h>

char *ou_strcpy(char *dst, const char *src)
{
	char *dst2 = dst;

	do {
		*dst2++ = *src;
	} while (*src++);

	return dst;
}
