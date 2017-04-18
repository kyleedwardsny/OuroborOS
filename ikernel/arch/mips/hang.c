#include <ouroboros/ikernel/eat_self.h>

void k_hang(void)
{
	__asm__("di");
	for (;;) {
		__asm__("wait");
	}
}
