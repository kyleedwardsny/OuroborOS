#include <ouroboros/string.h>

#include <ouroboros/stdint.h>

void *ou_memchr(const void *ptr, int value, ou_size_t len)
{
	ou_uint8_t *bptr = (ou_uint8_t *) ptr;

	while (bptr < (ou_uint8_t *) ptr + len) {
		if (*bptr == value) {
			return bptr;
		}
		bptr++;
	}

	return NULL;
}
