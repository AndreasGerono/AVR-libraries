#define UART_RX_BUF_SIZE 32	//musi byc ^2
#define UART_TX_BUF_SIZE 16 //musi byc ^2






void uartInit();	//inicjalizacja
void uartSend(uint8_t);	//wysyłanie ze sprawdzaniem flagi
uint8_t uartReceive();	//odbiór ze sprawdzaniem flagi


char uartGetchar();	//zwraca znak z bufora danych
void uartPutchar(char); //wrzucanie do bufora nadawczego
void uartPutTekst(char*);

