#include<avr/io.h>
#include<avr/interrupt.h>
#include <util/delay.h>
#define DELAY_MS 50



ISR(TIMER1_OVF_vect){

	PORTB = PORTB ^ (1<<5);		// toggle the LED
	TCNT1 = 49911;				// for 1 sec at 16MHz
	_delay_ms(DELAY_MS);   				//Delay of 50ms 

}	

int main(){
	
	DDRB |= (1<<5); 							// Port B pin 5 is an output
	DDRB |= (1<<0) | (1<<1) | (1<<2) | (1<<3); 	// set first 4 pins of port B as an output
	
	TCNT1 = 49911;								// for 1 sec at 16MHz

	TCCR1A = 0x00;
	TCCR1B = 0b101; 							//Time mode with 1:1024 pre-scalar
	
	TIMSK1 |= (1 << TOIE1); 					//Enable timer1 overflow interrupt
	
	sei();										//Enable the global interrupt

// Knight Rider Circuit	
	while(1){
		
		for(int i=0;i<4;i++){    				//loop for 4
			PORTB = 1<<i;  						//Left shift 1 by i and asign it to PORTB pin 8
			_delay_ms(DELAY_MS);   				//Delay of 50ms 
		}
    
		for(int i=0;i<2;i++){  		
			PORTB = 4>>i;     					//Right shift 001 by i and asign it to PORTB start by pin -10
			_delay_ms(DELAY_MS);   				//Delay of 50ms
		}
		
	}
	
	return 0;
	
}

/*

	Delay = 1s 
	
	TXTAL = 1/16μs
	
	Pre-scaler = 1:1024
	
	TCounter_clock = 1024/16 = 64μs
	
	Counter increment needed = 1 s /64μs = 15625
	
	Initial counter value = 1+65535 - 15625 = 49911

*/