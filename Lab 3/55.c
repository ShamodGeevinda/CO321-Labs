#include<avr/io.h>
#include<avr/interrupt.h>
	
unsigned int counter = 1;

int main(){
	
	DDRB |= (1<<5); 			// Port B pin 5 is an output
	TCNT0 = 0x06;				//intial value is 6 in binary
	
	TCCR0A = 0x00;				// set to normal mode
	TCCR0B = 0b100;				//set cs bits to 100(256 scale)
	
	TIMSK0 |= (1 << TOIE0); 	//Enable timer1 overflow interrupt
	
	sei();						//Enable the global interrupt
		
	while(1){
	}
	
	return 0;
}

ISR(TIMER0_OVF_vect){

	
	TCNT0 = 0x06;				//intial value is 6 in binary
	
	counter++;
	
	if(counter == 25){
		PORTB = PORTB ^ (1<<5);		// toggle the LED after 100ms
		counter = 1;
	}
	
}	

/*
XTAL = 16MHz → Txtal _clock = 1/ 16 µs 

Selecting the prescaler to the maximum value, 
Prescaler = 1:256 → Tcounter_clock = 256 × 1/ 16 µs = 16 µs 

Counter increments needed = 4 ms / 16µs =250 

Initial counter value = 1+255 – 250 = 6

but we need 100 ms; but we know 100ms = 25 x 4 ms

we use counter variable to increase until 25.

*/