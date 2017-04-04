SECTIONS
{
	. = 0x80010000;
	.text : { *(.text) }
	.rodata : { *(.rodata) }
	. = 0x84000000;
	.data : { *(.data) }
	.bss : { *(.bss) }
}
ENTRY(_start)
