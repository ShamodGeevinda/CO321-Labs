#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

#define DELAY_MS 1000
static int z = 0; 			// to count releases

int main(){
	

	DDRB |= 0b00111111;			//initialized PORTB pin 0 as output
	DDRD &= ~(1<<2);		//initialized PORTD pin 2 as input
    DDRD &= ~(1<<3);		//initialized PORTD pin 3 as input
	
	EICRA |= (1<<ISC01); 	//set for positive edge detection
	EICRA |= (1<<ISC00);	//set for positive edge detection

    EICRA |= (1<<ISC11); 	//set for positive edge detection
	EICRA |= (1<<ISC10);	//set for positive edge detection
	
	sei();					//enable the global interrupt
	
	EIMSK |= (1<<INT0); 	//enable external interrupt for INT0  // pin 2
    EIMSK |= (1<<INT1); 	//enable external interrupt for INT1  // pin 3
	
	while(1){
	}
	
	return 0;
	
}

ISR(INT0_vect){
	
	PORTB = (PORTB<<1) | 0b00000000;    // shifting the value in the register to left and then add 0
	_delay_ms(DELAY_MS);
	
}


ISR(INT1_vect){
	
	PORTB = (PORTB<<1) | 0b00000001;    // shifting the value in the register to left and then add 1				
	_delay_ms(DELAY_MS);
	
}