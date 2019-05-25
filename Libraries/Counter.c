#include<avr/io.h>
#include <avr/interrupt.h>






void initTimer(){
	TCCR1B = _BV(ICNC1)|_BV(ICES1); //włączenie trypu capture i noise cancel
	TCCR1B |= _BV(CS11)|_BV(CS10); //preskaler 64
	TIMSK1 = _BV(ICIE1)|_BV(TOIE1); //przerwanie z capture i przepełnienia
}

volatile uint8_t isOK;
ISR(TIMER1_OVF_vect){
	isOK = 0; //sygnalizuje przepełnienie - za niska f
}

volatile uint16_t timestamp;
volatile uint16_t period;

ISR(TIMER1_CAPT_vect){
	static uint8_t loctimestamp; //=0??
	if(TCCR1B & _BV(ICES1)){	//jeśli zbocze narastające jest wł
		GTCCR = _BV(PSRSYNC); //zerowanie preskalera
		TCNT1 = 0;	//zerowanie licznika
		TCCR1B &= ~_BV(ICES1); //nast zdarzenie na zborze opadajace
		period = ICR1;		//okres jest wartoscia z licznika ICR1 w którym jest wartosc TCNT w chwili przerwania
		timestamp = loctimestamp;
		isOK = 255;
	}
	else{ //jeśli zdarzenie na zboczu op
		TCCR1B |= _BV(ICES1); //nast zdarzenie na zbocze narastajace
		loctimestamp = ICR1;
		}
	}

