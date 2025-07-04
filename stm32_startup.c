// STARTUP FILE

// external symbol declaration
extern uint32_t _estack ;
extern uint32_t _etext ;
extern uint32_t _edata ;
extern uint32_t _sdata ;
extern uint32_t _ebss ;
extern uint32_t _sbss ;

// declaring function prototypes and corresponding attributes
void Reset_Handler(void);
void main(void);

void NMI_Handler(void)__attribute__((weak,alias("Default_Handler")));
void HardFault_Handler(void)__attribute__((weak,alias("Default_Handler")));
void MemManage_Handler(void)__attribute__((weak,alias("Default_Handler")));
// define additional interrept handlers here , if needed

// vector table definition
uint32_t vector_tbl[] __attribute__((section(".isr_vector_tbl"))) = {
  (uint32_t) &_estack,
  (uint32_t) &Reset_Handler,
  (uint32_t) &NMI_Handler,
  (uint32_t) &HardFault_Handler,
  (uint32_t) &MemManage_Handler,
  // add additional interrept handlers here , if available
};

// Default Handler definition
void Default Handler(void)
{
  while(1)
  {
    // infinite loop 
    //in case the handler for any interrept is not defined in else where in the code
  }
}
// Reset Handler definition
void Reset_Handler(void)
{
  uint32_t data_mem_size = (uint32_t) &_edata - (uint32_t) &_sdata ;
  uint32_t bss_mem_size = (uint32_t) &_ebss - (uint32_t) &_sbss ;

  // copying data section in FLASH to SRAM
  uint32_t *p_src_mem = (uint32_t) &_etext;
  uint32_t *p_dest_mem = (uint32_t) &_sdata;

  for(uint32_t i=0 ; i < data_mem_size ; i++)
  {
    *p_dest_mem++ = *p_src_mem++ ;
  }

  // initializing .bss section to zero
  p_dest_mem = (uint32_t *) &_sbss ;

  for( uint32_t i=0 ; i < bss_mem_size ; i++)
  {
    *p_dest_mem++ = 0 ; 
  }

  // calling application main function
  main() ; 
}
