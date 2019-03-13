//	TODO: Put license here

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/crs.h>
#include <libopencm3/stm32/syscfg.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/systick.h>

#include "usb.c"

//	Variables go here
usbd_device *usbDevice;
uint8_t usbControlBuffer[128];
struct __attribute__((packed)){
	uint8_t buttons;
	int16_t x;
	int16_t y;
	int8_t	wheel;
} mouseData;


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

void sys_tick_handler(void)
{
	mouseData.buttons = 0;
	mouseData.x = 0;
	mouseData.y = 0;
	mouseData.wheel = 0;
	
	usbd_ep_write_packet(usbDevice, 0x81, (void *)&mouseData, 6);
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
	
	usbDevice = usbd_init(&st_usbfs_v2_usb_driver, &devDescriptor, &config, usbStrings, 2 ,usbControlBuffer, 128);
	usbd_register_set_config_callback(usbDevice, hidSetConfig);
	
	while(1)
	{
		usbd_poll(usbDevice);
	};
}