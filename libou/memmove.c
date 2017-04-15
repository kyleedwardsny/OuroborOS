#include <ouroboros/string.h>

void *ou_memmove(void *destination, const void *source, ou_size_t len)
{
	if (destination >= source && destination < source + len) {
		return ou_memrcpy(destination, source, len);
	} else {
		return ou_memcpy(destination, source, len);
	}
}
