ENTRY(entry_x86)

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
