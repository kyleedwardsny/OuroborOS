#include <ouroboros/arch/mips/shadow.h>

void k_read_current_pss(struct mips_regstore *regstore)
{
	__asm__(".set noat");
	RDPGPR(regstore->gpr_1.ptr, $1);
	__asm__(".set at");
	RDPGPR(regstore->gpr_2.ptr, $2);
	RDPGPR(regstore->gpr_3.ptr, $3);
	RDPGPR(regstore->gpr_4.ptr, $4);
	RDPGPR(regstore->gpr_5.ptr, $5);
	RDPGPR(regstore->gpr_6.ptr, $6);
	RDPGPR(regstore->gpr_7.ptr, $7);
	RDPGPR(regstore->gpr_8.ptr, $8);
	RDPGPR(regstore->gpr_9.ptr, $9);
	RDPGPR(regstore->gpr_10.ptr, $10);
	RDPGPR(regstore->gpr_11.ptr, $11);
	RDPGPR(regstore->gpr_12.ptr, $12);
	RDPGPR(regstore->gpr_13.ptr, $13);
	RDPGPR(regstore->gpr_14.ptr, $14);
	RDPGPR(regstore->gpr_15.ptr, $15);
	RDPGPR(regstore->gpr_16.ptr, $16);
	RDPGPR(regstore->gpr_17.ptr, $17);
	RDPGPR(regstore->gpr_18.ptr, $18);
	RDPGPR(regstore->gpr_19.ptr, $19);
	RDPGPR(regstore->gpr_20.ptr, $20);
	RDPGPR(regstore->gpr_21.ptr, $21);
	RDPGPR(regstore->gpr_22.ptr, $22);
	RDPGPR(regstore->gpr_23.ptr, $23);
	RDPGPR(regstore->gpr_24.ptr, $24);
	RDPGPR(regstore->gpr_25.ptr, $25);
	RDPGPR(regstore->gpr_26.ptr, $26);
	RDPGPR(regstore->gpr_27.ptr, $27);
	RDPGPR(regstore->gpr_28.ptr, $28);
	RDPGPR(regstore->gpr_29.ptr, $29);
	RDPGPR(regstore->gpr_30.ptr, $30);
	RDPGPR(regstore->gpr_31.ptr, $31);
}

void k_write_current_pss(const struct mips_regstore *regstore)
{
	__asm__(".set noat");
	WRPGPR(regstore->gpr_1.ptr, $1);
	__asm__(".set at");
	WRPGPR(regstore->gpr_2.ptr, $2);
	WRPGPR(regstore->gpr_3.ptr, $3);
	WRPGPR(regstore->gpr_4.ptr, $4);
	WRPGPR(regstore->gpr_5.ptr, $5);
	WRPGPR(regstore->gpr_6.ptr, $6);
	WRPGPR(regstore->gpr_7.ptr, $7);
	WRPGPR(regstore->gpr_8.ptr, $8);
	WRPGPR(regstore->gpr_9.ptr, $9);
	WRPGPR(regstore->gpr_10.ptr, $10);
	WRPGPR(regstore->gpr_11.ptr, $11);
	WRPGPR(regstore->gpr_12.ptr, $12);
	WRPGPR(regstore->gpr_13.ptr, $13);
	WRPGPR(regstore->gpr_14.ptr, $14);
	WRPGPR(regstore->gpr_15.ptr, $15);
	WRPGPR(regstore->gpr_16.ptr, $16);
	WRPGPR(regstore->gpr_17.ptr, $17);
	WRPGPR(regstore->gpr_18.ptr, $18);
	WRPGPR(regstore->gpr_19.ptr, $19);
	WRPGPR(regstore->gpr_20.ptr, $20);
	WRPGPR(regstore->gpr_21.ptr, $21);
	WRPGPR(regstore->gpr_22.ptr, $22);
	WRPGPR(regstore->gpr_23.ptr, $23);
	WRPGPR(regstore->gpr_24.ptr, $24);
	WRPGPR(regstore->gpr_25.ptr, $25);
	WRPGPR(regstore->gpr_26.ptr, $26);
	WRPGPR(regstore->gpr_27.ptr, $27);
	WRPGPR(regstore->gpr_28.ptr, $28);
	WRPGPR(regstore->gpr_29.ptr, $29);
	WRPGPR(regstore->gpr_30.ptr, $30);
	WRPGPR(regstore->gpr_31.ptr, $31);
}
