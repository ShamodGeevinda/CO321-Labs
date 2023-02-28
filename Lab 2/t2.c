#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 100


int main(){
    DDRB &= ~(1<<2); // PD2 is input
    DDRB |= (1<<0); // PB0 is output

    EICRA |= (1<<ISC01); // set for rising edge detection
    EICRA |= (1<<ISC00); // set for rising edge detection

    sei();   // enable global interupts

    EIMSK |= (1<<INT0); // enable external interupts for int0

    while(1){

    }
    return 0;
}


 ISR (INT0_vect){
    PORTB &= ~(1<<0);
    _delay_ms (BLINK_DELAY_MS);
    PORTB |= (1<<0);
 }