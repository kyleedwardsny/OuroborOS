#include <ouroboros/arch/mips/cp0.h>
#include <ouroboros/common.h>
#include <ouroboros/hw/uart/16550.h>

#include <ouroboros/ikernel/config.h>
#include <ouroboros/ikernel/eat_self.h>
#include <ouroboros/ikernel/mmu.h>

#include <ouroboros/stdio.h>
#include <ouroboros/stdint.h>
#include <ouroboros/stdlib.h>
#include <ouroboros/string.h>

#include <libfdt.h>

static int k_putchar(struct uart_16550 *uart, int c)
{
	while (!(uart->lsr & UART_16550_LSR_THRE));
	uart->port0.rbr = c;
	return c;
}

static ou_ssize_t k_write(void *cb_data, const void *data, ou_size_t len)
{
	struct uart_16550 *uart = cb_data;
	ou_size_t i;
	const ou_uint8_t *bytes = data;

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

void k_main(void)
{
	k_read_cpu_config();
	k_clear_tlb();
}

void k_main_args(long arg0, unsigned long arg1, unsigned long arg2)
{
	void *fdt;

	switch (arg0) {
	case -2:
		fdt = (void *) arg1;
		if (fdt_check_header(fdt) < 0) {
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
