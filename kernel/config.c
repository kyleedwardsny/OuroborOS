#include <ouroboros/arch/mips/cp0.h>
#include <ouroboros/kernel/config.h>

#include <ouroboros/stdint.h>

unsigned int k_num_tlb_entries = 0;

void k_read_cpu_config(void)
{
	ou_uint32_t config1;
	unsigned int mmu_size;

	MFC0(config1, MIPS_CP0_CONFIG1);

	/* Get the number of TLB entries available */
	mmu_size = (config1 & MIPS_CP0_CONFIG1_MMUSIZE) >> 25;
	if (mmu_size > 0) {
		k_num_tlb_entries = mmu_size + 1;
	}
}
