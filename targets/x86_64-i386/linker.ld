ENTRY(start)

SECTIONS
{
	. = 1M;

	.boot :
	{
		KEEP(*(.mb2_header))
	}

	.text :
	{
		*(.text)
	}
}
