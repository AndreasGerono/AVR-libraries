
#include "avr/io.h"


#define BLACK 1
#define WHITE 0

#define LCDWIDTH 128
#define LCDHEIGHT 64

#define ST7565R_DISPLAY_ON                     0xAF					//W³¹cz LCD
#define ST7565R_DISPLAY_OFF                    0xAE					//Wy³¹cz LCD
#define ST7565R_START_LINE_SET		           0x40					//Ustaw adres pierwszej wywietlanej linii
#define ST7565R_PAGE_ADDRESS_SET		       0xB0					//Ustaw adres strony
#define ST7565R_COLUMN_ADDRESS_SET_MSB		   0x10					//Ustaw adres kolumny
#define ST7565R_COLUMN_ADDRESS_SET_LSB         0x00
#define ST7565R_ADC_NORMAL                     0xA0
#define ST7565R_ADC_REVERSE                    0xA1
#define ST7565R_DISPLAY_NORMAL                 0xA6
#define ST7565R_DISPLAY_REVERSE                0xA7
#define ST7565R_DISPLAY_ALL_POINTS_OFF         0xA4					//Normalny tryb pracy LCD
#define ST7565R_DISPLAY_ALL_POINTS_ON          0xA5					//W³¹cz wszystkie piksele - dla testowania LCD
#define ST7565R_LCD_BIAS_1_DIV_5_DUTY33        0xA1
#define ST7565R_LCD_BIAS_1_DIV_6_DUTY33        0xA2
#define ST7565R_NORMAL_SCAN_DIRECTION          0xC0
#define ST7565R_REVERSE_SCAN_DIRECTION         0xC8
#define ST7565R_VOLTAGE_RESISTOR_RATIO_0       0x20
#define ST7565R_VOLTAGE_RESISTOR_RATIO_1       0x21
#define ST7565R_VOLTAGE_RESISTOR_RATIO_2       0x22
#define ST7565R_VOLTAGE_RESISTOR_RATIO_3       0x23
#define ST7565R_VOLTAGE_RESISTOR_RATIO_4       0x24
#define ST7565R_VOLTAGE_RESISTOR_RATIO_5       0x25
#define ST7565R_VOLTAGE_RESISTOR_RATIO_6       0x26
#define ST7565R_VOLTAGE_RESISTOR_RATIO_7       0x27
#define ST7565R_POWER_CTRL_ALL_ON              0x2F
#define ST7565R_SLEEP_MODE                     0xAC
#define ST7565R_NORMAL_MODE                    0xAD
#define ST7565R_RESET                          0xE2
#define ST7565R_NOP                            0xE3
#define ST7565R_ELECTRONIC_VOLUME_MODE_SET     0x81
#define ST7565R_BOOSTER_RATIO_SET              0xF8
#define ST7565R_BOOSTER_RATIO_2X_3X_4X         0x00
#define ST7565R_BOOSTER_RATIO_5X               0x01
#define ST7565R_BOOSTER_RATIO_6X               0x03
#define ST7565R_STATUS_READ                    0x00
#define ST7565R_END                            0xEE
#define ST7565R_READ_MODIFY_WRITE              0xE0


void st7565_init();
void st7565_display();
void st7565_clear();
void st7565_fill(uint8_t color);
void st7565_drawPixel(uint8_t x, uint8_t y, uint8_t color);
void st7565_setContrast(uint8_t);
void st7565_writeCommand(uint8_t);
void st7565_writeData(uint8_t);

