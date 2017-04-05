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
	ou_uint32_t status;
	ou_uint32_t *write0 = (ou_uint32_t *) 0x05000000;
	ou_uint32_t *write1 = (ou_uint32_t *) 0x05001000;
	ou_uint32_t *read0 = (ou_uint32_t *) 0x86000000;
	ou_uint32_t *read1 = (ou_uint32_t *) 0x86800000;

	MTC0(MIPS_CP0_INDEX_INDEX_INDEX(0), MIPS_CP0_INDEX);
	MTC0(MIPS_CP0_PAGE_MASK_MASK_4K, MIPS_CP0_PAGE_MASK);
	MTC0(MIPS_CP0_ENTRY_LO_PFN_PFN(0x06000000) | MIPS_CP0_ENTRY_LO_C_U | MIPS_CP0_ENTRY_LO_D | MIPS_CP0_ENTRY_LO_V | MIPS_CP0_ENTRY_LO_G, MIPS_CP0_ENTRY_LO0);
	MTC0(MIPS_CP0_ENTRY_LO_PFN_PFN(0x06800000) | MIPS_CP0_ENTRY_LO_C_U | MIPS_CP0_ENTRY_LO_D | MIPS_CP0_ENTRY_LO_V | MIPS_CP0_ENTRY_LO_G, MIPS_CP0_ENTRY_LO1);
	MTC0(MIPS_CP0_ENTRY_HO_VPN2_VPN2(0x05000000), MIPS_CP0_ENTRY_HO);
	TLBWI();

	MFC0(status, MIPS_CP0_STATUS);
	status &= ~(MIPS_CP0_STATUS_ERL | MIPS_CP0_STATUS_EXL | MIPS_CP0_STATUS_KSU);
	status |= MIPS_CP0_STATUS_KSU_K;
	MTC0(status, MIPS_CP0_STATUS);

	*write0 = 0xdeadbea7;

	if (*read0 == 0xdeadbea7) {
		k_puts("Even page wrote");
	} else {
		k_puts("Even page didn't write");
	}

	*write1 = 0xd00dfeed;

	if (*read1 == 0xd00dfeed) {
		k_puts("Odd page wrote");
	} else {
		k_puts("Odd page didn't write");
	}
}
