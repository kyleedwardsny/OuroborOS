#include <ouroboros/common.h>
#include <ouroboros/errno.h>

#include <ouroboros/ikernel/config.h>
#include <ouroboros/ikernel/eat_self.h>
#include <ouroboros/ikernel/main.h>
#include <ouroboros/ikernel/mmu.h>

#include <ouroboros/stdio.h>
#include <ouroboros/stdint.h>
#include <ouroboros/stdlib.h>
#include <ouroboros/string.h>

#include <libfdt.h>

const void *initrd_start;
const void *initrd_end;

static int get_pointer(const void *fdt, int node, const char *propname, const void **pointer)
{
	int retval = -OU_ERR_UNKNOWN;
	const void *prop;
	int proplen;

	if (!(prop = fdt_getprop(fdt, node, propname, &proplen))) {
		retval = -OU_ERR_INVALID_ARGUMENT;
		goto ret;
	}

	if (proplen != sizeof(*pointer)) {
		retval = -OU_ERR_INVALID_ARGUMENT;
		goto ret;
	}

	switch (sizeof(*pointer)) {
	case 2:
		*pointer = (const void *) BTON16(*(const ou_uint16_t *) prop);
		break;

	case 4:
		*pointer = (const void *) BTON32(*(const ou_uint32_t *) prop);
		break;

	case 8:
		*pointer = (const void *) BTON64(*(const ou_uint64_t *) prop);
		break;
	}

	retval = -OU_ERR_SUCCESS;
ret:
	return retval;
}

static int read_fdt(const void *fdt)
{
	int retval = -OU_ERR_UNKNOWN;
	int err;
	int chosen;
	const void *prop;
	int proplen;

	if (fdt_check_header(fdt) < 0) {
		retval = -OU_ERR_INVALID_ARGUMENT;
		goto ret;
	}

	if ((chosen = fdt_path_offset(fdt, "/chosen")) < 0) {
		retval = -OU_ERR_INVALID_ARGUMENT;
		goto ret;
	}

	if ((err = get_pointer(fdt, chosen, "linux,initrd-start", &initrd_start)) < 0) {
		retval = err;
		goto ret;
	}

	if ((err = get_pointer(fdt, chosen, "linux,initrd-end", &initrd_end)) < 0) {
		retval = err;
		goto ret;
	}

	retval = -OU_ERR_SUCCESS;
ret:
	return retval;
}

void k_main(const void *fdt)
{
	if (read_fdt(fdt) < 0) {
		k_hang();
	}

	k_read_cpu_config();
	k_clear_tlb();

	/* TODO */
}

void k_do_syscall(struct ou_context *context,
		unsigned long index,
		unsigned long arg0,
		unsigned long arg1,
		unsigned long arg2,
		unsigned long arg3,
		unsigned long arg4,
		unsigned long arg5,
		unsigned long arg6,
		unsigned long arg7)
{
}
