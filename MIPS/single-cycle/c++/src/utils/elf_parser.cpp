#include "../../inc/utils/elf_parser.hpp"


elf_parser elf_parser::read_file(std::string file) {
	
	std::ifstream fileIt(file, std::ios::binary);
	std::vector<char> bytes((std::istreambuf_iterator<char>(fileIt)),
				(std::istreambuf_iterator<char>()));
	fileIt.close();

	if (bytes[4] == 1) {
		// 32-bit format
		return elf_32_parser(bytes);
	} else {
		// 64-bit format
		return elf_64_parser(bytes);
	}
}


int elf_parser::join_bytes(std::vector<char>::iterator ptr, int numOfBytes, bool bigEndian) {

	int result=0;

	for (int i=0; i<numOfBytes; i++) {
		if (bigEndian) {
			result = result<<8;
			result += *ptr;
		} else {
			result += (*ptr) << (8*i);
		}
		ptr++;
	}

	return result;
}


elf_32_parser::elf_32_parser(std::vector<char> bytes) {

	// Parse Header
	elfHeader.e_ident.EI_OSABI = bytes[7];
        elfHeader.e_ident.EI_ABIVERSION = bytes[8];
	
	bool bigEndian = bytes[5] == 2;

	elfHeader.e_type = join_bytes(bytes.begin()+10, 2, bigEndian);
	elfHeader.e_machine = join_bytes(bytes.begin()+12, 2, bigEndian);
	elfHeader.e_version = join_bytes(bytes.begin()+14, 4, bigEndian);
	elfHeader.e_entry = join_bytes(bytes.begin()+18, 4, bigEndian);
	elfHeader.e_phoff = join_bytes(bytes.begin()+0x1C, 4, bigEndian);
	elfHeader.e_shoff = join_bytes(bytes.begin()+0x20, 4, bigEndian);
	elfHeader.e_flags = join_bytes(bytes.begin()+0x24, 4, bigEndian);
	elfHeader.e_ehsize = join_bytes(bytes.begin()+0x28, 2, bigEndian);
	elfHeader.e_phentsize = join_bytes(bytes.begin()+0x2A, 2, bigEndian);
	elfHeader.e_phnum = join_bytes(bytes.begin()+0x2C, 2, bigEndian);
	elfHeader.e_shentsize = join_bytes(bytes.begin()+0x2E, 2, bigEndian);
	elfHeader.e_shnum = join_bytes(bytes.begin()+0x30, 2, bigEndian);
	elfHeader.e_shstrndx = join_bytes(bytes.begin()+0x32, 2, bigEndian);

}

elf_64_parser::elf_64_parser(std::vector<char> bytes) {

	// Parse Header
        elfHeader.e_ident.EI_OSABI = bytes[7];
        elfHeader.e_ident.EI_ABIVERSION = bytes[8];

        bool bigEndian = bytes[5] == 2;

        elfHeader.e_type = join_bytes(bytes.begin()+10, 2, bigEndian);
        elfHeader.e_machine = join_bytes(bytes.begin()+12, 2, bigEndian);
        elfHeader.e_version = join_bytes(bytes.begin()+14, 4, bigEndian);
        elfHeader.e_entry = join_bytes(bytes.begin()+18, 8, bigEndian);
        elfHeader.e_phoff = join_bytes(bytes.begin()+0x20, 8, bigEndian);
        elfHeader.e_shoff = join_bytes(bytes.begin()+0x28, 8, bigEndian);
        elfHeader.e_flags = join_bytes(bytes.begin()+0x30, 4, bigEndian);
        elfHeader.e_ehsize = join_bytes(bytes.begin()+0x34, 2, bigEndian);
        elfHeader.e_phentsize = join_bytes(bytes.begin()+0x36, 2, bigEndian);
        elfHeader.e_phnum = join_bytes(bytes.begin()+0x38, 2, bigEndian);
        elfHeader.e_shentsize = join_bytes(bytes.begin()+0x3A, 2, bigEndian);
        elfHeader.e_shnum = join_bytes(bytes.begin()+0x3C, 2, bigEndian);
        elfHeader.e_shstrndx = join_bytes(bytes.begin()+0x3E, 2, bigEndian);

}
