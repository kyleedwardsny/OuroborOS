#ifndef OUROBOROS_ARCH_MIPS_IKERNEL_USERSPACE_H
#define OUROBOROS_ARCH_MIPS_IKERNEL_USERSPACE_H

#include <ouroboros/stddef.h>

#define ACCESS_LEVEL_KERNEL	(0)
#define ACCESS_LEVEL_SUPERVISOR	(1)
#define ACCESS_LEVEL_USER	(2)

#define ADDR_IN_RANGE(addr, size, lower, upper)								\
	((addr) >= (lower) && ((addr) < (upper) || (upper) == 0) && (size) <= (upper) - (lower))

static inline int k_access_ok(const void *addr, ou_size_t size, unsigned int access_level)
{
	unsigned long addr_ulong = (unsigned long) addr;

	if (ADDR_IN_RANGE(addr_ulong, size, 0x00000000, 0x80000000)) {
		return access_level <= ACCESS_LEVEL_USER;
	} else if (ADDR_IN_RANGE(addr_ulong, size, 0xC0000000, 0xE0000000)) {
		return access_level <= ACCESS_LEVEL_SUPERVISOR;
	} else if (ADDR_IN_RANGE(addr_ulong, size, 0x80000000, 0xA0000000)
		|| ADDR_IN_RANGE(addr_ulong, size, 0xA0000000, 0xC0000000)
		|| ADDR_IN_RANGE(addr_ulong, size, 0xE0000000, 0x00000000)) {
		return access_level <= ACCESS_LEVEL_KERNEL;
	} else {
		return 0;
	}
}

#define k_get_userspace_window(addr, size)	((void *) (addr))
#define k_put_userspace_window(addr, size)

#endif /* OUROBOROS_ARCH_MIPS_IKERNEL_USERSPACE_H */
