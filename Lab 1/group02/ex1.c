#include <avr/io.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 2000
int main (void){
    DDRB = 0x0F; /* configure pin 2,3,4,5 of PORTB for output*/

    while(1){
        PORTB = 0x0F; /* set pin 5 high to turn led on */
        _delay_ms(BLINK_DELAY_MS);
        PORTB = 0x00; /* set pin 5 low to turn led off */
        _delay_ms(BLINK_DELAY_MS);
    }
}



