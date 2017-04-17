INCLUDE arch/mips/config.ld

SECTIONS
{
	. = _kernel_link_addr;
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

	. = ALIGN(_max_cores_aligned * 32 * 4);

	.bss.regstore :
	{
		*(.bss.regstore)
	}

	_regstore_begin = ABSOLUTE(k_regstore);
	_regstore_upper = _regstore_begin >> 16;
	_regstore_lower = _regstore_begin & 0xFFFF;

	. = ALIGN(32);
	_bss_end = .;
	_bss_size = _bss_end - _bss_begin;

	. = ALIGN(0x1000);

	_single_stack_size = 0x1000;
	_stack_begin = ABSOLUTE(.);
	. += _single_stack_size * _max_cores_aligned;
	_stack_end = ABSOLUTE(.);
	_stack_size = _stack_end - _stack_begin;

	. = ALIGN(0x1000);
	_kernel_end = ABSOLUTE(.);
	_kernel_size = _kernel_end - _kernel_begin;
}
ENTRY(_start)
