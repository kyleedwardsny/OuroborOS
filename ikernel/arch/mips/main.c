#include <ouroboros/ikernel/main.h>
#include <ouroboros/ikernel/eat_self.h>

void k_main_args(unsigned long arg0, unsigned long arg1, unsigned long arg2)
{
	const void *fdt;

	switch (arg0) {
	case -2:
		fdt = (const void *) arg1;
		k_main(fdt);

	default:
		k_hang();
	}
}
