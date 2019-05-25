
#include "avr/io.h"


#define BLACK 1
#define WHITE 0

#define LCDWIDTH 128
#define LCDHEIGHT 64

#define ST7565_DISPLAY_OFF   0xAE
#define ST7565_DISPLAY_ON    0xAF

#define ST7565_DISP_START_LINE  0x40
#define ST7565_PAGE  0xB0

#define ST7565_COLUMN_UPPER  0x10
#define ST7565_COLUMN_LOWER  0x00

#define ST7565_ADC_NORMAL  0xA0
#define ST7565_ADC_REVERSE 0xA1

#define ST7565_DISP_NORMAL 0xA6
#define ST7565_DISP_REVERSE 0xA7

#define ST7565_ALLPTS_NORMAL 0xA4
#define ST7565_ALLPTS_ON  0xA5
#define ST7565_BIAS_9 0xA2 
#define ST7565_BIAS_7 0xA3

#define ST7565_RMW  0xE0
#define ST7565_RMW_CLEAR 0xEE
#define ST7565_INTERNAL_RESET  0xE2
#define ST7565_COM_NORMAL  0xC0
#define ST7565_COM_REVERSE  0xC8
#define ST7565_POWER_CONTROL  0x28
#define ST7565_RESISTOR_RATIO  0x20
#define ST7565_VOLUME_FIRST  0x81
#define ST7565_VOLUME_SECOND  0
#define ST7565_STATIC_OFF  0xAC
#define ST7565_STATIC_ON  0xAD
#define ST7565_STATIC_REG  0x0
#define ST7565_BOOSTER_FIRST  0xF8
#define ST7565_BOOSTER_234  0
#define ST7565_BOOSTER_5  1
#define ST7565_BOOSTER_6  3
#define ST7565_NOP  0xE3
#define ST7565_TEST  0xF0



void st7565_init();
void st7565_display();
void st7565_clear();
void st7565_fill(uint8_t color);
void st7565_drawPixel(uint8_t x, uint8_t y, uint8_t color);
void st7565_setContrast(uint8_t);
void st7565_writeCommand(uint8_t);
void st7565_writeData(uint8_t);

