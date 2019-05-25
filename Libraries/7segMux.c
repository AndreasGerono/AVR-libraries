#include <avr/io.h>
#include<avr/pgmspace.h>
#include <avr/interrupt.h>
#include"7segMux.h"



static void showOnLED(uint8_t);
static const uint8_t __flash digits[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f}; //__flash wrzuca do pamięci flash...

ISR(TIMER0_OVF_vect){

	static uint8_t ledon;
	ONDPORT = 0x0; //wyłącz wszystkie
	ledon = (ledon+1)%DISP; //bo 4 działaja
	showOnLED(ledDigit[ledon]);
	ONDPORT = _BV(ledon);

}


ISR(TIMER0_COMPA_vect){
	ONDPORT = 0;
}

void valToBCD(uint16_t val){
	int i,l;
		for(i=0,l=1;i<=DISP;i++,l*=10)
			ledDigit[i]=(val/l)%10;
}

void timer0Init(){
	TCCR0B |= _BV(CS01)|_BV(CS00);  //preskaler
	TIMSK0 |= _BV(TOIE0); //przerwanie z przepełnienia

	TIMSK0 |= _BV(OCIE0A);  //przerwanie z porównania
	OCR0A = 240; //wartośc do której ma liczyc/retulacja jasnosci

}


void showOnLED(uint8_t val){
	uint8_t tmp = 0x3f;
	if ((val&0xf)<sizeof(digits))
		tmp = digits[val];
	LEDDDR = tmp;
}


