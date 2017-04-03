SECTIONS
{
	. = 0x80010000;
	.text : { *(.text) }
	.rodata : { *(.rodata) }
	. = 0x87000000;
	.data : { *(.data) }
	. = 0x88000000;
	.bss : { *(.bss) }
}
ENTRY(_start)
