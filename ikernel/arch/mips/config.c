#include <ouroboros/arch/mips/ikernel/config.h>
#include <ouroboros/arch/mips/ikernel/entry.h>
#include <ouroboros/arch/mips/cp0.h>
#include <ouroboros/arch/mips/entry.h>
#include <ouroboros/errno.h>
#include <ouroboros/ikernel/config.h>

#include <ouroboros/stdint.h>

CPU_LOCAL_DEFINE(unsigned int, _k_num_tlb_entries);
CPU_LOCAL_DEFINE(unsigned int, _k_num_shadow_sets);
CPU_LOCAL_DEFINE(int, _k_user_local_present);
CPU_LOCAL_DEFINE(int, _k_scratch_present);
CPU_LOCAL_DEFINE(k_exit_fn, _k_exit_function);

void k_read_cpu_config(void)
{
	ou_uint32_t config1;
	ou_uint32_t config3;
	ou_uint32_t config4;
	ou_uint32_t srsctl;
	unsigned int mmu_size;

	MFC0(config1, MIPS_CP0_CONFIG1);

	/* Get the number of TLB entries available */
	mmu_size = (config1 & MIPS_CP0_CONFIG1_MMUSIZE) >> 25;
	if (mmu_size > 0) {
		k_num_tlb_entries = mmu_size + 1;
	}

	MFC0(config3, MIPS_CP0_CONFIG3);

	/* Get status of user-local register */
	if (config3 & MIPS_CP0_CONFIG3_ULRI) {
		k_user_local_present = 1;
	}

	MFC0(config4, MIPS_CP0_CONFIG4);

	/* Get status of KScratch registers */
	if (config4 & MIPS_CP0_CONFIG4_KSCREXIST(2) | MIPS_CP0_CONFIG4_KSCREXIST(3)
			== MIPS_CP0_CONFIG4_KSCREXIST(2) | MIPS_CP0_CONFIG4_KSCREXIST(3)) {
		k_scratch_present = 1;
		k_exit_function = k_exit_scratch;
	} else {
		k_exit_function = k_exit_standard;
	}
}

typedef void (*evt_fn)(void);
