// source code to blink on board led in nucleo board
// C structures are explored to define hardware registers

#include <stdint.h>

// GPIO_TypeDef Structure definition
typedef struct
{
  volatile uint32_t MODER;
  volatile uint32_t OTYPER;
  volatile uint32_t OSPEEDR;
  volatile uint32_t PUPDR;
  volatile uint32_t IDR;
  volatile uint32_t ODR;
  volatile uint32_t BSRR;
  volatile uint32_t LCKR;
  volatile uint32_t AFRL;
  volatile uint32_t AFRH;
}GPIO_TypeDef ;

// RCC_TypeDef Structure definition
typedef struct
{
  volatile uint32_t DUMMY[12];
  volatile uint32_t AHB1ENR;
}RCC_TypeDef ;

// base address definition
#define RCC_BASE 0x40023800 
#define GPIOA_BASE 0x40020000

// peripheral pointer definition
#define RCC ((RCC_TypeDef*) RCC_BASE)
#define GPIOA ((GPIO_TypeDef*) GPIOA_BASE)

void main()
{
  // enable clock for GPIOA from RCC
  RCC->AHB1ENR |= (1U<<0);

  GPIOA->MODER |= (1U<<10);
  GPIOA->MODER &= ~(1U<<11);

  while(1)
  {
    // Set PIN5 High
    GPIOA->ODR ^= (1U<<5);
    for(int i=0 ; i<10000 ; i++){ /* delay */ }    
  }
}
