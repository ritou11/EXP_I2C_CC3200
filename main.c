/*
 * main.c
 */
// system includes
#include <stdio.h>
// Driverlib includes
#include "hw_types.h"
#include "hw_ints.h"
#include "hw_memmap.h"
#include "hw_common_reg.h"
#include "interrupt.h"
#include "hw_apps_rcm.h"
#include "prcm.h"
#include "rom.h"
#include "rom_map.h"
#include "prcm.h"
#include "gpio.h"
#include "utils.h"
// user-defined includes
#include "pin_mux_config.h"
#include "ht_gpio_if.h"
#include "uart_if.h"
#include "i2c_if.h"
#include "oled_if.h"

extern void (* const g_pfnVectors[])(void);

void LEDBlinkyRoutine();
static void BoardInit(void);

void LEDBlinkyRoutine()
{
    //
    // Toggle the lines initially to turn off the LEDs.
    // The values driven are as required by the LEDs on the LP.
    //
    GPIO_IF_LedOff(MCU_RED_LED_GPIO);
    unsigned char ucBtn1,ucBtn2;
    while(1)
    {
    	ucBtn1=GPIO_IF_ButtonRead(BTN1);
    	if(ucBtn1) GPIO_IF_LedOn(MCU_RED_LED_GPIO);
    	ucBtn2=GPIO_IF_ButtonRead(BTN2);
    	if(ucBtn2) GPIO_IF_LedOff(MCU_RED_LED_GPIO);
    }

}

static void
BoardInit(void)
{

    MAP_IntVTableBaseSet((unsigned long)&g_pfnVectors[0]);
    //
    // Enable Processor
    //
    MAP_IntMasterEnable();
    MAP_IntEnable(FAULT_SYSTICK);

    PRCMCC3200MCUInit();
}

int main(void) {

	BoardInit();

    PinMuxConfig();

    InitTerm();

    GPIO_IF_LedConfigure(LED1);
    GPIO_IF_ButtonConfigure(BTN1|BTN2);
    GPIO_IF_LedOff(MCU_RED_LED_GPIO);

    Report("This is my CC3200 Demo. Now it has uart,i2c,spi,gpio.\n\r");

    OLEDInit();

    OLED_Print(0,0,(byte *)"清");
    OLED_Print(0,2,(byte *)"华");
    OLED_Print(0,4,(byte *)"大");
    OLED_Print(0,6,(byte *)"学");

    OLED_Print(112,1,(byte *)"电");
    OLED_Print(112,3,(byte *)"机");
    OLED_Print(112,5,(byte *)"系");

    I2C_IF_Open(I2C_MASTER_MODE_STD);
    InitTermInt();

    while(1){
    	MAP_UtilsDelay(8000000);
    }
    return 0;
}
