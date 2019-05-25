#include"uSonic.h"
#include<avr/io.h>
#include<avr/interrupt.h>
#include <util/delay.h>

static volatile uint16_t start,stop;

ISR(TIMER1_CAPT_vect){

	if (TCCR1B & _BV(ICES1)){
		start = ICR1;
		TCCR1B &= ~ _BV(ICES1); //nast falling edge
	}
	else{
		stop = ICR1;
		TCCR1B |= _BV(ICES1); //nast rising edge
	}

}

ISR(TIMER1_COMPA_vect){
	TRPORT &= ~TRPIN;
}

ISR(TIMER1_OVF_vect){

	TRPORT |= TRPIN;
}


void initUsSensor(){
	TRDDR |= TRPIN;
	OCR1A = 200;
	TCCR1B |= _BV(CS01) | _BV(ICNC1); //preskaler 8, red szumu
	TIMSK1 = _BV(TOIE1) | _BV(ICIE1) | _BV(OCIE1A);

}


uint32_t getDistanse(){ //zwraca dystans w cm
	uint32_t distans;
	distans = (stop-start);
	distans = (distans*17)/1000;
	return distans;
}


