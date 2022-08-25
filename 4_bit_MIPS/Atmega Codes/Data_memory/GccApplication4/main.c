/*
 * GccApplication3.c
 *
 * Created: 8/24/2022 4:33:59 PM
 * Author : User
 */ 

#include <avr/io.h>
#include <util/delay.h>

int btoi(char c){
	int a=0;
	if(c==0x01){
		a=1;
	}
	else if(c==0x02){
		a=2;
	}
	else if(c==0x03){
		a=3;
	}
	
	else if(c==0x04){
		a=4;
	}
	
	else if(c==0x05){
		a=5;
	}
	
	else if(c==0x06){
		a=6;
	}
	else if(c==0x07){
		a=7;
	}
	else if(c==0x08){
		a=8;
	}
	else if(c==0x09){
		a=9;
	}
	else if(c==0x0A){
		a=10;
	}
	else if(c==0x0B){
		a=11;
	}
	else if(c==0x0C){
		a=12;
	}
	else if(c==0x0D){
		a=13;
	}
	else if(c==0x0E){
		a=14;
	}
	else if(c==0x0E){
		a=15;
	}
	return a;
}

int main(void)
{
	MCUCSR = (1<<JTD);
	MCUCSR = (1<<JTD); 
	DDRA= 0X00;
	DDRB= 0XF0;
	DDRD= 0xFF;
	
    /* Replace with your application code */
	
	//pb0-3 rdata2  input
	//pb4-7 writedata out
	// pa0-3 address/alures
	// pa4 -memwrite
	// pa5 -memread
	// pa6 -memto reg
	// pa7 - in
	
	unsigned char data[16],r2,wrData,AluResult,mWr,mRead,m_Reg;
	unsigned char c,in;
    while (1) 
    {
			
			c=PINA;
			AluResult=(c&0x0F);
			mWr=(c&0x10)>>4;
			mRead=(c&0x20)>>5;
			m_Reg=(c&0x40)>>6;
			in=(c&0x80)>>7;
			c=PINB;
			r2=(c&0x0F);
			
			wrData=AluResult;
			if(mRead&0x01 && m_Reg&0x01){
				wrData=data[btoi(AluResult)];
			}
			PORTD =wrData;
			
			if(!(in)){
				if(mWr){
					data[btoi(AluResult)]=r2;
				}
			}
			_delay_ms(2000);
    }
}

