#include <ouroboros/string.h>

#include <ouroboros/stdint.h>

int ou_memcmp(const void *ptr1, const void *ptr2, ou_size_t len)
{
	const ou_uint8_t *bptr1 = ptr1;
	const ou_uint8_t *bptr2 = ptr2;
	ou_size_t i;

	for (i = 0; i < len; i++) {
		if (*bptr1 != *bptr2) {
			return *bptr1 - *bptr2;
		}
		bptr1++;
		bptr2++;
	}

	return 0;
}
