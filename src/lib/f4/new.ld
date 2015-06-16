/* kopirano iz openBLTa i dodani dijelovi da ne javlja greske.
   prodje sve, ali se program ne pokrene */

MEMORY
{
    /* FLASH (rx) : ORIGIN = 0x0800C000, LENGTH = 1024K-48K */
    FLASH (rx) : ORIGIN = 0x0800C000, LENGTH = 1024K
    SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}

SECTIONS
{
    __STACKSIZE__ = 2048;

    .text :
    {
        KEEP(*(.isr_vector))
        *(.text*)
        *(.rodata*)
        _etext = .;
		_sidata = _etext;	/* INFO for startup file */
    } > FLASH

    .data : AT (ADDR(.text) + SIZEOF(.text))
    {
        _data = .;
		_sdata = _data;		/* INFO for startup file */
        *(vtable)
        *(.data*)
        _edata = .;
    } > SRAM

		.ARM.extab :
		{
		    *(.ARM.extab*)
		} > SRAM
		
		__exidx_start = .;
		.ARM.exidx :
		{
		    *(.ARM.exidx*)
		} > SRAM
		__exidx_end = .;


    PROVIDE( flash_used_size = SIZEOF(.text) + SIZEOF(.data) + SIZEOF(.ARM.extab) + SIZEOF(.ARM.exidx) );


    .bss :
    {
        _bss = .;
		_sbss = _bss;		/* INFO for startup file */
        *(.bss*)
        *(COMMON)
        _ebss = .;
        _stack = .;
        . = ALIGN(MAX(_stack + __STACKSIZE__ , .), 4);
        _estack = .;
    } > SRAM
}
