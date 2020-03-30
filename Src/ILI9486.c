#include "ILI9486.h"
#include "Font_24x16.h"

int16_t textColor = White, BackgroundColor = Black;
int16_t fontSize = 1;

void TFT_Init() {
   TFT_WriteCMD (ILI9341_RESET); // software reset comand
   HAL_Delay(100);
	 TFT_WriteCMD (ILI9341_SLEEP_OUT); // sleep out
   HAL_Delay(100);
   TFT_WriteCMD (ILI9341_DISPLAY_OFF); // display off
   //------------power control------------------------------
   TFT_WriteCMD (ILI9341_POWER1); // power control
   TFT_WriteData   (0x26); // GVDD = 4.75v
   TFT_WriteCMD (ILI9341_POWER2); // power control
   TFT_WriteData   (0x11); // AVDD=VCIx2, VGH=VCIx7, VGL=-VCIx3
   //--------------VCOM-------------------------------------
   TFT_WriteCMD (ILI9341_VCOM1); // vcom control
   TFT_WriteData   (0x35); // Set the VCOMH voltage (0x35 = 4.025v)
   TFT_WriteData   (0x3e); // Set the VCOML voltage (0x3E = -0.950v)
   TFT_WriteCMD (ILI9341_VCOM2); // vcom control
   TFT_WriteData   (0xbe);

   //------------memory access control------------------------
   TFT_WriteCMD (ILI9341_MAC); // memory access control
   TFT_WriteData(0x48);

   TFT_WriteCMD (ILI9341_PIXEL_FORMAT); // pixel format set
   TFT_WriteData   (0x55); // 16bit /pixel

	 TFT_WriteCMD(ILI9341_FRC);
   TFT_WriteData(0);
   TFT_WriteData(0x1F);
   //-------------ddram ----------------------------
   TFT_WriteCMD (ILI9341_COLUMN_ADDR); // column set
   TFT_WriteData   (0x00); // x0_HIGH---0
   TFT_WriteData   (0x00); // x0_LOW----0
   TFT_WriteData   (0x01); // x1_HIGH---240
   TFT_WriteData   (0xE0); // x1_LOW----240
   TFT_WriteCMD (ILI9341_PAGE_ADDR); // page address set
   TFT_WriteData   (0x00); // y0_HIGH---0
   TFT_WriteData   (0x00); // y0_LOW----0
   TFT_WriteData   (0x01); // y1_HIGH---320
   TFT_WriteData   (0x3F); // y1_LOW----320

   TFT_WriteCMD (ILI9341_TEARING_OFF); // tearing effect off
   //LCD_write_cmd(ILI9341_TEARING_ON); // tearing effect on
   //LCD_write_cmd(ILI9341_DISPLAY_INVERSION); // display inversion
   TFT_WriteCMD (ILI9341_Entry_Mode_Set); // entry mode set
   // Deep Standby Mode: OFF
   // Set the output level of gate driver G1-G320: Normal display
   // Low voltage detection: Disable
   TFT_WriteData   (0x07);
   //-----------------display------------------------
   TFT_WriteCMD (ILI9341_DFC); // display function control
   //Set the scan mode in non-display area
   //Determine source/VCOM output in a non-display area in the partial display mode
   TFT_WriteData   (0x0a);
   //Select whether the liquid crystal type is normally white type or normally black type
   //Sets the direction of scan by the gate driver in the range determined by SCN and NL
   //Select the shift direction of outputs from the source driver
   //Sets the gate driver pin arrangement in combination with the GS bit to select the optimal scan mode for the module
   //Specify the scan cycle interval of gate driver in non-display area when PTG to select interval scan
   TFT_WriteData   (0x82);
   // Sets the number of lines to drive the LCD at an interval of 8 lines
   TFT_WriteData   (0x27);
   TFT_WriteData   (0x00); // clock divisor

   TFT_WriteCMD (ILI9341_DISPLAY_ON); // display on
   HAL_Delay(100);
   TFT_WriteCMD (ILI9341_GRAM); // memory write
   HAL_Delay(5);
}

void TFT_SetFontSize(uint16_t sizeFont)
{
	fontSize = sizeFont;
}

void TFT_DrawString(int16_t x, int16_t y, char *string, int16_t color)
{
	int i;
	for(i = 0; string[i] != 0; i++) {
		TFT_DrawChar(x + (8 * i * fontSize), y , string[i], White);
	}
}

void TFT_DrawButton(int16_t x, int16_t y, char *string, int16_t color, int16_t BackgroundColor)
{
	int c;
	while(string[c] != '\0')
      c++;
	TFT_DrawFillRect(x, y, x + (9 * fontSize * c) + 20, y + 9 + 40, BackgroundColor);
	TFT_setBackgroundColor(BackgroundColor);
	TFT_DrawString(x + 20, y + 20, string, color);
}

void TFT_DrawChar(int16_t x, int16_t y, char character, int16_t color)
{
	int16_t i, j, k, h;
	
	LCD_Window(x, x + (8 * fontSize) -1, y, y + (8 * fontSize) -1);
	
	for(int i = 0; i < 8; i++) {
		for(h = 0; h < fontSize; h++) {
			for(int j = 0; j < 8; j++) {
				if((font8x8_basic[character][j] >> i) & 0x1) {
					for(k = 0; k < fontSize; k++)
						TFT_WriteData(color);
					} else {
					for(k = 0; k < fontSize; k++)
						TFT_WriteData(BackgroundColor);
				}
			}
		}
	}
}

void TFT_setTextColor(int16_t color)
{
	textColor = color;
}

void TFT_setBackgroundColor(int16_t color)
{
	BackgroundColor = color;
}

void TFT_Clear(uint16_t color) 
{
	unsigned int   i;

	LCD_WindowMax();

	for(i = 0; i < (WIDTH*HEIGHT); i++) {
		TFT_WriteData(color);
	}
}

void TFT_DrawFillRect(int16_t startx, int16_t starty, int16_t endx, int16_t endy, int16_t color)
{
	unsigned int i;
	unsigned int sizerect = (endx - startx) * (endy - starty);
	LCD_Window(startx, endx-1, starty, endy-1);
	
	for(i=0; i < sizerect; i++) {
		TFT_WriteData(color);
	}
}

void TFT_DrawPixel(int16_t x, int16_t y, int16_t color)
{
	LCD_Window(x, x, y, y);
	
	TFT_WriteData(color);
}

void TFT_DrawCircle(int16_t x0, int16_t y0, int16_t r, int16_t color)
{
	{
    int x = -r, y = 0, err = 2-2*r, e2;
    do {
        TFT_DrawPixel(x0-x, y0+y,color);
        TFT_DrawPixel(x0+x, y0+y,color);
        TFT_DrawPixel(x0+x, y0-y,color);
        TFT_DrawPixel(x0-x, y0-y,color);
        e2 = err;
        if (e2 <= y) {
            err += ++y*2+1;
            if (-x == y && e2 <= x) e2 = 0;
        }
        if (e2 > x) err += ++x*2+1;
    } while (x <= 0);
	}
}

void TFT_DrawFillCircle(int16_t x0, int16_t y0, int16_t r, int16_t color)
{
    int x = -r, y = 0, err = 2-2*r, e2;
    do {
        TFT_DrawLineVertical(y0-y, y0+y, x0-x, color);
        TFT_DrawLineVertical(y0-y, y0+y, x0+x, color);
        e2 = err;
        if (e2 <= y) {
            err += ++y*2+1;
            if (-x == y && e2 <= x) e2 = 0;
        }
        if (e2 > x) err += ++x*2+1;
    } while (x <= 0);
}

void TFT_DrawRect(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t color)
{
	if (x1 > x0) TFT_DrawLineHorizontal(x0,x1,y0,color);
	else  TFT_DrawLineHorizontal(x1,x0,y0,color);

	if (y1 > y0) TFT_DrawLineVertical(y0,y1, x0, color);
	else TFT_DrawLineVertical(y1,y0, x0, color);

	if (x1 > x0) TFT_DrawLineHorizontal(x0,x1,y1,color);
	else  TFT_DrawLineHorizontal(x1,x0,y1,color);

	if (y1 > y0) TFT_DrawLineVertical(y0,y1, x1, color);
	else TFT_DrawLineVertical(y1,y0, x1, color);
	return;
}


void TFT_DrawLineHorizontal(int16_t startx, int16_t endx, int16_t y, int16_t color)
{
	int16_t i;
	
	LCD_Window(startx, endx, y, y);
	
	for(i = startx; i <= endx ; i++)
	{
		TFT_WriteData(color);
	}
}

void TFT_DrawLineVertical(int16_t starty, int16_t endy, int16_t x, int16_t color)
{
	int16_t i;
	
	LCD_Window(x, x, starty, endy);
	
	for(i = starty; i <= endy ; i++)
	{
		TFT_WriteData(color);
	}
}

static __inline void LCD_WindowMax()
{
	LCD_Window(0, WIDTH-1, 0, HEIGHT-1);
}

void LCD_Window(int16_t Xstart, int16_t Xend, int16_t Ystart, int16_t Yend) 
{
	TFT_WriteCMD(ILI9341_COLUMN_ADDR);   
	TFT_WriteData(Xstart>>8);
	TFT_WriteData(Xstart&0xff);
	TFT_WriteData(Xend>>8);
	TFT_WriteData(Xend&0xff);

	TFT_WriteCMD(ILI9341_PAGE_ADDR);   
	TFT_WriteData(Ystart>>8);
	TFT_WriteData(Ystart&0xff);
	TFT_WriteData(Yend>>8);
	TFT_WriteData(Yend&0xff);

	//TFT_WriteCMD(0x3A);    // 16/18 bits
    //TFT_WriteData(0x55);
	
	TFT_WriteCMD(ILI9341_GRAM);
}

void TFT_Show() {
	LCD_WindowMax();
}

void TFT_DrawBitmap(uint16_t *image)
{
	unsigned int i;
	LCD_Window(0, WIDTH-1, 0, HEIGHT-1);

	for(i = 0; i < (WIDTH*HEIGHT); i++) {
		TFT_WriteData(image[i]);
	}
}

static __inline void TFT_WriteCMD(uint16_t data) { //WR: rise, RD: H, RS(D/CX):L
	cmdReg = data;
}

static __inline void TFT_WriteData(uint16_t data) {
	dataReg = data;
}

static __inline int16_t TFT_ReadData() { //
	unsigned short val = 0;
	return val;
}


static __inline int16_t TFT_ReadStatus() { //Implement later
	
}

