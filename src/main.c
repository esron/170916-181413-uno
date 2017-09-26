#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#include "usart/usart.h"

unsigned volatile int cont;

ISR (INT0_vect){
    cont++;
}

int main(void){
    char string[5];
    cont = 0;
    cli();                    // Disable interrupts
    USART_init();
    DDRB = 0xFF;
    DDRD &= ~(1 << DDD2);     // Clear the PD2 pin
    PORTD |= (1 << PORTD2);   // turn On the Pull-up

    EICRA |= (1 << ISC00) | (1 << ISC01);    // set INT0 to trigger on ANY logic change
    EIMSK |= (1 << INT0);     // Turns on INT0

    PORTB = 0;

    for (int cont = 0; cont < 1000; cont++) {
        utoa(cont, string, 10);
        USART_putString(string);
        USART_putString("\n");
    }

    sei(); // Enable interrups
    while(1) {
        _delay_ms(5000);
        utoa(cont, string, 9);
        USART_putString(string);
        USART_putString("\n");
        //cont = 0;
    }
}
