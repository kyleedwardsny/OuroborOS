#include <ouroboros/hw/uart/16550.h>
#include <ouroboros/arch/mips/cp0.h>
#include <ouroboros/common.h>
#include <ouroboros/stdint.h>

static struct uart_16550 *uart = (struct uart_16550 *) 0x940003F8;

static void k_putchar(char c)
{
	while (!(uart->lsr & UART_16550_LSR_THRE));
	uart->port0.rbr = c;
}

static void k_puts(const char *str)
{
	while (*str) {
		k_putchar(*str++);
	}
	k_putchar('\n');
}

void k_main(void)
{
	ou_uint32_t pagemask = MIPS_CP0_PAGE_MASK_MASK_4K;
	ou_uint32_t index = MIPS_CP0_INDEX_INDEX_INDEX(3);
	ou_uint32_t entrylo =
		MIPS_CP0_ENTRY_LO_PFN_PFN(0x6000000) |
		MIPS_CP0_ENTRY_LO_C_U |
		MIPS_CP0_ENTRY_LO_V |
		MIPS_CP0_ENTRY_LO_D |
		MIPS_CP0_ENTRY_LO_G;
	ou_uint32_t entryho =
		MIPS_CP0_ENTRY_HO_VPN2_VPN2(0x5000000);
	ou_uint32_t status;

	MTC0(pagemask, MIPS_CP0_PAGE_MASK);
	MTC0(entrylo, MIPS_CP0_ENTRY_LO0);
	MTC0(entrylo, MIPS_CP0_ENTRY_LO1);
	MTC0(entryho, MIPS_CP0_ENTRY_HO);
	MTC0(MIPS_CP0_INDEX_INDEX_INDEX(3), MIPS_CP0_INDEX);
	MFC0(index, MIPS_CP0_INDEX);
	if ((index & MIPS_CP0_INDEX_INDEX) != MIPS_CP0_INDEX_INDEX_INDEX(3)) {
		k_puts("Uh-oh, something has gone awry");
	}
	TLBWI();

	MTC0(MIPS_CP0_ENTRY_HO_VPN2_VPN2(0x5000000), MIPS_CP0_ENTRY_HO);
	MTC0(MIPS_CP0_INDEX_INDEX_INDEX(24), MIPS_CP0_INDEX);
	TLBP();
	MFC0(index, MIPS_CP0_INDEX);

	if ((index & MIPS_CP0_INDEX_P) || (index & MIPS_CP0_INDEX_INDEX) != MIPS_CP0_INDEX_INDEX_INDEX(3)) {
		k_puts("TLBP unsuccessful");
	} else {
		k_puts("TLBP successful");
	}

	MFC0(status, MIPS_CP0_STATUS);
	status &= ~(MIPS_CP0_STATUS_ERL | MIPS_CP0_STATUS_EXL);
	status &= ~MIPS_CP0_STATUS_KSU;
	status |= MIPS_CP0_STATUS_KSU_K;
	MTC0(status, MIPS_CP0_STATUS);

	ou_uint32_t *write = 0x5000000, *read = 0x86000000;
	*write = 0xCAFEBABE;
	if ((*read) == 0xCAFEBABE) {
		k_puts("Read/write successful");
	} else {
		k_puts("Read/write unsuccessful");
	}
}
