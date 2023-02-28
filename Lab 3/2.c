#include<avr/io.h>

void delay_timer(){
	
	TCNT0 = 0x83;				//intial value is 131 in binary
	
	TCCR0A = 0x00;			// set to normal mode	 
	TCCR0B = 0b100;			//set cs bits to 110(x256 scale)

	while((TIFR0 & 0x01)==0); //wait till timer overflow bit (T0V0)
	
	TCCR0A = 0x00;	// clear timer setting
	TCCR0B = 0x00;
	
	TIFR0 = 0x01; // clear the overflow bit (T0V0)
}	

int main(){
	
	DDRB |= (1<<5); 	// Port B pin 5 is an output
	
	while(1){
		
		PORTB = PORTB ^ (1<<5);
		
		for(int i =0; i < 250; i++){  	// increase the delay to 500ms using 'for loop'
			delay_timer();
		}
		
	}
	
	return 0;
}