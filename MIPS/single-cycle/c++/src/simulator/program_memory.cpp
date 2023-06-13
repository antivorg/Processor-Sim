#include "../../inc/simulator/program_memory.hpp"

void program_memory::from_file(std::string file, std::string fileType) {

	std::ifstream fileIt(file);

	if (fileType == "binary") {
		for (std::string line; getline(fileIt, line);) {
			int value = std::stoi(line, 0, 2);
			instruction_t instruction = decode(value);
			program.push_back(instruction);
		}
	} else if (fileType == "assembly") {
		for (std::string line; getline(fileIt, line);) {
			instruction_t instruction = assemble(line);
			program.push_back(instruction);
		}
	}
}


// Needs testing
instruction_t program_memory::decode(int value) {

	instruction_t instruction;
	
	int opcode = (value >> 26) & (2^6-1);
	int funct = value & (2^6-1);
	switch (opcode) {
		// R-type
		case 0:
			instruction.opcode = rType;
			switch (funct) {
				case 0:
					instruction.funct = sll;
					break;
				case 0x1A:
                                        instruction.funct = div_e;
					break;
				case 0x1B:
                                        instruction.funct = divu;
					break;
				case 0x02:
                                        instruction.funct = srl;
                                        break;
				case 0x2A:
                                        instruction.funct = slt;
                                        break;
				case 0x2B:
                                        instruction.funct = sltu;
                                        break;
				case 0x03:
                                        instruction.funct = sra;
                                        break;
				case 0x08:
                                        instruction.funct = jr;
                                        break;
				case 0x09:
                                        instruction.funct = jalr;
                                        break;
				case 0x10:
                                        instruction.funct = mfhi;
                                        break;
				case 0x11:
                                        instruction.funct = mthi;
                                        break;
				case 0x12:
                                        instruction.funct = mflo;
                                        break;
				case 0x13:
                                        instruction.funct = mtlo;
                                        break;
				case 0x18:
                                        instruction.funct = mult;
                                        break;
				case 0x19:
                                        instruction.funct = multu;
                                        break;
				case 0x20:
                                        instruction.funct = add;
                                        break;
				case 0x21:
                                        instruction.funct = addu;
                                        break;
				case 0x22:
                                        instruction.funct = sub;
                                        break;
				case 0x23:
                                        instruction.funct = subu;
                                        break;
				case 0x24:
                                        instruction.funct = and_e;
                                        break;
				case 0x25:
                                        instruction.funct = or_e;
                                        break;
				case 0x26:
                                        instruction.funct = xor_e;
                                        break;
				case 0x27:
                                        instruction.funct = nor;
                                        break;
			}
			instruction.rd = (value>>11) & (2^5-1);
			instruction.shamt = (value>>6) & (2^5-1);
			break;
		// J-type, no regs needed, just return
                case 0x02:
                        instruction.opcode = j;
                        instruction.address = value & (2^26-1);
                        return instruction;
                case 0x03:
                        instruction.opcode = jal;
                        instruction.address = value & (2^26-1);
                        return instruction;
		// I-type
		case 0x0A:
                        instruction.opcode = slti;
                        break;
		case 0x0B:
                        instruction.opcode = sltiu;
                        break;
		case 0xc0:
                        instruction.opcode = andi;
                        break;
		case 0x0D:
                        instruction.opcode = ori;
                        break;
		case 0x0F:
                        instruction.opcode = lui;
                        break;
		case 0x2B:
                        instruction.opcode = sw;
                        break;
		case 0x04:
                        instruction.opcode = beq;
                        break;
		case 0x05:
                        instruction.opcode = bne;
                        break;
		case 0x06:
                        instruction.opcode = blez;
                        break;
		case 0x07:
                        instruction.opcode = bgtz;
                        break;
		case 0x08:
                        instruction.opcode = addi;
                        break;
		case 0x09:
                        instruction.opcode = addiu;
                        break;
		case 0x20:
                        instruction.opcode = lb;
                        break;
		case 0x23:
                        instruction.opcode = lw;
                        break;
		case 0x24:
                        instruction.opcode = lbu;
                        break;
		case 0x25:
                        instruction.opcode = lhu;
                        break;
		case 0x28:
                        instruction.opcode = sb;
                        break;
		case 0x29:
                        instruction.opcode = sh;
                        break;
		default:
			// Raise Error
			break;
	}
	// remaining regs for I- and R-type
	instruction.rs = (value>>21) & (2^5-1);
	instruction.rt = (value>>16) & (2^5-1);

	return instruction;
}


// Incomplete
instruction_t program_memory::assemble(std::string assembly) {

	instruction_t instruction;

	std::map<std::string, opcode_e> opcodeMap = {
    		{"add", rType},
    		{"addi", addi},
    		{"j", j}
	};
	std::map<std::string, funct_e> functMap = {
		{"add", add}
	};
	std::map<std::string, int> regMap = {
		{"$zero", 0}
	};

	std::string operation = assembly.substr(0, assembly.find(" "));
	if (opcodeMap.find(operation) == opcodeMap.end()) {
		// Raise error
		return instruction;
	} else {
		instruction.opcode = opcodeMap[operation];
	}

	return instruction;
}
