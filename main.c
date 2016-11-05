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
	char cmd[50];
	int cnt;

	BoardInit();

    PinMuxConfig();

    InitTerm();

    GPIO_IF_LedConfigure(LED1);
    GPIO_IF_ButtonConfigure(BTN1|BTN2);
    GPIO_IF_LedOff(MCU_RED_LED_GPIO);

    Message("Hello world! This is a test of UART on CC3200.\n\r");
    Message("Please input something to test UART:");

    cnt=GetCmd(cmd,50);

    if(cnt>0) Report("Success, recevied %d chars.\n\r",cnt);
    else Report("Failed.\n\r");

    Report("Send Charactor 't' to get temperature.\n\r");
    I2C_IF_Open(I2C_MASTER_MODE_STD);
    InitTermInt();

    while(1){
    	MAP_UtilsDelay(8000000);
    }
    return 0;
}
