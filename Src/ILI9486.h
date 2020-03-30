#ifndef __ILI9486_H__
#define __ILI9486_H__
#include <stdint.h>
#include "stm32f4xx_hal.h"

#define cmdReg *(__IO uint16_t *)(0x6C000000)
#define dataReg *(__IO uint16_t *)(0x6C000800)


// LCD Size Defenition
#ifndef WIDTH
#define WIDTH       	480         		/* Screen Width (in pixels)           */
#define HEIGHT      	320             /* Screen Hight (in pixels)           */
#endif

#define ILI9341_RESET			 		    	0x01
#define ILI9341_SLEEP_OUT		  			0x11
#define ILI9341_GAMMA			    			0x26
#define ILI9341_DISPLAY_OFF					0x28
#define ILI9341_DISPLAY_ON					0x29
#define ILI9341_COLUMN_ADDR					0x2A
#define ILI9341_PAGE_ADDR			  		0x2B
#define ILI9341_GRAM				    		0x2C
#define ILI9341_TEARING_OFF					0x34
#define ILI9341_TEARING_ON					0x35
#define ILI9341_DISPLAY_INVERSION		0xb4
#define ILI9341_MAC			        		0x36
#define ILI9341_PIXEL_FORMAT    		0x3A
#define ILI9341_WDB			    	  		0x51
#define ILI9341_WCD				      		0x53
#define ILI9341_RGB_INTERFACE   		0xB0
#define ILI9341_FRC					    	0xB1
#define ILI9341_BPC					    	0xB5
#define ILI9341_DFC				 	    	0xB6
#define ILI9341_Entry_Mode_Set		0xB7
#define ILI9341_POWER1						0xC0
#define ILI9341_POWER2						0xC1
#define ILI9341_VCOM1							0xC5
#define ILI9341_VCOM2							0xC7
#define ILI9341_POWERA						0xCB
#define ILI9341_POWERB						0xCF
#define ILI9341_PGAMMA						0xE0
#define ILI9341_NGAMMA						0xE1
#define ILI9341_DTCA							0xE8
#define ILI9341_DTCB							0xEA
#define ILI9341_POWER_SEQ					0xED
#define ILI9341_3GAMMA_EN					0xF2
#define ILI9341_INTERFACE					0xF6
#define ILI9341_PRC				   	  	0xF7
#define ILI9341_VERTICAL_SCROLL 	0x33

#define ILI9341_MEMCONTROL         0x36
#define ILI9341_MADCTL_MY  0x80
#define ILI9341_MADCTL_MX  0x40
#define ILI9341_MADCTL_MV  0x20
#define ILI9341_MADCTL_ML  0x10
#define ILI9341_MADCTL_RGB 0x00
#define ILI9341_MADCTL_BGR 0x08
#define ILI9341_MADCTL_MH  0x04

/* LCD RGB color definitions */
#define Black           0x0000			/*   0,   0,   0 */
#define Navy            0x000F      /*   0,   0, 128 */
#define DarkGreen       0x03E0      /*   0, 128,   0 */
#define DarkCyan        0x03EF      /*   0, 128, 128 */
#define Maroon          0x7800      /* 128,   0,   0 */
#define Purple          0x780F      /* 128,   0, 128 */
#define Olive           0x7BE0      /* 128, 128,   0 */
#define LightGrey       0xC618      /* 192, 192, 192 */
#define DarkGrey        0x7BEF      /* 128, 128, 128 */
#define Blue            0x001F      /*   0,   0, 255 */
#define Green           0x07E0      /*   0, 255,   0 */
#define Cyan            0x07FF      /*   0, 255, 255 */
#define Red             0xF800      /* 255,   0,   0 */
#define Magenta         0xF81F      /* 255,   0, 255 */
#define Yellow          0xFFE0      /* 255, 255, 0   */
#define White           0xFFFF      /* 255, 255, 255 */
#define WHITE           0XFFFF      /* 255, 255, 255 */   
#define RED             0xF800      /* 255,   0,   0 */
#define BLUE            0x001F      /*   0,   0, 255 */

void TFT_Init(); //Initialization
void TFT_Clear (uint16_t color); // Clears the LCD to color
void TFT_WriteCMD(uint16_t Data); 
void TFT_WriteData(uint16_t data);
void LCD_Window(int16_t Xstart, int16_t Xend, int16_t Ystart, int16_t Yend); // Sets the LCD write window
void LCD_WindowMax(); // Sets the LCD write window to maximum.
void TFT_setTextColor(int16_t color); // sets text color.
void TFT_setBackgroundColor(int16_t color); // sets background color.
void TFT_DisplayChar (unsigned int ln, unsigned int col, unsigned char c);
void TFT_Show();

void TFT_DrawPixel(int16_t x, int16_t y, int16_t color); // Puts just a pixel.

void TFT_DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t color);
void TFT_DrawLineVertical(int16_t starty, int16_t endy, int16_t x, int16_t color);
void TFT_DrawLineHorizontal(int16_t startx, int16_t endx, int16_t y, int16_t color);

void TFT_DrawCircle(int16_t x0, int16_t y0, int16_t r, int16_t color);
void TFT_DrawFillCircle(int16_t x0, int16_t y0, int16_t r, int16_t color);

void TFT_DrawFillRect(int16_t startx, int16_t starty, int16_t endx, int16_t endy, int16_t color);  
void TFT_DrawRect(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t color);

void TFT_DrawChar(int16_t x, int16_t y, char character, int16_t color);
void TFT_SetFontSize(uint16_t sizeFont);
void TFT_DrawString(int16_t x, int16_t y, char *string, int16_t color);
void TFT_DrawButton(int16_t x, int16_t y, char *string, int16_t color, int16_t BackgroundColor);

void TFT_DrawBitmap(uint16_t *image);
int16_t TFT_ReadPins();
int16_t TFT_ReadData();
int16_t TFT_ReadStatus();





#endif