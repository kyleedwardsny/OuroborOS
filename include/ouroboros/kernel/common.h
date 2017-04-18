#ifndef OUROBOROS_KERNEL_COMMON_H
#define OUROBOROS_KERNEL_COMMON_H

#include <ouroboros/genconfig.h>
#include <ouroboros/arch/current/common.h>

#define CPU_LOCAL_NAME(name)	\
	_cpu_local_##name

#define CPU_LOCAL_DEFINE(type, name)		\
	type CPU_LOCAL_NAME(name)[OU_MAX_CORES]

#define CPU_LOCAL_DECLARE(type, name)		\
	extern CPU_LOCAL_DEFINE(type, name)

#define CPU_LOCAL_ACCESS(name)				\
	((CPU_LOCAL_NAME(name))[k_get_current_cpu()])

#endif /* OUROBOROS_KERNEL_COMMON_H */
