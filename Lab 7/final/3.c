#include <avr/io.h>

#define BAUD 103  

//reading from the EEPROM
unsigned char EEPROMread(unsigned int uiAddress)
{
    /* Wait for completion of previous write */
    while(EECR & (1<<EEPE));
    
    /* Set up address register */
    EEAR = uiAddress;

    /* Start eeprom read by writing EERE */
    EECR |= (1<<EERE);

    /* Return data from Data Register */
    return EEDR;
}

void usart_init(){
	UCSR0B  |= (1 << RXEN0 ); 		// Enable the USART receiver
	UCSR0B  |= (1 << TXEN0 ); 		// Enable the USART transmitter
	
	UCSR0C &= ~(1<<UPM01 | 1<<UPM00);	//No parity
	UCSR0C &= ~(1<<USBS0);				//1 stop bit
	
	UCSR0C |= (1<<UCSZ00) | (1<<UCSZ01);  //8 bit data frame
	UCSR0B &= ~(1<<UCSZ02);
	
	UBRR0 = 103;   	//set baud rate tom 9600
}


void usart_send (char data){
	while (!(UCSR0A & (1<<UDRE0))){    //wait until UDRE0 bit is set
	}
	UDR0 = data;		//character is written to UDR0 register
}


int main(){

    usart_init(BAUD);

    unsigned char read_sentence[1000];

    int i=0;
    
    for(i=0;read_sentence[i]!='\r';i++){
        read_sentence[i] = EEPROMread(i); 
    }
    
    for (int counter = 0; counter<i; counter++)
    {
        
        usart_send(read_sentence[counter]);

    }
    usart_send('\n');
        
    return 0;
}