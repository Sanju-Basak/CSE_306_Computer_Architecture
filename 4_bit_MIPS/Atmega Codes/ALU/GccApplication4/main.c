/*
 * GccApplication4.c
 *
 * Created: 8/24/2022 10:20:31 PM
 * Author : User
 */ 

#include <avr/io.h>
#define F_CPU 1000000
#include <util/delay.h>



int main(void){
	MCUCSR= (1<< JTD);
	MCUCSR= (1<< JTD);
	
	DDRB = 0x00;
	DDRA = 0x00; 
	DDRC = 0xFF;
	DDRD= 0xFF;
	
	// alu_op = pb1-3
	// alu_src = pb0
	// R#3 = pb4-7
	// R#1 = pa0-3
	// R#2 = pa4-7
	// alu_result = pc0-3
	// zf = PC7
	unsigned char alu_op,alu_src, alu_result;
	unsigned char r_3, r_2, r_1;
	signed char data_1;
	signed char data_2;
	unsigned char c;
	unsigned char zf;
	while (1) {
		c = PINA;
		r_1 = (c & 0x0F);	//take the lower 4 bit of the port
		r_2 = (c>>4);	//take the upper 4 bit of the port
		c = PINB;
		alu_op = (c & 0x0E) >> 1;// take bit from pb1 to pb3	
		alu_src = (c & 0x01);    // take bit from pb0
		r_3 = (c >> 4);	    //take the upper 4 bit of the port
		if (alu_src == 0x00) {
			data_2 = r_2;
		} else if(alu_src==0x01){
			data_2 = r_3;
		}
		
		data_1 = r_1;
		
		if (!(alu_op)) {
			alu_result = data_1 + data_2;
		}else if ((alu_op & 0x01)) {
			alu_result = data_1 - data_2;
			//alu_result = 0x02;
			
		}else if (alu_op & 0x02) {
			alu_result = data_1 & data_2;
		}else if (alu_op & 0x03) {
			alu_result = data_1 | data_2;
		}else if (alu_op & 0x04) {
			alu_result = data_1 << data_2;
		}else if (alu_op & 0x05) {
			alu_result = data_1 >> data_2;
		}else if (alu_op & 0x06) {
			alu_result = ~(data_1 | data_2);
		} else {
			alu_result = -1;
		}
		
		if (alu_result == 0) {
			zf = 1;
		}else {
			zf = 0;
		}
		PORTC = zf<<7;
		PORTD=alu_result;
		_delay_ms(100);
	}
}