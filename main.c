//	TODO: Put license here

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/crs.h>
#include <libopencm3/stm32/syscfg.h>
#include <libopencm3/stm32/gpio.h>

#include "usb.c"


//	Delay function supplied by Kristian Nielsen(knielsen)
static void delay(uint32_t nCount)
{
  // This should be 4 cycles per iteration. nCount must be > 0.
  __asm volatile
    ("\n"
	 ".syntax unified\n\t"
     "0:\n\t"
     "subs %1, #1\n\t"
     "bne 0b"
     : "=l" (nCount)
     : "0" (nCount)
     : "cc");
}

int main(void)
{
	rcc_clock_setup_in_hsi48_out_48mhz();
	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_GPIOB);
	rcc_periph_clock_enable(RCC_SYSCFG_COMP);	// Used for usb clock autotrim
	SYSCFG_CFGR1 |= SYSCFG_CFGR1_PA11_PA12_RMP;	// Pin replacement needed for usb
	crs_autotrim_usb_enable();
	rcc_set_usbclk_source(RCC_HSI48);
	
	while(1){};
}