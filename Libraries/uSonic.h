#include<avr/io.h>

#define TRPIN	_BV(PB1)
#define TRDDR	DDRB
#define TRPORT	PORTB
#define MAXDIST 12000

void initUsSensor();
uint32_t getDistanse();

