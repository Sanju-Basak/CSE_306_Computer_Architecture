#include <avr/io.h>
#define F_CPU 1000000
#include <util/delay.h>

int main(void)
{
	MCUCSR= (1<< JTD);
	MCUCSR= (1<< JTD);

	unsigned int instruction_ara [] = {0x0023,0x803e,0xe231,0x9234,0x5135,0x7323,0xa331,0x2341,0xd140,0x1441,0x6334,0xd130,0xc131,0xa552,0xf531,0x1551,0x3225,0xf324,0xd140,0xb138};
	unsigned int instruction;
	unsigned char address,x,y,c=0,d=0;
	DDRB=0x00;
	DDRC=0xff;
	DDRD=0xff;
	
	
	while (1)
	{
		address=PINB;
		instruction=instruction_ara[address];
		x=instruction;
		y=instruction>>8;
		c=(y&(0xf0))|(x&(0x0f));
		d=(y&(0x0f))|(x&(0xf0));
		
		PORTC=c;
		PORTD=d;
		_delay_ms(100);
	}
}
