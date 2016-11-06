#ifndef __HT_GPIOIF_H__
#define __HT_GPIOIF_H__

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum
{
    NO_LED,
    LED1 = 0x1, /* RED LED D7/GP9/Pin64 */
    LED2 = 0x2, /* ORANGE LED D6/GP10/Pin1 */
    LED3 = 0x4  /* GREEN LED D5/GP11/Pin2 */
} ledEnum;

typedef enum
{
    NO_BTN,
    BTN1 = 0x1, /* BTN1 SW2 GP22/Pin15 */
    BTN2 = 0x2 /* BTN2 SW3 GP13/Pin4 */

} btnEnum;

typedef enum
{
    NO_LED_IND = NO_LED,
    MCU_SENDING_DATA_IND = LED1,
    MCU_ASSOCIATED_IND, /* Device associated to an AP */
    MCU_IP_ALLOC_IND, /* Device acquired an IP */
    MCU_SERVER_INIT_IND, /* Device connected to remote server */
    MCU_CLIENT_CONNECTED_IND, /* Any client connects to device */
    MCU_ON_IND,              /* Device SLHost invoked successfully */
    MCU_EXECUTE_SUCCESS_IND, /* Task executed sucessfully */
    MCU_EXECUTE_FAIL_IND, /* Task execution failed */
    MCU_RED_LED_GPIO,	/* GP09 for LED RED as per LP 3.0 */
    MCU_ORANGE_LED_GPIO,/* GP10 for LED ORANGE as per LP 3.0 */
    MCU_GREEN_LED_GPIO, /* GP11 for LED GREEN as per LP 3.0 */
    MCU_ALL_LED_IND
} ledNames;

//*****************************************************************************
//
// API Function prototypes
//
//*****************************************************************************
extern void GPIO_IF_GetPortNPin(unsigned char ucPin,
                     unsigned int *puiGPIOPort,
                     unsigned char *pucGPIOPin);

extern void GPIO_IF_ConfigureNIntEnable(unsigned int uiGPIOPort,
                                  unsigned char ucGPIOPin,
                                  unsigned int uiIntType,
                                  void (*pfnIntHandler)(void));					 
extern void GPIO_IF_Set(unsigned char ucPin,
             unsigned int uiGPIOPort,
             unsigned char ucGPIOPin,
             unsigned char ucGPIOValue);

extern unsigned char GPIO_IF_Get(unsigned char ucPin,
             unsigned int uiGPIOPort,
             unsigned char ucGPIOPin);
extern void GPIO_IF_LedConfigure(unsigned char ucPins);
extern void GPIO_IF_LedOn(char ledNum);
extern void GPIO_IF_LedOff(char ledNum);
extern unsigned char GPIO_IF_LedStatus(unsigned char ucGPIONum);
extern void GPIO_IF_LedToggle(unsigned char ucLedNum);

extern void GPIO_IF_ButtonConfigure(unsigned char ucPins);
extern unsigned char GPIO_IF_ButtonRead(unsigned char btnNum);
extern void Button1Interrupt();
extern void Button2Interrupt();
//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif //  __HT_GPIOIF_H__

