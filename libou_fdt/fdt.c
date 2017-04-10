#include <ouroboros/fdt.h>
#include <ouroboros/common.h>

int ou_fdt_check_header(const struct ou_fdt_header *header)
{
	if (BTON32(header->magic) != 0xD00DFEED) {
		return -1;
	}
	return 0;
}
