#ifndef OUROBOROS_IKERNEL_EAT_SELF_H
#define OUROBOROS_IKERNEL_EAT_SELF_H

#include <stdarg.h>

void k_eat_self(const char *fmt, ...);

void vk_eat_self(const char *fmt, va_list args);

void k_hang(void);

#endif /* OUROBOROS_IKERNEL_EAT_SELF_H */
