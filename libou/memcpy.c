#include <ouroboros/string.h>

#include <ouroboros/stdint.h>

/* TODO Make this more efficient (word-aligned). We are doing a simple byte-by-
 * byte copy for now.
 */
void *ou_memcpy(void *destination, const void *source, ou_size_t len)
{
	ou_uint8_t *dst_byte = destination;
	const ou_uint8_t *src_byte = source;
	ou_size_t i;

	for (i = 0; i < len; i++) {
		*dst_byte++ = *src_byte++;
	}

	return destination;
}
