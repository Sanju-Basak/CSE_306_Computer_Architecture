#include <avr/io.h>
#define F_CPU 1000000
#include <util/delay.h>
#define ALU_OP 4
#define ALU_SRC 7
#define BEQ 0
#define BNEQ 1
#define JMP 2
#define MEM_WR 5
#define MEM_READ 6
#define MEM_TO_REG 7
#define REG_DST 2
#define REG_WR 3

//Opcode PB4-7
//BEQ, BNEQ, JUMP PB0-2
//MEMWRITE, MEMREAD, MEMTOREG PC5-7
//REGDST, REGWRITE PD2-3
//ALUOP PD4-6
//ALUSRC PD7


int main(void)
{
	MCUCSR= (1<< JTD);
	MCUCSR= (1<< JTD);

	
	unsigned char opcode,aluop,alusrc;
	unsigned char jump,reg_dst,reg_wr,mem_read,mem_wr,mem_to_reg,beq,bneq;
	unsigned char c;
	DDRB=0b00001111;
	DDRC=0xff;
	DDRD=0xff;
	
	
	
	while (1)
	{
		opcode=PINB;
		opcode=opcode>>4;
		if(opcode==0x00){//addi
			aluop=0b000;
			alusrc=1;
			jump = 0;
			reg_dst = 0;
			reg_wr = 1;
			mem_read = 0;
			mem_wr = 0;
			mem_to_reg = 0;
			beq = 0;
			bneq = 0;
			
		}
		else if(opcode==0x01){//sll
			aluop=0b100;
			alusrc=1;
			jump = 0;
			reg_dst = 0;
			reg_wr = 1;
			mem_read = 0;
			mem_wr = 0;
			mem_to_reg = 0;
			beq = 0;
			bneq = 0;
		}
		else if(opcode==0x02){//beq
			aluop=0b001;
			alusrc=0;
			jump = 0;
			reg_dst = 0;
			reg_wr = 0;
			mem_read = 0;
			mem_wr = 0;
			mem_to_reg = 0;
			beq = 1;
			bneq = 0;
		}
		else if(opcode==0x03){//ori
			aluop=0b011;
			alusrc=1;
			jump = 0;
			reg_dst = 0;
			reg_wr = 1;
			mem_read = 0;
			mem_wr = 0;
			mem_to_reg = 0;
			beq = 0;
			bneq = 0;
		}
		else if(opcode==0x04){//and
			aluop=0b010;
			alusrc=0;
			jump = 0;
			reg_dst = 1;
			reg_wr = 1;
			mem_read = 0;
			mem_wr = 0;
			mem_to_reg = 0;
			beq = 0;
			bneq = 0;
		}
		else if(opcode==0x05){//nor
			aluop=0b110;
			alusrc=0;
			jump = 0;
			reg_dst = 1;
			reg_wr = 1;
			mem_read = 0;
			mem_wr = 0;
			mem_to_reg = 0;
			beq = 0;
			bneq = 0;
		}
		else if(opcode==0x06){//lw
			aluop=0b000;
			alusrc=1;
			jump = 0;
			reg_dst = 0;
			reg_wr = 1;
			mem_read = 1;
			mem_wr = 0;
			mem_to_reg = 1;
			beq = 0;
			bneq = 0;
		}
		else if(opcode==0x07){//sw
			aluop=0b000;
			alusrc=1;
			jump = 0;
			reg_dst = 0;
			reg_wr = 0;
			mem_read = 0;
			mem_wr = 1;
			mem_to_reg = 0;
			beq = 0;
			bneq = 0;
		}
		else if(opcode==0x08){//subi
			aluop=0b001;
			alusrc=1;
			jump = 0;
			reg_dst = 0;
			reg_wr = 1;
			mem_read = 0;
			mem_wr = 0;
			mem_to_reg = 0;
			beq = 0;
			bneq = 0;
		}
		else if(opcode==0x09){//sub
			aluop=0b001;
			alusrc=0;
			jump = 0;
			reg_dst = 1;
			reg_wr = 1;
			mem_read = 0;
			mem_wr = 0;
			mem_to_reg = 0;
			beq = 0;
			bneq = 0;
		}
		else if(opcode==0x0A){//srl
			aluop=0b101;
			alusrc=1;
			jump = 0;
			reg_dst = 0;
			reg_wr = 1;
			mem_read = 0;
			mem_wr = 0;
			mem_to_reg = 0;
			beq = 0;
			bneq = 0;
		}
		else if(opcode==0x0B){//bneq
			aluop=0b001;
			alusrc=0;
			jump = 0;
			reg_dst = 0;
			reg_wr = 0;
			mem_read = 0;
			mem_wr = 0;
			mem_to_reg = 0;
			beq = 0;
			bneq = 1;
		}
		else if(opcode==0x0C){//or
			aluop=0b011;
			alusrc=0;
			jump = 0;
			reg_dst = 1;
			reg_wr = 1;
			mem_read = 0;
			mem_wr = 0;
			mem_to_reg = 0;
			beq = 0;
			bneq = 0;
		}
		else if(opcode==0x0D){//jmp
			aluop=0b000;
			alusrc=0;
			jump = 1;
			reg_dst = 0;
			reg_wr = 0;
			mem_read = 0;
			mem_wr = 0;
			mem_to_reg = 0;
			beq = 0;
			bneq = 0;
		}
		else if(opcode==0x0E){//add
			aluop=0b000;
			alusrc=0;
			jump = 0;
			reg_dst = 1;
			reg_wr = 1;
			mem_read = 0;
			mem_wr = 0;
			mem_to_reg = 0;
			beq = 0;
			bneq = 0;
		}
		else if(opcode==0x0F){//andi
			aluop=0b010;
			alusrc=1;
			jump = 0;
			reg_dst = 0;
			reg_wr = 1;
			mem_read = 0;
			mem_wr = 0;
			mem_to_reg = 0;
			beq = 0;
			bneq = 0;
		} else {
			aluop=0b000;
			alusrc=0;
			jump = 0;
			reg_dst = 0;
			reg_wr = 0;
			mem_read = 0;
			mem_wr = 0;
			mem_to_reg = 0;
			beq = 0;
			bneq = 0;
		}
		
		c = 0x00 | (beq << BEQ) | (bneq << BNEQ) | (jump << JMP);
		PORTB = c;
		c = 0x00 | (mem_wr << MEM_WR) | (mem_read << MEM_READ) | (mem_to_reg << MEM_TO_REG);
		PORTC = c;
		c = 0x00 | (reg_dst << REG_DST) | (reg_wr << REG_WR) | (aluop << ALU_OP) | (alusrc << ALU_SRC);
		PORTD = c;
	}
}
