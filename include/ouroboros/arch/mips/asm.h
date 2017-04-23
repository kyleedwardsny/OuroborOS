#ifndef OUROBOROS_ARCH_MIPS_ASM_H
#define OUROBOROS_ARCH_MIPS_ASM_H

#include <ouroboros/common.h>

#define MIPS_CP_STR(r, s)	CPP_STR(r) ", " CPP_STR(s)

#define MTC0_OP(op, expr, reg, select)										\
do {														\
	__asm__ volatile(CPP_STR(op) " %[mips_reg], " MIPS_CP_STR(reg, select) : : [mips_reg] "r" (expr));	\
} while (0)

#define MFC0_OP(op, var, reg, select)										\
do {														\
	__asm__ volatile(CPP_STR(op) " %[mips_reg], " MIPS_CP_STR(reg, select) : [mips_reg] "=r" (var) :);	\
} while (0)

#define MTC0_R(expr, reg, select)	MTC0_OP(mtc0, expr, reg, select)
#define MTC0(expr, reg)			MTC0_R(expr, reg)

#define MFC0_R(var, reg, select)	MFC0_OP(mfc0, var, reg, select)
#define MFC0(var, reg)			MFC0_R(var, reg)

#define DMTC0_R(expr, reg, select)	MTC0_OP(dmtc0, expr, reg, select)
#define DMTC0(expr, reg)		DMTC0_R(expr, reg)

#define DMFC0_R(var, reg, select)	MFC0_OP(dmfc0, var, reg, select)
#define DMFC0(var, reg)			DMFC0_R(var, reg)

#define TLBR()				\
do {					\
	__asm__ volatile("tlbr" : :);	\
} while (0)

#define TLBWI()				\
do {					\
	__asm__ volatile("tlbwi" : :);	\
} while (0)

#define TLBWR()				\
do {					\
	__asm__ volatile("tlbwr" : :);	\
} while (0)

#define TLBP()				\
do {					\
	__asm__ volatile("tlbp" : :);	\
} while (0)

#define MTHI(expr)							\
do {									\
	__asm__ volatile("mthi %[mips_reg]" : : [mips_reg] "r" (expr));	\
} while (0)

#define MFHI(var)							\
do {									\
	__asm__ volatile("mfhi %[mips_reg]" : [mips_reg] "=r" (var) :);	\
} while (0)

#define MTLO(expr)							\
do {									\
	__asm__ volatile("mtlo %[mips_reg]" : : [mips_reg] "r" (expr));	\
} while (0)

#define MFLO(var)							\
do {									\
	__asm__ volatile("mflo %[mips_reg]" : [mips_reg] "=r" (var) :);	\
} while (0)

#define RDPGPR(var, reg)									\
do {												\
	__asm__ volatile("rdpgpr %[mips_reg], " CPP_STR(reg) : [mips_reg] "=r" (var) :);	\
} while (0)

#define WRPGPR(expr, reg)										\
do {													\
	__asm__ volatile("wrpgpr %[mips_reg], " CPP_STR(reg) : : [mips_reg] "r" (expr) :);	\
} while (0)

#define MIPS_INSTR_RS			BITS(25, 21)

#define MIPS_INSTR_OPCODE		BITS(31, 26)

#define MIPS_INSTR_OPCODE_SPECIAL	(0x00 << 26)
#define MIPS_INSTR_OPCODE_REGIMM	(0x01 << 26)
#define MIPS_INSTR_OPCODE_J		(0x02 << 26)
#define MIPS_INSTR_OPCODE_JAL		(0x03 << 26)
#define MIPS_INSTR_OPCODE_BEQ		(0x04 << 26)
#define MIPS_INSTR_OPCODE_BNE		(0x05 << 26)
#define MIPS_INSTR_OPCODE_BLEZ		(0x06 << 26)
#define MIPS_INSTR_OPCODE_BGTZ		(0x07 << 26)
#define MIPS_INSTR_OPCODE_COP1		(0x11 << 26)
#define MIPS_INSTR_OPCODE_COP2		(0x12 << 26)
#define MIPS_INSTR_OPCODE_BEQL		(0x14 << 26)
#define MIPS_INSTR_OPCODE_BNEL		(0x15 << 26)
#define MIPS_INSTR_OPCODE_BLEZL		(0x16 << 26)
#define MIPS_INSTR_OPCODE_BGTZL		(0x17 << 26)
#define MIPS_INSTR_OPCODE_JALX		(0x1D << 26)

#define MIPS_INSTR_SPECIAL_OPCODE	BITS(5, 0)

#define MIPS_INSTR_SPECIAL_JR		(0x08 << 0)
#define MIPS_INSTR_SPECIAL_JALR		(0x09 << 0)

#define MIPS_INSTR_REGIMM_OPCODE	BITS(20, 16)

#define MIPS_INSTR_REGIMM_BGEZ		(0x01 << 16)
#define MIPS_INSTR_REGIMM_BGEZAL	(0x11 << 16)

#define MIPS_INSTR_COP			BITS(25, 21)

#define MIPS_INSTR_COP_BC		(0x08 << 21)

#define MIPS_INSTR_OFFSET		BITS(15, 0)

#define MIPS_INSTR_J_INDEX		BITS(25, 0)

#endif /* OUROBOROS_ARCH_MIPS_ASM_H */
