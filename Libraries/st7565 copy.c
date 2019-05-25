#include "string.h"
#include "spi.h"
#include "util/delay.h"

#define ST7565_DDR DDRB
#define ST7565_PORT PORTB
#define A0_PIN	PB0
#define CS_PIN PB1
#define RST_PIN PB2




void st7565_display();
void st7565_clear();
void st7565_fill(uint8_t color);
void st7565_drawPixel(uint8_t x, uint8_t y, uint8_t color);



static void st7565_reset(){
	ST7565_PORT &= ~RST_PIN;
	_delay_ms(10);
	ST7565_PORT |= RST_PIN;
	_delay_us(100);
}



void st7565_init(){
		ST7565_DDR |= _BV(A0_PIN) | _BV(RST_PIN) | _BV(CS_PIN);
		st7565_reset();
		
		st7565r_writeCommand(ST7565R_LCD_BIAS_1_DIV_6_DUTY33); //nie inne?
		st7565r_writeCommand(ST7565R_ADC_NORMAL);              
		st7565r_writeCommand(ST7565R_REVERSE_SCAN_DIRECTION);  //?? nie normal?
		
		st7565r_writeCommand(ST7565R_VOLTAGE_RESISTOR_RATIO_7);
		st7565_setContrast(0x10); //pobawić sie?
		st7565r_writeCommand(ST7565R_POWER_CTRL_ALL_ON);       
		st7565r_writeCommand(ST7565R_BOOSTER_RATIO_SET);       
		st7565r_writeCommand(ST7565R_BOOSTER_RATIO_2X_3X_4X); //nie inne?
		
		st7565r_writeCommand(ST7565R_DISPLAY_NORMAL); // 
		st7565r_writecommand(ST7565R_CMD_START_LINE_SET);
		st7565r_writecommand(ST7565R_DISPLAY_ON);

}

void st7565_setContrast(uint8_t contrast){
	st7565r_writeCommand(ST7565R_ELECTRONIC_VOLUME_MODE_SET);
	st7565r_writeCommand(contrast);
}


void st7565_writeCommand(uint8_t command){
	ST7565_PORT &= ~_BV(CS_PIN); //chip select
	ST7565_PORT |= _BV(A0_PIN); //data
	spi_readWrite(command);
	ST7565_PORT &= ~_BV(A0_PIN);
	ST7565_PORT |= _BV(CS_PIN);
}
void st7565_writeData(uint8_t);