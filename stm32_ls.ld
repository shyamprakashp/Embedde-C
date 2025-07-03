// F/W entry point
ENTRY(Reset_Handler)

// Memory Directive
MEMORY
{
  FLASH(rx) : ORIGIN = 0x08000000 , LENGTH = 512K 
  SRAM(rwx) : ORIGIN = 0x20000000 , LENGTH = 128K
}

/* define a symbo _estack and setting it to end of the SRAM, this symbol is used for stack pointer initialization */
_estack = ORIGIN(SRAM) + LENGTH(SRAM) ;

/* define the maximum size of heap and stack , used for dynamic meomery allocation */
__max_heap_size = 0x200 ;
__max_stack_size = 0x400 ;

// output sections
SECTIONS
{
  // .text section
  .text :
  {
    . = ALIGN(4) ; // align the location pointer(.) in 4 byte boundary
    *(.isr_vector_tbl) // merge all all .isr_vector_tbl sections in input files
    *(.text)  // merge all .text sections in input files
    *(.rodata) // merge all .rodata section in input files
    . = ALIGN(4) ;
    _etext = . ; // symbol is defined at current location of location pointer(end of .text section) 
  }> FLASH 

  // .data section
  .data :
  {
    . = ALIGN(4);
    _sdata = . ;
    *(.data)  // merge all .data sections in the input files
    . = ALIGN(4);
    _edata = . ;
  }> SRAM AT> FLASH     // LMA (load memory address) in Flash and VMA (virtual memory address) in SRAM 

  // .bss section
  .bss :
  {
    . = ALIGN(4) ;
    _sbss = . ;
    *(.bss) // merge all .bss section from input files
    . = ALIGN(4) ;
    _ebss = . ;
  }> SRAM
}

