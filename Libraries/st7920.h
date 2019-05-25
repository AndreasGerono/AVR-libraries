//----------------------------

#include <avr/io.h>
#include <util/delay.h>

//-------------------------------------------------------------------------------------------------
//
// Konfiguracja wejśc

//
//-------------------------------------------------------------------------------------------------


#define LCD_RS_DIR		DDRB
#define LCD_RS_PORT 	PORTB
#define LCD_RS			_BV(PB2)

#define LCD_E_DIR		DDRB
#define LCD_E_PORT		PORTB
#define LCD_E			_BV(PB3)

#define LCD_DB4_DIR		DDRB
#define LCD_DB4_PORT	PORTB
#define LCD_DB4			_BV(PB4)

#define LCD_DB5_DIR		DDRB
#define LCD_DB5_PORT	PORTB
#define LCD_DB5			_BV(PB5)

#define LCD_DB6_DIR		DDRB
#define LCD_DB6_PORT	PORTB
#define LCD_DB6			_BV(PB6)

#define LCD_DB7_DIR		DDRB
#define LCD_DB7_PORT	PORTB
#define LCD_DB7			_BV(PB7)


//-------------------------------------------------------------------------------------------------
//
// Instrukcje kontrolera Hitachi ST7920
//
//-------------------------------------------------------------------------------------------------

#define ST7920_CLEAR					0x01

#define ST7920_HOME						0x02

#define ST7920_ENTRY_MODE				0x04
#define ST7920_EM_SHIFT_CURSOR			0
#define ST7920_EM_SHIFT_DISPLAY			1
#define ST7920_EM_DECREMENT				0
#define ST7920_EM_INCREMENT				2

#define ST7920_DISPLAY_ONOFF			0x08
#define ST7920_DISPLAY_OFF				0
#define ST7920_DISPLAY_ON				4
#define ST7920_CURSOR_OFF				0
#define ST7920_CURSOR_ON				2
#define ST7920_CURSOR_NOBLINK			0
#define ST7920_CURSOR_BLINK				1

#define ST7920_DISPLAY_CURSOR_SHIFT		0x10
#define ST7920_SHIFT_CURSOR				0
#define ST7920_SHIFT_DISPLAY			8
#define ST7920_SHIFT_LEFT				0
#define ST7920_SHIFT_RIGHT				4

#define ST7920_FUNCTION_SET				0x20
#define ST7920_EXTENDED					7
#define ST7920_GRAFIC					2
#define ST7920_4_BIT					0
#define ST7920_8_BIT					16

#define ST7920_CGRAM_SET				0x40


//-------------------------------------------------------------------------------------------------
//
// Deklaracje funkcji
//
//-------------------------------------------------------------------------------------------------

void LCD_GraphicModeOn();
void LCD_WriteCommand(uint8_t);
void LCD_WriteData(uint8_t);
void LCD_WriteText(char *);
void LCD_GoTo(uint8_t, uint8_t);
void LCD_Clear(void);
void LCD_Home(void);
void LCD_Initalize(void);

//-------------------------------------------------------------------------------------------------
//
// Koniec pliku ST7920.h
//
//-------------------------------------------------------------------------------------------------
