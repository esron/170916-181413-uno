#ifndef USART_H_   /* Include guard */
#define USART_H_

#define FOSC 16000000 // Clock Speed
#define BAUD 115200     // baudrate
#define MYUBRR (FOSC/8/BAUD-1) // Baudrate prescaller

// Initialization of registeres
void USART_init();

// Send a caracter
void USART_send(unsigned char data);

// Receive a caracter
unsigned char USART_receive();

// Send a string of caracters
void USART_putString(char* StringPtr);

// Receive a string of caracters
void USART_getString(char* StringPtr);

#endif // FOO_H_
