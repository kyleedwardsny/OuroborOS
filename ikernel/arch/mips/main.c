#include <ouroboros/ikernel/main.h>
#include <ouroboros/ikernel/eat_self.h>

#include <ouroboros/arch/mips/ikernel/config.h>
#include <ouroboros/arch/mips/ikernel/entry.h>
#include <ouroboros/arch/mips/cp0.h>
#include <ouroboros/arch/mips/context.h>

#include <ouroboros/errno.h>
#include <ouroboros/stdint.h>
#include <ouroboros/string.h>

CPU_LOCAL_DEFINE(struct ou_context, _k_context) __attribute__((section(".bss.ctx")));

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

static int syscall_advance_pc(ou_uint32_t cause)
{
	int retval = -OU_ERR_UNKNOWN;
	unsigned long pc;
	ou_uint32_t instr;
	unsigned int rs;
	long offset;

	MFC0(pc, MIPS_CP0_EPC);

	if (cause & MIPS_CP0_CAUSE_BD) {
		MFC0(instr, MIPS_CP0_BADINSTRP);

		switch (instr & MIPS_INSTR_OPCODE) {
		case MIPS_INSTR_OPCODE_SPECIAL:
			switch (instr & MIPS_INSTR_SPECIAL_OPCODE) {
			case MIPS_INSTR_SPECIAL_JR:
			case MIPS_INSTR_SPECIAL_JALR:
				rs = (instr & MIPS_INSTR_RS) >> 21;
				pc = k_context.gpr.by_index[rs].u;
				break;

			default:
				retval = -OU_ERR_UNKNOWN;
				goto ret;
			}
			break;

		case MIPS_INSTR_OPCODE_REGIMM:
			switch (instr & MIPS_INSTR_REGIMM_OPCODE) {
			case MIPS_INSTR_REGIMM_BGEZ:
			case MIPS_INSTR_REGIMM_BGEZAL:
				offset = (short) (instr & MIPS_INSTR_OFFSET);
				pc += offset << 2;
				break;

			default:
				retval = -OU_ERR_UNKNOWN;
				goto ret;
			}
			break;

		case MIPS_INSTR_OPCODE_J:
		case MIPS_INSTR_OPCODE_JAL:
		case MIPS_INSTR_OPCODE_JALX:
			pc &= ~MIPS_INSTR_J_INDEX << 2;
			pc |= (instr & MIPS_INSTR_J_INDEX) << 2;
			break;

		case MIPS_INSTR_OPCODE_BEQ:
		case MIPS_INSTR_OPCODE_BNE:
		case MIPS_INSTR_OPCODE_BLEZ:
		case MIPS_INSTR_OPCODE_BGTZ:
		case MIPS_INSTR_OPCODE_BEQL:
		case MIPS_INSTR_OPCODE_BNEL:
		case MIPS_INSTR_OPCODE_BLEZL:
		case MIPS_INSTR_OPCODE_BGTZL:
			offset = (short) (instr & MIPS_INSTR_OFFSET);
			pc += offset << 2;
			break;

		case MIPS_INSTR_OPCODE_COP1:
		case MIPS_INSTR_OPCODE_COP2:
			switch (instr & MIPS_INSTR_COP_BC) {
			case MIPS_INSTR_COP_BC:
				offset = (short) (instr & MIPS_INSTR_OFFSET);
				pc += offset << 2;
				break;

			default:
				retval = -OU_ERR_UNKNOWN;
				goto ret;
			}
			break;

		default:
			retval = -OU_ERR_UNKNOWN;
			goto ret;
		}
	} else { /* Simpler case, just advance PC by 4 */
		pc += 4;
	}

	MTC0(pc, MIPS_CP0_EPC);

	retval = -OU_ERR_SUCCESS;
ret:
	return retval;
}

void k_entry(void)
{
	ou_uint32_t cause;
	ou_uint32_t instr;

	MFC0(cause, MIPS_CP0_CAUSE);

	switch (cause & MIPS_CP0_CAUSE_EXC) {
	case MIPS_CP0_CAUSE_EXC_SYS:
		MFC0(instr, MIPS_CP0_BADINSTR);
		k_do_syscall(&k_context,
				(instr & BITS(25, 6)) >> 6,
				k_context.gpr.by_name.a0.u,
				k_context.gpr.by_name.a1.u,
				k_context.gpr.by_name.a2.u,
				k_context.gpr.by_name.a3.u,
				k_context.gpr.by_name.s0.u,
				k_context.gpr.by_name.s1.u,
				k_context.gpr.by_name.s2.u,
				k_context.gpr.by_name.s3.u);
		syscall_advance_pc(cause);
		break;
	}
}

void k_exit(void)
{
	k_exit_policy();
}

int k_enter_initrd(void *start, void *end, void *load_addr, void *entry_addr)
{
	int retval = -OU_ERR_UNKNOWN;
	ou_size_t length = end - start;
	ou_uint32_t index;
	ou_uint32_t entry_lo;
	ou_uint32_t entry_ho;
	struct ou_context context;
	ou_size_t i;

	if (!IS_PAGE_ALIGNED((ou_size_t) start) || !IS_PAGE_ALIGNED((ou_size_t) load_addr)) {
		retval = -OU_ERR_INVALID_ARGUMENT;
		goto ret;
	}

	if (entry_addr < load_addr || entry_addr >= load_addr + PAGE_SIZE) {
		retval = -OU_ERR_INVALID_ARGUMENT;
		goto ret;
	}

	index = (k_num_tlb_entries - 1) & MIPS_CP0_INDEX_INDEX;
	MTC0(index, MIPS_CP0_INDEX);

	entry_lo = MIPS_CP0_ENTRY_LO_PFN_PFN(((ou_size_t) start) & ~0xC0000000) | MIPS_CP0_ENTRY_LO_C_C(MIPS_CP0_CACHE_ATTR_U) | MIPS_CP0_ENTRY_LO_D | MIPS_CP0_ENTRY_LO_V;
	MTC0(entry_lo, MIPS_CP0_ENTRY_LO0);
	entry_ho = MIPS_CP0_ENTRY_HO_VPN2_VPN2((ou_size_t) load_addr) | MIPS_CP0_ENTRY_HO_ASID_ASID(1);
	MTC0(entry_ho, MIPS_CP0_ENTRY_HO);
	MTC0(MIPS_CP0_PAGE_MASK_MASK_4K, MIPS_CP0_PAGE_MASK);

	TLBWI();

	context.mask_0 = CTX_MASK_0_PC | CTX_MASK_0_HI | CTX_MASK_0_LO | CTX_MASK_0_PC;
	context.mask_regs = BITS(31, 1);

	context.pc = entry_addr;
	for (i = 1; i < 32; i++) {
		context.gpr.by_index[i].u = 0;
	}
	context.asid = 1;

	k_load_new_context(&context);

	k_exit();

	retval = -OU_ERR_SUCCESS;
ret:
	return retval;
}
