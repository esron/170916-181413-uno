#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#include "usart/usart.h"

unsigned volatile int counter = 0;

// INT0 interrupt service routine
ISR (INT0_vect) {
    counter++;
}

// INT1 interrupt service routine
ISR (INT1_vect) {
    counter++;
}

// Sends via serial the count of pulses per sensor type
void sendPulses(char sensorType) {
    char string[5];

    if(sensorType == 'i') {
        // Counting inductive interrups in 5 seconds
        EIMSK |= (1 << INT0);        // Turns on INT0
        _delay_ms(5000);
        EIMSK &= ~(1 << INT0);       // Disable INT0
        USART_putString("i\n");
    }
    else if (sensorType == 'o'){
        // Counting optic interrups in 5 seconds
        EIMSK |= (1 << INT1);        // Turns on INT1
        _delay_ms(5000);
        EIMSK &= ~(1 << INT1);       // Disable INT1
        USART_putString("o\n");
    }
    utoa(counter, string, 10); // Converts the integer to a string
    USART_putString(string);     // Send the value via serial port
    USART_send('\n');        // Sends a '\n' to indicate the end of message
    counter = 0;
}

int main(void) {

    cli(); // Disable interrupts
    USART_init();

    DDRD &= ~(1 << DDD2);     // Clear the PD2 pin
    DDRD &= ~(1 << DDD3);     // Clear the PD3 pin
    PORTD |= (1 << PORTD2) | (1 << PORTD3);   // turn On the Pull-up

    // set INT0 and INT1 to trigger on the rising edge
    EICRA |= (1 << ISC00) | (1 << ISC01) | (1 << ISC11) |  (1 << ISC10);

    sei(); // Enable interrups

    while(1) {
        sendPulses('i');
        sendPulses('o');
    }

    return 0;
}
