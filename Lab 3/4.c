#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


// A B C D    C B    A B C D   C B
#define BLINK_DELAY_MS 200
#define DELAY_MS 50


ISR(TIMER1_OVF_vect){				//called when flag is overflowed and TOV0 is set
	
	PORTB ^= (1<<5);				//toggle the PB5 bit
	TCNT1 = 3036; 					//set the initial value again
    _delay_ms(DELAY_MS); 
}


int main (void){

    // data direction register for Port B
    DDRB = 0xFF; /* configure all pins of PORTB for output*/
	
	sei();					//enable global interrupt in the status reg
  
  	TIMSK1 |=(1<<TOIE1);	//enable interrupt for timer1
	
	
	TCNT1 = 3036;               	//inital value is set to 3036(1seconds)
  	TCCR1A = 0x00;					//mode is set to normal
  	TCCR1B = 0b00000100;           	//prescaler is maximized to 256
	
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





//  XTAL = 16MHz → Txtal _clock = 1/ 16 µs 

// Selecting the prescaler to the maximum value, 
// Prescaler = 1:256 → Tcounter_clock = 256 × 1/ 16 µs = 16 µs

// Counter increments needed = 1,000,000µs / 16µs =62500

// Initial counter value = 1+65535 – 62500 = 3036
