#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char count=0;				//global because used in ISR


ISR(TIMER0_OVF_vect){				//called when flag is overflowed and TOV0 is set
	
	count++;						//incrementing the counter
	if(count==10){					//check if the counter is 10
		PORTB ^= (1<<5);			//if it is 10, 100ms is completed
		count=0;					//reset the counter to 0
	}
	TCNT0 = 100;                    //inital value is set to 100
}

int main(void){ 

	DDRB |= (1<<5);        			//PB5 is an output

	sei();							//setting global interrupts
	
  	TIMSK0 |=(1<<TOIE0);			//enable timer interrupt for timer0
	
	PORTB &= ~(1<<5);				//initially PB5 is reset
	
	TCNT0 = 100;                    //inital value is set to 100(10ms)
  	TCCR0A = 0x00;					//mode is set to normal
  	TCCR0B = 0b00000101;            //prescaler is maximized to 1024
	
	//delay is 10ms

	while(1);						//going to inifinity	
	
	return 0;
}



/*
XTAL = 16MHz → Txtal _clock = 1/ 16 µs 

Selecting the prescaler to the maximum value, 
Prescaler = 1:1024 → Tcounter_clock = 1024 × 1/ 16 µs = 64 µs 

Counter increments needed = 10,000µs / 64µs =156.25 (~156 increments)

Initial counter value = 1+255 – 156 = 100
*/
