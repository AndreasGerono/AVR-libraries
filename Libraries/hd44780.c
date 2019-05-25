//-------------------------------------------------------------------------------------------------
// Wyswietlacz alfanumeryczny ze sterownikiem HD44780
// Sterowanie w trybie 4-bitowym bez odczytu flagi
// Data : 24.03.2007
//-------------------------------------------------------------------------------------------------

#include "hd44780.h"
//-------------------------------------------------------------------------------------------------
//
//
//-------------------------------------------------------------------------------------------------
static void _LCD_OutNibble(uint8_t nibbleToWrite) {
	if (nibbleToWrite & _BV(0))
		LCD_DB4_PORT |= LCD_DB4;
	else
		LCD_DB4_PORT &= ~LCD_DB4;

	if (nibbleToWrite & _BV(1))
		LCD_DB5_PORT |= LCD_DB5;
	else
		LCD_DB5_PORT &= ~LCD_DB5;

	if (nibbleToWrite & _BV(2))
		LCD_DB6_PORT |= LCD_DB6;
	else
		LCD_DB6_PORT &= ~LCD_DB6;

	if (nibbleToWrite & _BV(3))
		LCD_DB7_PORT |= LCD_DB7;
	else
		LCD_DB7_PORT &= ~LCD_DB7;
}
//-------------------------------------------------------------------------------------------------
//
// Funkcja zapisu bajtu do wyswietacza (bez rozroznienia instrukcja/dane).
//
//-------------------------------------------------------------------------------------------------
void _LCD_Write(uint8_t dataToWrite) {
	LCD_E_PORT |= LCD_E;
	_LCD_OutNibble(dataToWrite >> 4);
	LCD_E_PORT &= ~LCD_E;
	LCD_E_PORT |= LCD_E;
	_LCD_OutNibble(dataToWrite);
	LCD_E_PORT &= ~LCD_E;
	_delay_us(50);
}
//-------------------------------------------------------------------------------------------------
//
// Funkcja zapisu rozkazu do wyswietlacza
//
//-------------------------------------------------------------------------------------------------
void LCD_WriteCommand(uint8_t commandToWrite) {
	LCD_RS_PORT &= ~LCD_RS;
	_LCD_Write(commandToWrite);
}
//-------------------------------------------------------------------------------------------------
//
// Funkcja zapisu danych do pamieci wyswietlacza
//
//-------------------------------------------------------------------------------------------------
void LCD_WriteData(uint8_t dataToWrite) {
	LCD_RS_PORT |= LCD_RS;
	_LCD_Write(dataToWrite);
}
//-------------------------------------------------------------------------------------------------
//
// Funkcja wyswietlenia napisu na wyswietlaczu.
//
//-------------------------------------------------------------------------------------------------
void LCD_WriteText(char * text) {
	while (*text)
		LCD_WriteData(*text++);
}
//-------------------------------------------------------------------------------------------------
//
// Funkcja ustawienia wsporzednych ekranowych
//
//-------------------------------------------------------------------------------------------------
void LCD_GoTo(uint8_t x, uint8_t y) {
	LCD_WriteCommand(HD44780_DDRAM_SET | (x + (0x40 * y)));
}
//-------------------------------------------------------------------------------------------------
//
// Funkcja czyszczenia ekranu wyswietlacza.
//
//-------------------------------------------------------------------------------------------------
void LCD_Clear(void) {
	LCD_WriteCommand(HD44780_CLEAR);
	_delay_ms(2);
}
//-------------------------------------------------------------------------------------------------
//
// Funkcja przywr�cenia pocz�tkowych wsp�rz�dnych wy�wietlacza.
//
//-------------------------------------------------------------------------------------------------
void LCD_Home(void) {
	LCD_WriteCommand(HD44780_HOME);
	_delay_ms(2);
}
//-------------------------------------------------------------------------------------------------
//
// Procedura inicjalizacji kontrolera HD44780.
//
//-------------------------------------------------------------------------------------------------
void LCD_Initalize(void) {
	uint8_t i;
	LCD_DB4_DIR |= LCD_DB4; // Konfiguracja kierunku pracy wyprowadzen
	LCD_DB5_DIR |= LCD_DB5; //
	LCD_DB6_DIR |= LCD_DB6; //
	LCD_DB7_DIR |= LCD_DB7; //
	LCD_E_DIR |= LCD_E;   //
	LCD_RS_DIR |= LCD_RS;  //
	_delay_ms(15); // oczekiwanie na ustalibizowanie sie napiecia zasilajacego
	LCD_RS_PORT &= ~LCD_RS; // wyzerowanie linii RS
	LCD_E_PORT &= ~LCD_E;  // wyzerowanie linii E

	for (i = 0; i < 3; i++) // trzykrotne powtorzenie bloku instrukcji
			{
		LCD_E_PORT |= LCD_E; //  E = 1
		_LCD_OutNibble(0x03); // tryb 8-bitowy
		LCD_E_PORT &= ~LCD_E; // E = 0
		_delay_ms(5); // czekaj 5ms
	}

	LCD_E_PORT |= LCD_E; // E = 1
	_LCD_OutNibble(0x02); // tryb 4-bitowy
	LCD_E_PORT &= ~LCD_E; // E = 0

	_delay_ms(1); // czekaj 1ms
	LCD_WriteCommand(HD44780_FUNCTION_SET | HD44780_FONT5x7 | HD44780_TWO_LINE | HD44780_4_BIT); // interfejs 4-bity, 2-linie, znak 5x7
	LCD_WriteCommand(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_OFF); // wyczyszczenie wyswietlacza
	LCD_WriteCommand(HD44780_CLEAR); // czyszczenie zawartosci pamieci DDRAM
	_delay_ms(2);
	LCD_WriteCommand(HD44780_ENTRY_MODE | HD44780_EM_SHIFT_CURSOR | HD44780_EM_INCREMENT); // inkrementaja adresu i przesuwanie kursora
	LCD_WriteCommand(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_ON | HD44780_CURSOR_OFF| HD44780_CURSOR_NOBLINK); // LCD bez kursora i mrugania
}

//-------------------------------------------------------------------------------------------------
//
// Koniec pliku HD44780.c
//
//-------------------------------------------------------------------------------------------------
