#include <avr/io.h>
#define F_CPU 1000000
#include <util/delay.h>


int main(void)
{
	MCUCSR= (1<< JTD);
	MCUCSR= (1<< JTD);

	
	unsigned char pc=0x00;
	unsigned char reg1,reg2,reg3;
	unsigned char beq,bneq,zf,j;
	unsigned char in;
	unsigned char c;
	//pb0-8 pcin --out
	//pd4-7 reg2
	//pd0-3 reg1
	//pc0-3 reg3
	//pa0 - beq
	//pa1 - bneq
	//pa2 - zf
	//pa3 - j
	//pa7 - in
	//
	DDRA=0x00;//input
	DDRB=0xff;//output
	DDRC=0x00;
	DDRD=0x00;
	
	
	
	unsigned char jump;
	unsigned char pc2,pc3,pcout;
	unsigned char offset;
	unsigned char pcb;
	unsigned char s;
	unsigned char j_select=0;
	
	while (1)
	{
		PORTB=pc;
		c=PIND;
		reg1=(c&0x0F); //taking the lower 4 bit of pin
		reg2=(c&0xF0)>>4;		//taking the higher 4 bit of the pin
		c=PINC;
		reg3=(c&0x0F);	//taking the lower 4 bit of the pin
		c=PINA;
		beq=(c&0x01);
		bneq=(c&0x02)>>1;
		zf=(c&0x04)>>2;
		j=(c&0x08)>>3;
		in=(c&0x80)>>7;
		jump = reg2 | (reg1<<4);
		
		pc2=pc+1;
		s=(reg3&0x08)>>3;
		if(s&0x01){
			offset=(reg3)|(0xF0);
		}
		else {
			offset = (reg3) | (0x00);
		}
		pcb =pc2+offset;
		j_select=0;
		if(zf&0x01){
			if(beq&0x01){
				j_select=1;
			}
		}
		else{
			if(bneq&0x01){
				j_select=1;
			}
		}
		if(j_select&0x01){
			pc3=pcb;
			}else {
			pc3=pc2;
		}
		
		if(j&0x01){
			pcout=jump;
		}
		else {
			pcout = pc3;
		}
		
		if(!in){
			pc=pcout;
			PORTB = pc;
			_delay_ms(500);
		}
	}
}
