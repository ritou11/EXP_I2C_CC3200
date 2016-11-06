//*****************************************************************************
// oled_if.h
//
// oled interface header file: Prototypes and Macros for OLED
//
//*****************************************************************************

#ifndef __oled_if_H__
#define __oled_if_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************/
/*								MACROS										*/
/****************************************************************************/
#define byte unsigned char
#define word unsigned short

#define SPI_BIT_RATE  	100000
#define SYSCLK          80000000
#define OLED         	GSPI_BASE
#define OLED_PERIPH  	PRCM_GSPI
#define GPIO_RST 30
#define GPIO_DC 31
//
// Define the size of UART IF buffer for RX
//
#define OLED_IF_BUFFER           64
#define X_WIDTH     128
#define Y_WIDTH     64
#define XLevelL		0x00
#define XLevelH		0x10
#define XLevel		((XLevelH&0x0F)*16+XLevelL)
#define Max_Column	128
#define Max_Row		  64
#define	BRIGHTNESS	0xCF
//
// Define the UART IF buffer
//
extern unsigned char g_ucOLEDBuffer[];


/****************************************************************************/
/*								FUNCTION PROTOTYPES							*/
/****************************************************************************/
extern void OLEDInit();
extern void OLED_CLS(void);
extern void OLED_P6x8Str(byte x,byte y,byte ch[]);
extern void OLED_P8x16Str(byte x,byte y,byte ch[]);
extern void OLED_P16x16Str(byte x,byte y,byte ch[]);
extern void OLED_Print(byte x, byte y, byte ch[]);
extern void OLED_PutPixel(byte x,byte y);
extern void OLED_Rectangle(byte x1,byte y1,byte x2,byte y2,byte gif);
extern void OLED_DrawLibLogo(void);
extern void OLED_DrawBMP(byte x0,byte y0,byte x1,byte y1,byte bmp[]);
extern void OLED_Fill(byte dat);
//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif

