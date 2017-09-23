#include <avr/io.h>
#include "usart.h"

void USART_init(void){
    UBRR0H = (uint8_t)(MYUBRR>>8); // Setting baudhate
    UBRR0L = (uint8_t)(MYUBRR);
    UCSR0B = (1<<RXEN0)|(1<<TXEN0); // Enable TX and RX
    UCSR0C = ((1<<UCSZ00)|(1<<UCSZ01)); // 8-bits data and 1 stop bit
}

void USART_send( unsigned char data){
    while(!(UCSR0A & (1<<UDRE0)));
    UDR0 = data;
}

unsigned char USART_receive(void){
    while(!(UCSR0A & (1<<RXC0)));
    return UDR0;
}

void USART_putString(char* StringPtr){
    while(*StringPtr != 0x00){    //Here we check if there is still more chars to send, this is done checking the actual char and see if it is different from the null char
        USART_send(*StringPtr);    //Using the simple send function we send one char at a time
        StringPtr++;
    }        //We increment the pointer so we can read the next char
}

void USART_getString(char* StringPtr){
    unsigned char ch = '\0';
    while(ch != '\n'){
        ch = USART_receive();
        *StringPtr = ch;
        StringPtr++;
    }
    *StringPtr = 0x00;
}
