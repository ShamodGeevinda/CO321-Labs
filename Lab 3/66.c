#include<avr/io.h>
#include<avr/interrupt.h>
	
unsigned int counter = 0;

int main(){
	
	DDRB = (1<<5) | (1<<3); 			// Port B pin 5 and pin 3 are an output
	
	TCNT0 = 131;						//intial value is 131 in binary
	TCNT1 = 34286;						//intial value is 34286 in binary
	
	TCCR0A = 0x00;						// set to normal mode
	TCCR0B = 0b100;						//set cs bits to 100(256 scale)
	
	TCCR1A = 0x00;
	TCCR1B = 0b100; 					//Time mode with 1:256 pre-scalar
	
	TIMSK0 |= (1 << TOIE0); 			//Enable timer1 overflow interrupt
	TIMSK1 |= (1 << TOIE1); 					//Enable timer1 overflow interrupt
	
	sei();								//Enable the global interrupt
		
	while(1);
	
	return 0;
}

//This is for 50ms
ISR(TIMER0_OVF_vect){

	
	TCNT0 = 131;				//intial value is 131 in binary
	
	counter++;
	
	if(counter == 25){
		PORTB = PORTB ^ (1<<5);		// toggle the LED after 100ms
		counter = 0;
	}
	
}	

//This is for 500ms 
ISR(TIMER1_OVF_vect){

	PORTB = PORTB ^ (1<<3);		// toggle the LED
	TCNT1 = 34286;				// intial value is 34286 in binary

}	

/*
For 50 ms,

XTAL = 16MHz → Txtal _clock = 1/ 16 µs 

Selecting the prescaler to the maximum value, 
Prescaler = 1:256 → Tcounter_clock = 256 × 1/ 16 µs = 16 µs 

Counter increments needed = 2 ms / 16µs = 125 

Initial counter value = 1+255 – 125 = 131

but we need 50 ms; but we know 100ms = 25 x 2 ms

we use counter variable to increase until 25.

*/

/*
For 100 ms,

XTAL = 16MHz → Txtal _clock = 1/ 16 µs 

Selecting the prescaler to the maximum value, 
Prescaler = 1:256 → Tcounter_clock = 256 × 1/ 16 µs = 16 µs

Counter increments needed = 500 ms / 16µs = 31250

Initial counter value = 1+65535 – 31250 = 34286 


*/