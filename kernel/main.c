#include <ouroboros/arch/mips/cp0.h>
#include <ouroboros/common.h>
#include <ouroboros/fdt.h>
#include <ouroboros/hw/uart/16550.h>
#include <ouroboros/kernel/eat_self.h>
#include <ouroboros/stdio.h>
#include <ouroboros/stdlib.h>
#include <ouroboros/string.h>

#include <stdint.h>

static int k_putchar(struct uart_16550 *uart, int c)
{
	while (!(uart->lsr & UART_16550_LSR_THRE));
	uart->port0.rbr = c;
	return c;
}

static ou_ssize_t k_write(void *cb_data, const void *data, size_t len)
{
	struct uart_16550 *uart = cb_data;
	size_t i;
	const uint8_t *bytes = data;

	for (i = 0; i < len; i++) {
		k_putchar(uart, bytes[i]);
	}

	return len;
}

static int vk_printf(const char *format, va_list args)
{
	struct uart_16550 *uart = (struct uart_16550 *) 0x940003F8;

	return _ou_vfprintf(k_write, uart, format, args);
}

static int k_printf(const char *format, ...)
{
	int retval;
	va_list args;

	va_start(args, format);
	retval = vk_printf(format, args);
	va_end(args);

	return retval;
}

static int num_tlb_pages = -1;

static int check_entry_lo_validity(uint32_t entry_lo)
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

void k_main(void);

void k_main_args(long arg0, unsigned long arg1, unsigned long arg2)
{
	struct ou_fdt_header *header;

	switch (arg0) {
	case -2:
		header = (struct ou_fdt_header *) arg1;
		if (ou_fdt_check_header(header) < 0) {
			k_printf("Invalid FDT header\n");
		} else {
			k_printf("Valid FDT header\n");
		}
		break;

	default:
		k_printf("Must pass an FDT\n");
	}

	k_main();
}

void k_main(void)
{
	uint32_t config1;
	unsigned int mmu_size;

	char buf[] = "abcdefghijklmnopqrstuvwxyz";

	MFC0(config1, MIPS_CP0_CONFIG1);

	/* Get the number of TLB entries available */
	mmu_size = (config1 & MIPS_CP0_CONFIG1_MMUSIZE) >> 25;
	if (mmu_size > 0) {
		num_tlb_pages = mmu_size + 1;
	} else {
		k_eat_self("Must have at least 1 TLB page");
	}

	k_printf("%p\n", 0775);
}
