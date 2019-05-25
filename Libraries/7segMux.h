#include<avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/io.h>


#define LEDDDR DDRB
#define LEDPORT PORTB
#define LEDPIN PINB
#define ONDDR DDRC
#define ONDPORT PORTC
#define ONDPIN PINC
#define DISP 4



volatile uint8_t ledDigit[(DISP-1)]; //tablica dostępu do cyfr

void timer0Init(); //funkcja inicjująca timer
void valToBCD(uint16_t);	//konwersja liczby do cyfr na 7seg










