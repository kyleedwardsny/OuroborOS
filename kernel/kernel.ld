SECTIONS
{
	. = 0x10000;
	.text : { *(.text) }
	.rodata : {
		_rodata_start = ABSOLUTE(.);
	       *(.rodata)
		_rodata_end = ABSOLUTE(.);
	}
	. = 0x7000000;
	.data : { *(.data) }
	. = 0x8000000;
	.bss : { *(.bss) }
}
ENTRY(_start)
