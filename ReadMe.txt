
Common used libraries:
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/atomic.h>
#include <util/setbaud.h> //do ustawiania szyb. transm.
#include <stdlib.h>	//atoa, dtostr
#include <string.h> //to memcpy, memmove

#define F_CPU 8000000UL



1. 7seg
2. 7seg Mux + buttons + brightness
3. PWM + CTC
4. Inertion
5. Freq meater
6. uSonic meater
7. Servo
8. USART
