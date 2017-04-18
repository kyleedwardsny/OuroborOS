#include "config.h"

#include <ouroboros/arch/mips/cp0.h>
#include <ouroboros/arch/mips/entry.h>
#include <ouroboros/errno.h>
#include <ouroboros/kernel/config.h>

#include <ouroboros/stdint.h>

CPU_LOCAL_DEFINE(unsigned int, _k_num_tlb_entries);
CPU_LOCAL_DEFINE(unsigned int, _k_num_shadow_sets);
CPU_LOCAL_DEFINE(int, _k_user_local_present);
CPU_LOCAL_DEFINE(unsigned int, _k_entry_policy);
CPU_LOCAL_DEFINE(unsigned int, _k_available_entry_policies);

void k_read_cpu_config(void)
{
	ou_uint32_t config1;
	ou_uint32_t config3;
	ou_uint32_t srsctl;
	unsigned int mmu_size;

	k_available_entry_policies =
		(0x1 << ENTRY_POLICY_K0_K1) |
		(0x1 << ENTRY_POLICY_K0_ROTR) |
		(0x1 << ENTRY_POLICY_K1_ROTR);

	MFC0(config1, MIPS_CP0_CONFIG1);

	/* Get the number of TLB entries available */
	mmu_size = (config1 & MIPS_CP0_CONFIG1_MMUSIZE) >> 25;
	if (mmu_size > 0) {
		k_num_tlb_entries = mmu_size + 1;
	}

	MFC0(srsctl, MIPS_CP0_SRSCTL);

	/* Get the number of shadow register sets available */
	k_num_shadow_sets = (srsctl & MIPS_CP0_SRSCTL_HSS) >> 26;
	if (k_num_shadow_sets > 0) {
		k_available_entry_policies |= (0x1 << ENTRY_POLICY_SHADOW);
	}

	MFC0(config3, MIPS_CP0_CONFIG3);

	/* Get status of user-local register */
	if (config3 & MIPS_CP0_CONFIG3_ULRI) {
		k_user_local_present = 1;
		k_available_entry_policies |=
			(0x1 << ENTRY_POLICY_K0_UL) |
			(0x1 << ENTRY_POLICY_K1_UL) |
			(0x1 << ENTRY_POLICY_UL_ROTR);
	}
}

int k_set_entry_policy(unsigned int entry_policy)
{
	int retval = -OU_ERR_UNKNOWN;

	if (k_available_entry_policies & (0x1 << entry_policy)) {
		k_entry_policy = entry_policy;
	} else {
		retval = -OU_ERR_INVALID_ARGUMENT;
		goto ret;
	}

	retval = -OU_ERR_SUCCESS;
ret:
	return retval;
}
