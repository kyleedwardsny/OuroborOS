INCLUDE config.ld

SECTIONS
{
	. = KERNEL_LOAD_ADDR;

	.text :
	{
		*(.text.start)
		*(.text)
	}

	.rodata :
	{
		*(.rodata)
	}

	. = ALIGN(0x1000);

	.text.evt :
	{
		*(.text.evt)
	}

	. = ALIGN(0x1000);

	.data :
	{
		*(.data)
	}

	. = ALIGN(32);

	_bss_begin = ABSOLUTE(.);
	.bss :
	{
		*(.bss)
		. = ALIGN(32);
	}
	. = ALIGN(32);
	_bss_end = .;
	_bss_size = _bss_end - _bss_begin;

	. = ALIGN(0x1000);

	_stack_top = ABSOLUTE(.);
	. += 0x1000;
	_stack_bottom = ABSOLUTE(.);

	_initrd_begin = 0x80200000;
	_initrd_end = 0x80300000;
}
ENTRY(_start)
