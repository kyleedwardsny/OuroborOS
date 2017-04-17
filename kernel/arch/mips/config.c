#include <ouroboros/arch/mips/cp0.h>
#include <ouroboros/kernel/config.h>

#include <ouroboros/stdint.h>

unsigned int k_num_tlb_entries = 0;

int k_use_shadow_sets = 0;

unsigned int k_num_shadow_sets = 0;

unsigned int k_kernel_shadow_set = 0;

unsigned int k_user_shadow_set = 0;

int k_user_local_present = 0;

void k_read_cpu_config(void)
{
	ou_uint32_t config1;
	ou_uint32_t config3;
	ou_uint32_t srsctl;
	unsigned int mmu_size;

	MFC0(config1, MIPS_CP0_CONFIG1);

	/* Get the number of TLB entries available */
	mmu_size = (config1 & MIPS_CP0_CONFIG1_MMUSIZE) >> 25;
	if (mmu_size > 0) {
		k_num_tlb_entries = mmu_size + 1;
	}

	MFC0(srsctl, MIPS_CP0_SRSCTL);

	/* Get the number of shadow register sets available */
	k_num_shadow_sets = (srsctl & MIPS_CP0_SRSCTL_HSS) >> 26;

	/* Get the current shadow set */
	k_kernel_shadow_set = (srsctl & MIPS_CP0_SRSCTL_CSS) >> 0;

	if (k_num_shadow_sets > 0) {
		k_use_shadow_sets = 1;
		k_user_shadow_set = 1;
	} else {
		k_use_shadow_sets = 0;
		k_user_shadow_set = 0;
	}

	MFC0(config3, MIPS_CP0_CONFIG3);

	/* Get status of user-local register */
	if (config3 & MIPS_CP0_CONFIG3_ULRI) {
		k_user_local_present = 1;
	} else {
		k_user_local_present = 0;
	}
}
