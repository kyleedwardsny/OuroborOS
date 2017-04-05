#include <ouroboros/hw/uart/16550.h>
#include <ouroboros/arch/mips/cp0.h>
#include <ouroboros/arch/mips/uhi.h>
#include <ouroboros/common.h>
#include <ouroboros/stdint.h>
#include <ouroboros/stdlib.h>
#include <ouroboros/string.h>

#define CMDLINE_ARGV_BUF_LENGTH	(8192)
#define CMDLINE_ARGV_LENGTH	(512)

static char cmdline_argv_buf[CMDLINE_ARGV_BUF_LENGTH];

static int cmdline_argc;
static char *cmdline_argv[CMDLINE_ARGV_LENGTH];

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

static int num_tlb_pages = -1;

static int check_entry_lo_validity(ou_uint32_t entry_lo)
{
	if (entry_lo & BITS(31, 26)) {
		return -1;
	}

	switch (entry_lo & MIPS_CP0_ENTRY_LO_C) {
	case MIPS_CP0_ENTRY_LO_C_CNWTN:
	case MIPS_CP0_ENTRY_LO_C_U:
	case MIPS_CP0_ENTRY_LO_C_CNWBA:
	case MIPS_CP0_ENTRY_LO_C_UA:
		break;

	default:
		return -1;
	}

	return 0;
}

static int check_tlb_entry_validity(int index, const struct mips_tlb_entry *entry)
{
	int err;

	if (index >= num_tlb_pages) {
		return -1;
	}

	if ((err = check_entry_lo_validity(entry->entry_lo0)) < 0) {
		return err;
	}

	if ((err = check_entry_lo_validity(entry->entry_lo1)) < 0) {
		return err;
	}

	if (entry->entry_ho & BITS(12, 8)) {
		return -1;
	}

	switch (entry->page_mask & MIPS_CP0_PAGE_MASK_MASK) {
	case MIPS_CP0_PAGE_MASK_MASK_4K:
	case MIPS_CP0_PAGE_MASK_MASK_16K:
	case MIPS_CP0_PAGE_MASK_MASK_64K:
	case MIPS_CP0_PAGE_MASK_MASK_256K:
	case MIPS_CP0_PAGE_MASK_MASK_1M:
	case MIPS_CP0_PAGE_MASK_MASK_4M:
	case MIPS_CP0_PAGE_MASK_MASK_16M:
	case MIPS_CP0_PAGE_MASK_MASK_64M:
	case MIPS_CP0_PAGE_MASK_MASK_256M:
		break;

	default:
		return -1;
	}

	return 0;
}

static int set_tlb_entry(int index, const struct mips_tlb_entry *entry)
{
	int err;

	if ((err = check_tlb_entry_validity(index, entry)) < 0) {
		return err;
	}

	MTC0(entry->entry_lo0, MIPS_CP0_ENTRY_LO0);
	MTC0(entry->entry_lo1, MIPS_CP0_ENTRY_LO1);
	MTC0(entry->entry_ho, MIPS_CP0_ENTRY_HO);
	MTC0(entry->page_mask, MIPS_CP0_PAGE_MASK);

	if (index < 0) { /* Random index */
		TLBWR();
	} else {
		MTC0(MIPS_CP0_INDEX_INDEX_INDEX(index), MIPS_CP0_INDEX);
		TLBWI();
	}

	return 0;
}

void k_hang(void)
{
	for (;;);
}

void k_main(void)
{
	ou_uint32_t config1;
	unsigned int mmu_size;
	struct mips_tlb_entry tlb_entry;
	ou_uint32_t index;
	ou_uint32_t status;
	ou_uint32_t *write = (ou_uint32_t *) 0x86000000;
	ou_uint32_t *read = (ou_uint32_t *) 0x05000000;

	MFC0(config1, MIPS_CP0_CONFIG1);

	mmu_size = (config1 & MIPS_CP0_CONFIG1_MMUSIZE) >> 25;
	if (mmu_size > 0) {
		num_tlb_pages = mmu_size + 1;
	} else {
		k_hang();
	}

	tlb_entry.entry_lo0 = MIPS_CP0_ENTRY_LO_PFN_PFN(0x06000000) | MIPS_CP0_ENTRY_LO_C_U | MIPS_CP0_ENTRY_LO_V;
	tlb_entry.entry_lo1 = 0; /* Not valid */
	tlb_entry.entry_ho = MIPS_CP0_ENTRY_HO_VPN2_VPN2(0x05000000) | MIPS_CP0_ENTRY_HO_ASID_ASID(12);
	tlb_entry.page_mask = MIPS_CP0_PAGE_MASK_MASK_4K;

	set_tlb_entry(-1, &tlb_entry);

	MFC0(status, MIPS_CP0_STATUS);
	status &= ~(MIPS_CP0_STATUS_ERL | MIPS_CP0_STATUS_EXL | MIPS_CP0_STATUS_KSU);
	status |= MIPS_CP0_STATUS_KSU_K;
	MTC0(status, MIPS_CP0_STATUS);

	MTC0(MIPS_CP0_ENTRY_HO_ASID_ASID(12), MIPS_CP0_ENTRY_HO);

	*write = 0xDEADBEA7;
	if (*read == 0xDEADBEA7) {
		k_puts("Write success");
	} else {
		k_puts("Write failure");
	}

	MTC0(MIPS_CP0_ENTRY_HO_ASID_ASID(11), MIPS_CP0_ENTRY_HO);

	*write = 0xDEADBEA7;
	if (*read == 0xDEADBEA7) {
		k_puts("Write success");
	} else {
		k_puts("Write failure");
	}
}
