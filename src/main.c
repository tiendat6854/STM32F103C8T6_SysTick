#include "stm32f10x.h"                  // Device header

void GPIO_Init_PC13(void)
{
  RCC->APB2ENR |= (1 << 4);
	GPIOC->CRH &= ~(15 << 20);
	GPIOC->CRH |= (3 << 20);
}

void delay_us(uint32_t t)
{
  uint32_t i;
	for(i = 0 ; i < t ; i++)
	{
	  SysTick->LOAD = 7 - 1;
		SysTick->VAL = 0;
		SysTick->CTRL = 1; // 001: su dung clock he thong /8 (AHB/8) va cho phep bo dem SysTick hoat dong
		while( !(SysTick->CTRL & (1 << 16)) ); // doi bo dem dem ve 0
	}
}

void delay_ms(uint32_t t)
{
  uint16_t i;
	for(i = 0 ; i < t ; i++)
	{
	  SysTick->LOAD = 72*1000 -1 ;
		SysTick->VAL = 0;
		SysTick->CTRL = 5; // 101: su dung clock he thong (AHB) va cho phep bo dem SysTick hoat dong
		while( !(SysTick->CTRL & (1 << 16)) ); // doi bo dem dem ve 0
	}
}

int main()
{
  GPIO_Init_PC13();
	while(1)
	{
	  GPIOC->ODR |= (1 << 13);
		delay_us(500000);  // 500ms
		GPIOC->ODR &= ~(1 << 13);
		delay_us(600000);  // 600ms
	}
}
