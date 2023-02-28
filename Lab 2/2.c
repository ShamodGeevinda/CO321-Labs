#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

#define DELAY_MS 50

int main(){

	DDRB |= (1<<0);			//initialized PORTB pin 0 as output
	DDRD &= ~(1<<2);		//initialized PORTD pin 2 as input
	
	EICRA |= (1<<ISC01); 	//set for negative edge detection
	EICRA &= ~(1<<ISC00);	//set for negative edge detection
	
	sei();					//enable the global interrupt
	
	EIMSK |= (1<<INT0); 	//enable external interrupt for INT0
	
	while(1){
	}
	
	return 0;
	
}

ISR(INT0_vect){
	
	PORTB = PORTB ^ (1<<0);
	_delay_ms(DELAY_MS);
	
}	