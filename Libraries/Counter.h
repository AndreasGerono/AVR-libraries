//mierzony sygnał doprowadź do we ICP1
//zbocze na ICP1 prowadzi do zapamietania wartosci TCNT1 w ICR1


#include<avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/io.h>




void initTimer();
