INCLUDE config.ld

SECTIONS
{
	. = KERNEL_LOAD_ADDR;
	_kernel_begin = ABSOLUTE(.);

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
	_stack_size = _stack_bottom - _stack_top;

	. = ALIGN(0x1000);
	_kernel_end = ABSOLUTE(.);
	_kernel_size = _kernel_end - _kernel_begin;
}
ENTRY(_start)
