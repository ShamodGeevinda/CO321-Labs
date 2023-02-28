#include <avr/io.h>



int main(){

    DDRC &= ~(1<<1);            //make the PC1 as an input analog signal
    DDRD |= 0b11111111;         //make the port D as output pins
    
	
	ADCSRA |= 0b10000111;
	// ADEN | ADSC | ADATE | ADIF | ADIE | ADPS2 | ADPS1 | ADPS0
	
    // ADEN    enable the built in ADC
	// ADSC    stating the conversion 
	// ADPx    setting the prescaler of ADC as 128
	
	ADMUX |= 0b01100001; 
	// REFS1  | REFS0 | ADLAR | -- | MUX3 | MUX2 | MUX1 | MUX0
	
    // MUXx    setting the analog input channel as ADC1
    // REFSx   take the reference voltage as AVCC
    // ADLAR   getting the most significat 8 bits
	
	ADCSRA |= 0b01000000; // starting the convention


    while(1){

        // start conversion
        ADCSRA |= (1 << ADSC);

        while (((ADCSRA >> ADIF) & 0x01) ==0);// Wait for the conversion to be completed by polling the ADIF bit in the ADCSRA register.
											  // True when ADIF == 0. That means ADC conversion incompletes 

        PORTD = ADCH;                   
    }            

    return 0;
}


/*
prescaler value

-let prescaler be 128

    frequency of ADC = 16 MHz / 128 = 125kHz < 200kHz ==> ACCEPTABLE

*/