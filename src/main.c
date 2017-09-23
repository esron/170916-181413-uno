#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "usart/usart.h"

ISR (INT0_vect){
    USART_send('P');
    USART_send('\n');
}

int main(void){
    char string[] = "Oi Mundo\n";
    char response[5];

    cli();                    // Disable interrupts
    USART_init();
    DDRB = 0xFF;
    DDRD &= ~(1 << DDD2);     // Clear the PD2 pin
    PORTD |= (1 << PORTD2);   // turn On the Pull-up

    EICRA |= (1 << ISC00) | (1 << ISC01);    // set INT0 to trigger on ANY logic change
    EIMSK |= (1 << INT0);     // Turns on INT0

    sei();                    // turn on interrupts

    PORTB = 0;

    while(1)
    {
        USART_putString(string);
        USART_getString(response);
        _delay_ms(1000);
        USART_putString(response);

        if(response[0] == 'O' && response[1] == 'K')
            PORTB ^= _BV(5);

        //_delay_ms(5000);
    }
}
