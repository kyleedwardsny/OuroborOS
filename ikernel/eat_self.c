#include <ouroboros/ikernel/eat_self.h>

void k_eat_self(const char *fmt, ...)
{
	va_list vl;

	va_start(vl, fmt);
	vk_eat_self(fmt, vl);
	va_end(vl);
}

void vk_eat_self(const char *fmt, va_list args)
{
	/* TODO Not using arguments for now */
	k_hang();
}
