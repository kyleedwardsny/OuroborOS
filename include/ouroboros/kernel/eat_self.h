#ifndef OUROBOROS_KERNEL_EAT_SELF_H
#define OUROBOROS_KERNEL_EAT_SELF_H

#include <stdarg.h>

extern void k_eat_self(const char *fmt, ...);

extern void vk_eat_self(const char *fmt, va_list args);

extern void k_hang(void);

#endif /* OUROBOROS_KERNEL_EAT_SELF_H */
