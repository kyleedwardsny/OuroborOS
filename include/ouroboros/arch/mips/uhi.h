#ifndef OUROBOROS_ARCH_MIPS_UHI_H
#define OUROBOROS_ARCH_MIPS_UHI_H

#include <ouroboros/stdint.h>

ou_int32_t uhi_argc(void);

ou_int32_t uhi_argnlen(ou_int32_t n);

ou_int32_t uhi_argn(ou_int32_t n, char *buf);

#endif /* OUROBOROS_ARCH_MIPS_UHI_H */
