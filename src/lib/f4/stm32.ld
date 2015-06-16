ENTRY( Reset_Handler )

/* Highest address of the user mode stack .*/
_estack = 0x20020000; /* end of 128K RAM .*/


/*. Generate a link error if heap and s tack don’t fit int o RAM .*/
_Min_Heap_Size = 0;			/* required amount of heap */
/*_Min_Stack_Size = 0x200;	*/ /* required amount of stack */
_Min_Stack_Size = 0x20;	/* required amount of stack */

/* SRAM:	0x2000 0000 - 0x2001 FFFF */
/* CC SRAM: 0x1000 0000 - 0x1000 FFFF */
/* flash	0x0800 0000 - 0x080F FFFF */
MEMORY
{
    sram (W!RX) : ORIGIN = 0x20000000, LENGTH = 128K
    CCMRAM (xrw) : ORIGIN = 0x10000000, LENGTH = 64K
    flash (RX) : ORIGIN = 0x08000000, LENGTH = 1024K
}

SECTIONS
{  
    .text :
    {
        . = ALIGN(4);
        _text = .;
        PROVIDE(stext = .);
        KEEP(*(.isr_vector))
        *(.text .text.*)        
        *(.rodata .rodata.*)        
        *(.gnu.linkonce.t.*)
        *(.glue_7)
        *(.glue_7t)
        *(.gcc_except_table)
        *(.gnu.linkonce.r.*)
        . = ALIGN(4);
        _etext = .;
		_sidata = _etext;
        PROVIDE(etext = .);   
     		_fini = . ;
				*(.fini)

    } >flash

    .data : AT (_etext)
    {
        . = ALIGN(4);
        _sdata = .;
        *(.ramfunc .ramfunc.* .fastrun .fastrun.*)
        *(.data .data.*)
        *(.gnu.linkonce.d.*)
        . = ALIGN(4);
        _edata = .;
    } >sram
		
	/* INFO this sections i needed for linker */
		.ARM.extab :
		{
		    *(.ARM.extab*)
		} >sram
		
		__exidx_start = .;
		.ARM.exidx :
		{
		    *(.ARM.exidx*)
		} >sram
		__exidx_end = .;

    PROVIDE( flash_used_size = SIZEOF(.text) + SIZEOF(.data) + SIZEOF(.ARM.extab) + SIZEOF(.ARM.exidx) );
		
    .bss (NOLOAD) : {
		. = ALIGN(4);
        /* This is used by the startup in order to initialize the .bss secion */
        _sbss = .;
        *(.bss .bss.*)
        *(.gnu.linkonce.b.*)
        *(COMMON)
        . = ALIGN(4);        
        _ebss = .;
    } >sram
    
    end = .;
    /* PROVIDE( _estack = 0x20020000 ); */
    /*PROVIDE( _estack = 0x20020000 );	*//* end of 128 kB RAM */
	/* stack raste od kraja RAMa prema gore */
}

