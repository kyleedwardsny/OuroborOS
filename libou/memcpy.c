#include <ouroboros/string.h>

#include <ouroboros/stdint.h>

/* TODO Make this more efficient (word-aligned). We are doing a simple byte-by-
 * byte copy for now.
 */
void *ou_memcpy(void *destination, const void *source, ou_size_t num)
{
	ou_uint8_t *dst_byte = destination;
	const ou_uint8_t *src_byte = source;

	while ((const void *) src_byte < source + num) {
		*dst_byte++ = *src_byte++;
	}

	return destination;
}
