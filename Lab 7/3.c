#include <avr/io.h>

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

char usart_receive(){
	while ((UCSR0A & (1 << RXC0)) == 0){   //wait until RXC0 is set
	} 
	return UDR0;      //return the received character
}

void EEPROMwrite (unsigned int address, char data){
	//wait for completion of previous write
	while(EECR & (1<<EEPE));
	
	//set up address and data regs
	EEAR = address;
	EEDR = data;
	
	//write logical 1 to EEMPE
	EECR |= (1<<EEMPE);
	
	//start EEPROM write
	EECR |= (1<<EEPE);
}

char EEPROMread(unsigned int address){
	//wait for completion of writes
	while(EECR & (1<<EEPE));
	
	//set up address
	EEAR = address;
	
	//start EEPROM read
	EECR |= (1<<EERE);
	
	//return data
	return EEDR;
}


int main(){
	
	usart_init();

	// int i=0;
	// while(EEPROMread(i)!='\r'){
	// 	usart_send (EEPROMread(i));
	// 	_delay_ms(50);
	// 	i++;
	// }
	
	// for(int i=0; i<1023 ; i++){       //read data from EEPROM and transmit it to serial port
	// 	usart_send (EEPROMread(i));
	// }
	unsigned char read_sentence[1000];
	int i=0;
    
    for(i=0;read_sentence[i]!='\r';i++){
        read_sentence[i] = EEPROMread(i); 
    }
    
    for (int counter = 0; counter<i; counter++)
    {
        
        usart_send(read_sentence[counter]);

    }
	
	return 0;
	
	
}