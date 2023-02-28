#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

#define DELAY_MS 1000
static int z = 0; 			// to count releases

int main(){
	

	DDRB |= 0b00111111;			//initialized PORTB pin 0 as output
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
	
	z = z + 1; 				// incrementing z
	PORTB = z; 				// send z value to PORTB
	_delay_ms(DELAY_MS);
	
}	