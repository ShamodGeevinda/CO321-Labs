#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char count=0;				//global because used in ISR

int main(void) {
    DDRB = 0xFF;/* configure all pins of PORTB for output*/

    TCNT0 = 100; //load the timer counter register with 100
    TCCR0A = 0x00; //set the Timer0 under normal mode
    TCCR0B = 0x05; //with 1:1024 prescaler



    TCNT1 = 34286; //load the timer counter register with 34286
    TCCR1A = 0x00; //set the Timer1 under normal mode
    TCCR1B = 0x04; //with 1:256 prescaler


    TIMSK1 = 1;
    TIMSK0 = 1;

    sei();
    while (1) {
    };
}

ISR(TIMER0_OVF_vect){   //called when flag is overflowed

       count++;						//incrementing the counter
	if(count==5){					//check if the counter is 5
		PORTB ^= (1<<5);			//if it is 5, 10ms is completed
		count=0;
	}
	TCNT0 = 100; 
	                  //inital value is set to 100
}
ISR(TIMER1_OVF_vect){   //called when flag is overflowed

        PORTB = PORTB ^ (1 << 4);/* set pin 4 high to turn led on */
        TCNT1 = 34286; //load the timer counter register with 34286

}



/*
For timer 0

XTAL = 16MHz → Txtal _clock = 1/ 16 µs 

Selecting the prescaler to the maximum value, 
Prescaler = 1:1024 → Tcounter_clock = 1024 × 1/ 16 µs = 64 µs

Counter increments needed = 500,00µs / 64µs =781.25

781.25/5 => 156.25 = 156

Initial counter value = 1+255 – 156 = 100


For timer 1
XTAL = 16MHz → Txtal _clock = 1/ 16 µs 

Selecting the prescaler to the maximum value, 
Prescaler = 1:256 → Tcounter_clock = 256 × 1/ 16 µs = 16 µs

Counter increments needed = 500,000µs / 16µs =31250

Initial counter value = 1+65535 – 31250 = 34286

*/
