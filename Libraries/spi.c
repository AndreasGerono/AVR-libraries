

#include "spi.h"
#include <avr/io.h>


void spi_init(){
	DDRB |= _BV(PB5) | _BV(PB3); //mosi/sck output
	SPCR |= _BV(SPE) | _BV(MSTR) | _BV(CPOL) | _BV(CPHA);
	
}

uint8_t spi_readWrite(uint8_t data){
	SPDR=data;                    
	while(!(SPSR & (1<<SPIF)));   
	return SPDR;     
}