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
	_delay_us(10);
}



void st7565_init(){
		ST7565_DDR |= _BV(A0_PIN) | _BV(RST_PIN) | _BV(CS_PIN);
		st7565_reset();
		st7565_writeCommand(ST7565_BIAS_7); // 
	  st7565_writeCommand(ST7565_ADC_NORMAL);	  // 
	  st7565_writeCommand(ST7565_COM_NORMAL);	  // 
		
		st7565_writeCommand(ST7565_RESISTOR_RATIO | 0x6);
		st7565_setContrast(0x10);
	  st7565_writeCommand(ST7565_POWER_CONTROL | 0x7);
		//gdzie booster??
//		 
	  st7565_Writecommand(ST7565_ALLPTS_NORMAL);	
		st7565_Writecommand(ST7565_DISPLAY_ON);
		//st7565_writeCommand(ST7565_DISP_START_LINE);	 
	
}

void st7565_setContrast(uint8_t val){
  st7565_Writecommand(ST7565_VOLUME_FIRST);
  st7565_Writecommand(ST7565_VOLUME_SECOND | (val & 0x3f));
}


void st7565_writeCommand(uint8_t command){
	ST7565_PORT &= ~_BV(CS_PIN); //chip select
	ST7565_PORT |= _BV(A0_PIN); //data
	spi_readWrite(command);
	ST7565_PORT &= ~_BV(A0_PIN);
	ST7565_PORT |= _BV(CS_PIN);
}
void st7565_writeData(uint8_t);