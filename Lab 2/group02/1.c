#include <avr/io.h>
#include <util/delay.h>

#define DELAY_MS 500

int main(){
	
	unsigned char z = 0;	//use as the counter
	DDRD &= ~(1<<7);  		//PD7 is input
	DDRB = 0b00111111;		//PORTB 6 pins are output
	

	while(1){
		
		if(PIND & (1<<7)){
			z = z + 1;				//increament the counter
			PORTB = z; 				//assign the counter to display
			_delay_ms(DELAY_MS);		
		}
		
	}
	
	return 0;
}	
