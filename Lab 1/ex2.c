#include <avr/io.h>
#include <util/delay.h>


// A B C D    C B    A B C D   C B
#define BLINK_DELAY_MS 200
int main (void){

    // data direction register for Port B
    DDRB = 0x0F; /* configure pin 0,1,2,3 of PORTB for output*/
    while(1){

       

        // A B C D loop
        // 1 0 0 0 --->  1<0
        // 0 1 0 0 --->  1<1
        // 0 0 1 0 --->  1<2
        // 0 0 0 1 --->  1<3
        for(int i=0; i < 4; i++){
            PORTB =  1<<i;
            _delay_ms(BLINK_DELAY_MS);
        }

        // C B loop
        // A B C D
        // 0 0 1 0 ---> 4>>0
        // 0 1 0 0 ---> 4>>1

        for(int i=0; i < 2; i++){
            PORTB =  4>>i;
            _delay_ms(BLINK_DELAY_MS);
        }


    }
}




