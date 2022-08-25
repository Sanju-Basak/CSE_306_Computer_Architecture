/*
 * GccApplication3.c
 *
 * Created: 8/24/2022 4:33:59 PM
 * Author : User
 */ 

#include <avr/io.h>
int main(void)
{
	MCUCSR = (1<<JTD);
	MCUCSR = (1<<JTD); 
	DDRA= 0XFF;
	DDRB= 0XFF;
	DDRC= 0XFF;
	DDRD= 0XFF;
    /* Replace with your application code */
    while (1) 
    {
			PORTA= 0XFF;
			PORTB= 0XFF;
			PORTC= 0XFF;
			PORTD= 0XFF;
    }
}

