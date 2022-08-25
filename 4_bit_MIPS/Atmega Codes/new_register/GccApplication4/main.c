#include <avr/io.h>
#define F_CPU 1000000
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
	return a;
}

int main(void)
{
	MCUCSR= (1<< JTD);
	MCUCSR= (1<< JTD);

	unsigned char reg[6],reg1,reg2,reg3,a,b,value1,value2,data_in,data_out;
	unsigned char reg_dst,reg_write;
	unsigned char in;
	//pb0-3 reg1
	//pb4-7 reg2
	//pa0-3 reg3
	//pa5- regdest
	//pa6 -regwrite
	//pa7 in
	//pc0-3 data2	--output
	//pc4-7data1    --output
	//pd4-7 writedata  --input
	//pd0-3 reg#3 output
	DDRA=0x00;
	DDRB=0x00;
	DDRC=0xff;
	DDRD=0x0f;
	
	
	
	for(int i=0;i<6;i++){
		reg[i]=0x00;
	}
	//only for test case
	
	
	
	
	while (1)
	{
		b=PINB;
		reg1=b&(0x0f); //lower 4 bit
		reg2=(b>>4)&(0x0f); // higher 4 bit
		
		value1=reg[reg1];
		value2=reg[reg2];
		PORTC=(value1<<4)|value2;//1 upper bit 2 lower bit
		
		data_in=PIND;
		data_in=data_in>>4;//aluresult or write data
		
		
		a=PINA;
		reg3=a&(0x0f); // lower half
		
		reg_dst=(a&(0x20))>>5; // pin5
		reg_write=(a&(0x40))>>6; //pin6
		in =(a&(0x80))>>7;  //pin7
		
		if(!(in)){//when in 1 (button press) only then writes the data to the register
			if(reg_write&(0x01)){
				char d;
				if(reg_dst&(0x01)){
					d=reg3&0x07;//cut off the 4th bit of reg3
					reg[btoi(d)]=data_in;
				}
				else{
					d=reg2&0x07;//cut off the 4th bit of reg2
					reg[btoi(d)]=data_in;
				}
			}
		}
		
		/*if(selection_bit==0){
			data_out=0;
		}
		else if(selection_bit==1){
			data_out=reg[reg1];
		}
		else if(selection_bit==2){
			data_out=reg[reg2];
		}
		else if(selection_bit==3){
			data_out=reg[reg3];
		}
		else{
			data_out=0;
		}*/
		data_out=reg[reg3];
		PORTD=data_out;
		
		_delay_ms(5000);
	}
}
