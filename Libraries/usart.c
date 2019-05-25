#include<avr/io.h>
#include <avr/interrupt.h>
#include "usart.h"

#define F_CPU 8000000UL
#define UART_RX_BUF_MASK (UART_RX_BUF_SIZE - 1)
#define UART_TX_BUF_MASK (UART_TX_BUF_SIZE - 1)


static volatile char uartRxBuf[UART_RX_BUF_SIZE]; //bufor odbioru
static volatile uint8_t uartRxHead=0;	//indeks poczatku bufora (danych)
static volatile uint8_t uartRxTail=0;	//indeks konca bufora

static volatile char uartTxBuf[UART_TX_BUF_SIZE];	//bufor do nadawania
static volatile uint8_t uartTxHead=0;
static volatile uint8_t uartTxTail=0;

static void uart_9600(){	//pobranie wartosci do baudrate
	#define BAUD 9600
	#include <util/setbaud.h>
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;
}

void uartInit(){	//funkcja inicjalizacji
	uart_9600();
	UCSR0B = _BV(RXEN0) | _BV(TXEN0) | _BV(RXCIE0);// | _BV(TXCIE0); //wł odb/nad i przerwan
	UCSR0C = _BV(UCSZ00) | _BV(UCSZ01); //8 bit 1 stob bit
}

void uartSend(uint8_t data){
	while(!(UCSR0A & _BV(UDRE0))); //sprawdzenie gotowości do nadania
	UDR0 = data;
}

uint8_t uartReceive(){
	while(!(UCSR0A & _BV(RXC0))); //sprawdzenie gotowości do odbioru
	return UDR0;
}

char uartGetchar(){		//funkcja odbierania danych z bufora
	if (uartRxHead == uartRxTail)	//jak pusty
		return 0;
	uartRxTail = (uartRxTail+1) & UART_RX_BUF_MASK;	//nowy indeks ogona
	return uartRxBuf[uartRxTail];	//zwraca znak z bufora
}


ISR(USART_RX_vect){	//przerwanie wrzuca dane do bufora
	uint8_t tmpHead;
	char data;
	data = UDR0;
	tmpHead = (uartRxHead+1) & UART_RX_BUF_MASK;	//inkrementacja bufora i iloczyn z maską, mechanizm zapętlania

	if (tmpHead == uartRxTail)
		data = '!'; //obsługa próby nadpisania danych w buforze
	else{
		uartRxBuf[tmpHead] = data;	//wpisujemy odebrany bajt do bufora
		uartRxHead = tmpHead;	// zapamietujemy nowy indeks
	}
}


void uartPutchar(char data){
	uint8_t tmpHead;
	tmpHead = (uartTxHead +1) & UART_TX_BUF_MASK;
	while(tmpHead == uartTxTail)	//czeka jak brak miejsca w buforze
		;
	uartTxBuf[tmpHead] = data;
	uartTxHead = tmpHead;
	UCSR0B |= _BV(UDRIE0);	//wł przerwania bufor nadawczy pusty??
}

void uartPutTekst(char *txt){
	while(*txt)
		uartPutchar(*txt++);
}


ISR(USART_UDRE_vect){
	if (uartTxTail == uartTxHead) // jak bufor pusty zerujemy przerwanie z wolnego bufora nadawczego
		UCSR0B &= ~ _BV(UDRIE0); //wyłącz przerwanie

	else{
		uartTxTail = (uartTxTail +1) & UART_TX_BUF_MASK;
		UDR0 = uartTxBuf[uartTxTail];
	}

}

