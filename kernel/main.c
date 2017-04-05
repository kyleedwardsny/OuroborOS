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

void k_load_cmdline(int op, unsigned long arg1, unsigned long arg2)
{
	ou_size_t i;
	ou_size_t next_len;
	ou_int32_t argc;
	char *buf_current = cmdline_argv_buf;
	const char **argv = (const char **) arg1;

	switch (op) {
	case 0: /* No boot command line, nothing to do here */
		break;

	case -1: /* UHI */
		argc = uhi_argc();
		for (i = 0; i < argc; i++) {
			next_len = uhi_argnlen(i);
			uhi_argn(i, buf_current);
			cmdline_argv[i] = buf_current;
			buf_current += next_len + 1;
		}
		break;

	case -2: /* Device Tree */
		/* TODO */
		break;

	default:
		if (op > 0) {
			cmdline_argc = op;
			for (i = 0; i < cmdline_argc; i++) {
				ou_strcpy(buf_current, argv[i]);
				cmdline_argv[i] = buf_current;
				buf_current += ou_strlen(buf_current) + 1;
			}
		}
	}
}

void k_main(void)
{
	ou_uint32_t mask;

	MTC0(0, MIPS_CP0_INDEX);
	MTC0(MIPS_CP0_PAGE_MASK_MASK_4K, MIPS_CP0_PAGE_MASK);
	TLBWI();

	MTC0(1, MIPS_CP0_INDEX);
	MTC0(MIPS_CP0_PAGE_MASK_MASK_16K, MIPS_CP0_PAGE_MASK);
	TLBWI();

	MTC0(0, MIPS_CP0_INDEX);
	TLBR();
	MFC0(mask, MIPS_CP0_PAGE_MASK);

	if ((mask & MIPS_CP0_PAGE_MASK_MASK) == MIPS_CP0_PAGE_MASK_MASK_4K) {
		k_puts("4k mask succeeded");
	} else {
		k_puts("4k mask failed");
	}

	MTC0(1, MIPS_CP0_INDEX);
	TLBR();
	MFC0(mask, MIPS_CP0_PAGE_MASK);

	if ((mask & MIPS_CP0_PAGE_MASK_MASK) == MIPS_CP0_PAGE_MASK_MASK_16K) {
		k_puts("16k mask succeeded");
	} else {
		k_puts("16k mask failed");
	}
}
