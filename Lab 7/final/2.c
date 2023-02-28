#include <avr/io.h>

#define BAUD 103    

//writing to the EEPROM
void EEPROMwrite(unsigned int uiAddress, unsigned char ucData)
{

    /* Wait for completion of previous write */
    while(EECR & (1<<EEPE));

    /* Set up address and Data Registers */
    EEAR = uiAddress;
    EEDR = ucData;

    /* Write logical one to EEMPE */
    EECR |= (1<<EEMPE);

    /* Start eeprom write by setting EEPE */
    EECR |= (1<<EEPE);
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


char usart_receive(){
	while ((UCSR0A & (1 << RXC0)) == 0){   //wait until RXC0 is set
	} 
	return UDR0;      //return the received character
}


int main(){

    usart_init(BAUD);

    unsigned char rec_sentence[1000];           //for receiving the sentence

    int counter = 0;                            //counter
   
    while(1){

        rec_sentence[counter] = usart_receive();
        if(rec_sentence[counter]=='\r'){
            break;
        }
        counter++;
    }

    
    int i;
    for(i=0;i<counter;i++){
         EEPROMwrite(i,rec_sentence[i]);
    }

    return 0;
}