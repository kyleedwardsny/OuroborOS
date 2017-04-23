SECTIONS
{
	. = 0x40000000;

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
		ASSERT(. <= 0x40001000, "early section is too big");
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
