#ifndef OUREBOROS_HW_UART_16550_H
#define OUREBOROS_HW_UART_16550_H

#ifndef __ASSEMBLER__

#include <ouroboros/common.h>
#include <stdint.h>

PACKED_STRUCT_BEGIN(uart_16550) {
	union {
		volatile uint8_t thr;
		volatile uint8_t rbr;
		volatile uint8_t dll;
	} port0;

	union {
		volatile uint8_t ier;
		volatile uint8_t dlh;
	} port1;

	union {
		volatile uint8_t iir;
		volatile uint8_t fcr;
	} port2;

	volatile uint8_t lcr;
	volatile uint8_t mcr;
	volatile uint8_t lsr;
	volatile uint8_t msr;
	volatile uint8_t sr;
} PACKED_STRUCT_END;

#endif /* __ASSEMBLER__ */

/* Receive Buffer Register (DLAB = 0) */
#define UART_16550_RBR		(0)

/* Transmitter Holding Register (DLAB = 0) */
#define UART_16550_THR		(0)

/* Divisor Latch (LS) (DLAB = 1) */
#define UART_16550_DLL		(0)

/* Interrupt Enable Register (DLAB = 0) */
#define UART_16550_IER		(1)

/* Enable Received Data Available Interrupt */
#define UART_16550_IER_ERBFI	(0x01)
/* Enable Transmitter Holding Register Empty Interrupt */
#define UART_16550_IER_ETBEI	(0x02)
/* Enable Receiver Line Status Interrupt */
#define UART_16550_IER_ELSI	(0x04)
/* Enable MODEM Status Interrupt */
#define UART_16550_IER_EDSSI	(0x08)

/* Divisor Latch (MS) (DLAB = 1) */
#define UART_16550_DLM		(1)

/* Interrupt Identification Register */
#define UART_16550_IIR		(2)

/* 0 if Interrupt Pending */
#define UART_16550_IIR_IP	(0x01)
/* Interrupt ID */
#define UART_16550_IIR_IID0	(0x02)
#define UART_16550_IIR_IID1	(0x04)
#define UART_16550_IIR_IID2	(0x08)
#define UART_16550_IIR_IID	(UART_16550_IIR_IID0 | UART_16550_IIR_IID1 | UART_16550_IIR_IID2)
/* None */
#define UART_16550_IIR_IID_NONE	(UART_16550_IIR_IP)
/* Receiver Line Status */
#define UART_16550_IIR_IID_RLS	(UART_16550_IIR_IID0 | UART_16550_IIR_IID1)
/* Received Data Available */
#define UART_16550_IIR_IID_RDA	(UART_16550_IIR_IID1)
/* Character Timeout Indication */
#define UART_16550_IIR_IID_CTI	(UART_16550_IIR_IID1 | UART_16550_IIR_IID2)
/* Transmitter Holding Register Empty */
#define UART_16550_IIR_IID_THRE	(UART_16550_IIR_IID0)
/* MODEM Status */
#define UART_16550_IIR_IID_MS	(0)
/* FIFOs Enabled */
#define UART_16550_IIR_FE0	(0x40)
/* FIFOs Enabled (why are these duplicated?) */
#define UART_16550_IIR_FE1	(0x80)

/* FIFO Control Register */
#define UART_16550_FCR		(2)

/* FIFO Enable */
#define UART_16550_FCR_FE	(0x01)
/* RCVR FIFO Reset */
#define UART_16550_FCR_RFR	(0x02)
/* XMIT FIFO Reset */
#define UART_16550_FCR_XFR	(0x04)
/* DMA Mode Select */
#define UART_16550_FCR_DMS	(0x08)
/* RCVR Trigger (LSB) */
#define UART_16550_FCR_RTL	(0x40)
/* RCVR Trigger (MSB) */
#define UART_16550_FCR_RTM	(0x80)

/* Line Control Register */
#define UART_16550_LCR		(3)

/* Word Length Select */
#define UART_16550_LCR_WLS0	(0x01)
#define UART_16550_LCR_WLS1	(0x02)
#define UART_16550_LCR_WLS	(UART_16550_LCR_WLS0 | UART_LCR_WLS1)
#define UART_16550_LCR_WLS_5	(0)
#define UART_16550_LCR_WLS_6	(UART_16550_LCR_WLS0)
#define UART_16550_LCR_WLS_7	(UART_16550_LCR_WLS1)
#define UART_16550_LCR_WLS_8	(UART_16550_LCR_WLS0 | UART_16550_LCR_WLS1)
/* Number of Stop Bits */
#define UART_16550_LCR_STB	(0x04)
/* Parity Enable */
#define UART_16550_LCR_PEN	(0x08)
/* Even Parity Select */
#define UART_16550_LCR_EPS	(0x10)
/* Stick Parity */
#define UART_16550_LCR_SP	(0x20)
/* Set Break */
#define UART_16550_LCR_SB	(0x40)
/* Divisor Latch Access Bit */
#define UART_16550_LCR_DLAB	(0x80)

/* MODEM Control Register */
#define UART_16550_MCR		(4)

/* Data Terminal Ready */
#define UART_16550_MCR_DTR	(0x01)
/* Request to Send */
#define UART_16550_MCR_RTS	(0x02)
/* Out 1 */
#define UART_16550_MCR_OUT1	(0x04)
/* Out 2 */
#define UART_16550_MCR_OUT2	(0x08)
/* Loop */
#define UART_16550_MCR_LOOP	(0x10)

/* Line Status Register */
#define UART_16550_LSR		(5)

/* Data Ready */
#define UART_16550_LSR_DR	(0x01)
/* Overrun Error */
#define UART_16550_LSR_OE	(0x02)
/* Parity Error */
#define UART_16550_LSR_PE	(0x04)
/* Framing Error */
#define UART_16550_LSR_FE	(0x08)
/* Break Interrupt */
#define UART_16550_LSR_BI	(0x10)
/* Transmitter Holding Register */
#define UART_16550_LSR_THRE	(0x20)
/* Transmitter Empty */
#define UART_16550_LSR_TEMT	(0x40)
/* Error in RCVR FIFO */
#define UART_16550_LSR_ERF	(0x80)

/* MODEM Status Register */
#define UART_16550_MSR		(6)

/* Delta Clear to Send */
#define UART_16550_MSR_DCTS	(0x01)
/* Delta Data Set Ready */
#define UART_16550_MSR_DDSR	(0x02)
/* Trailing Edge Ring Indicator */
#define UART_16550_MSR_TERI	(0x04)
/* Delta Data Carrier Detect */
#define UART_16550_MSR_DDCD	(0x08)
/* Clear to Send */
#define UART_16550_MSR_CTS	(0x10)
/* Data Set Ready */
#define UART_16550_MSR_DSR	(0x20)
/* Ring Indicator */
#define UART_16550_MSR_RI	(0x40)
/* Data Carrier Detect */
#define UART_16550_MSR_DCD	(0x80)

/* Scratch Register */
#define UART_16550_SR		(7)

#endif /* OUREBOROS_HW_UART_16550_H */
