#include <avr/io.h>

/* 
	Baud rate = fosc/(16*(x+1))
	9600 = 16M/16(x+1)
	x = 103.166 ~ 103  
*/


void usart_init(){

	UCSR0B  |= (1 << RXEN0 ); 				// Enable the USART receiver
	UCSR0B  |= (1 << TXEN0 ); 				// Enable the USART transmitter
	
	UCSR0C &= ~(1<<UPM01 | 1<<UPM00);		//No parity
	UCSR0C &= ~(1<<USBS0);					//1 stop bit
	
	UCSR0C |= (1<<UCSZ00) | (1<<UCSZ01);  	//8 bit data frame
	UCSR0B &= ~(1<<UCSZ02);
	
	UBRR0 = 103;  					 		//set baud rate
	
}

void usart_send(char one_char){
	
	while (!(UCSR0A & (1<<UDRE0)));    		//wait until UDRE0 bit is set
	UDR0 = one_char;						//character is written to UDR0 register

}

char usart_receive(){
	
	while ((UCSR0A & (1 << RXC0)) == 0);   	//wait until RXC0 is set
	return UDR0;      						//return the received character

}



int main(){
	
	usart_init();
	
	char ch_arr[1000];
	
	while(1){
	
		int counter = 0;
	   
			while(1){

				ch_arr[counter] = usart_receive();
				if(ch_arr[counter]=='\r'){
					break;
				}
				counter++;
			}
		
		
		
		//char ch = ch_arr[0];
		int i = 0;
		
		while(ch_arr[i] != '\r'){									// loop work untill carriage return is received
			
			
			
			//ch_arr[i] = usart_receive();							// receiving the char
			
			if(ch_arr[i]>='A' && ch_arr[i]<='Z'){
				ch_arr[i] =((ch_arr[i] - 'A' + 3) % 26 + 'A' );		//getting the cipher character with key = 3
			}
			
			else if(ch_arr[i]>='a' && ch_arr[i]<='z'){
				ch_arr[i] =((ch_arr[i] - 'a' + 3) % 26 + 'a' );		//getting the cipher character with key = 3
			}
			
			usart_send(ch_arr[i]); 								// send the character after only encrypt alphabetic characters(Lower and Upper)
			i++;
		}
	
	}
	return 0;
	
}