	.section .rodata.header

_load_addr:
	.word 0x40000000

_entry_addr:
	.word _start

	.section .text.early

	.global _start
	.type _start, function
_start:
	b _start
