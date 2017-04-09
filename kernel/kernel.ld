SECTIONS
{
	. = 0x80010000;

	.text :
	{
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
}
ENTRY(_start)
