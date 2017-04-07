SECTIONS
{
	. = 0x80010000;
	.text : { *(.text) }
	. = ALIGN(0x1000);
	.text.evt : { *(.text.evt) }
	.rodata : { *(.rodata) }
	. = 0x84000000;
	.data : { *(.data) }
	.bss : { *(.bss) }
}
ENTRY(_start)
