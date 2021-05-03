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

	.idt BLOCK(0x1000) : ALIGN(0x1000)
	{
		_idt = .;
		. = . + 0x1000;
	}
}
