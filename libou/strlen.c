#include <ouroboros/string.h>

extern size_t ou_strlen(const char *str)
{
	const char *end = str;
	while (*end++);

	return end - str - 1;
}
