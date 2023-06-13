
#ifndef PROG_MEM_H
#define PROG_MEM_H


#include <fstream>
#include <vector>
#include <map>


#include "../utils/elf_parser.hpp"


enum opcode_e {
	rType,
	j,
	jal,
	addi,
	addiu,
	andi,
	beq,
	blez,
	bne,
	bgtz,
	lb,
	lbu,
	lhu,
	lui,
	lw,
	ori,
	sb,
	sh,
	slti,
	sltiu,
	sw
};

enum funct_e {
	sll,
	div_e,
	divu,
	srl,
	slt,
	sltu,
	sra,
	jr,
	jalr,
	mfhi,
	mthi,
	mflo,
	mtlo,
	mult,
	multu,
	add,
	addu,
	sub,
	subu,
	and_e,
	or_e,
	xor_e,
	nor
};

typedef struct instruction_t {
	opcode_e opcode;
	funct_e funct;
	int rs;
	int rt;
	int rd;
	int shamt;
	int immediate;
	int address;
} instruction_t;


class program_memory {

	private:
		std::vector<instruction_t> program;
		int instructionPoinrter;

	public:
		void from_file(std::string file, std::string fileType);

		instruction_t instructFetch();
		void pcIncrement();
		void pcJump(int address);

	private:
		instruction_t decode(int value);
		instruction_t assemble(std::string instruction);

};


#endif

