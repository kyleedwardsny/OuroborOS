SECTIONS
{
	_load_addr = 0x40000000;
	. = _load_addr;

	.rodata.header :
	{
		*(.rodata.header)
	}

	.text.early :
	{
		*(.text.early)
	}

	.rodata.early :
	{
		*(.rodata.early)
	}

	.data.early :
	{
		*(.data.early)
	}

	.bss.early :
	{
		*(.bss.early)
		ASSERT(. <= _load_addr + 0x1000, "early section is too big");
	}

	. = ALIGN(4);
	.text :
	{
		*(.text)
	}

	.rodata :
	{
		*(.rodata)
	}

	.data :
	{
		*(.data)
	}

	.bss :
	{
		*(.bss)
	}
}
