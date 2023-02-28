#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

#define DELAY_MS 500

int main(){

	DDRB = 0b00111111;			//initialized PORTB pin 0 as output
	DDRD &= ~(1<<2);			//initialized PORTD pin 2 as input
	DDRD &= ~(1<<3);			//initialized PORTD pin 3 as input
	
	
	EICRA |= (1<<ISC01); 		//set for positive edge detection
	EICRA |= (1<<ISC00);		//set for positive edge detection
	
	EICRA |= (1<<ISC10); 		//set for positive edge detection
	EICRA |= (1<<ISC11);		//set for positive edge detection
	
	sei();						//enable the global interrupt
	
	EIMSK |= (1<<INT0); 		//enable external interrupt for INT0
	EIMSK |= (1<<INT1); 		//enable external interrupt for INT1
	
	while(1){
	}
	
	return 0;
	
}

// When press A input is 0
ISR(INT0_vect){
	
	PORTB = (PORTB<<1) + 0b00000000; 	// shift PORTB to left and add zero to 0th bit
	_delay_ms(DELAY_MS);
	
}	

// When press B input is 1
ISR(INT1_vect){
	
	PORTB = (PORTB<<1) + 0b00000001;	// shift PORTB to left and add 1 to 0th bit
	_delay_ms(DELAY_MS);
	
}	