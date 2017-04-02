#include <ouroboros/hw/uart/16550.h>
#include <ouroboros/arch/mips/cp0.h>
#include <ouroboros/common.h>

static struct uart_16550 *uart = (struct uart_16550 *) 0x140003F8;

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
	k_puts("Hello world!");
}
