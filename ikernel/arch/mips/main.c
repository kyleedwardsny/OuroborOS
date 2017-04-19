#include <ouroboros/ikernel/main.h>
#include <ouroboros/ikernel/eat_self.h>

#include <ouroboros/arch/mips/ikernel/config.h>
#include <ouroboros/arch/mips/ikernel/entry.h>
#include <ouroboros/arch/mips/cp0.h>

#include <ouroboros/stdint.h>
#include <ouroboros/string.h>

CPU_LOCAL_DEFINE(struct mips_regstore, _k_regstore) __attribute__((section(".bss.regstore")));

void k_main_args(unsigned long arg0, unsigned long arg1, unsigned long arg2)
{
	const void *fdt;

	switch (arg0) {
	case -2:
		fdt = (const void *) arg1;
		k_main(fdt);

	default:
		k_hang();
	}
}

void k_entry(void)
{
	ou_uint32_t cause;
	struct ou_context context;

	ou_memcpy(&context.registers, &k_regstore, sizeof(context.registers));

	MFC0(cause, MIPS_CP0_CAUSE);

	switch (cause & MIPS_CP0_CAUSE_EXC) {
	case MIPS_CP0_CAUSE_EXC_SYS:
		k_do_syscall(&context,
				context.registers.gpr_2.u,	/* $v0 = index */
				context.registers.gpr_4.u,	/* $a0 = argument 0 */
				context.registers.gpr_5.u,	/* $a1 = argument 1 */
				context.registers.gpr_6.u,	/* $a2 = argument 2 */
				context.registers.gpr_7.u,	/* $a3 = argument 3 */
				context.registers.gpr_16.u,	/* $s0 = argument 4 */
				context.registers.gpr_17.u,	/* $s1 = argument 4 */
				context.registers.gpr_18.u,	/* $s2 = argument 4 */
				context.registers.gpr_19.u);	/* $s3 = argument 4 */
		break;
	}
}

void k_exit(void)
{
	k_exit_policy();
}
