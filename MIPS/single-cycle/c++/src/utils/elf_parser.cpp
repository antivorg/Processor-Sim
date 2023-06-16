#include "../../inc/utils/elf_parser.hpp"

namespace elf {

elf_parser elf_parser::read_file(std::string file) {

	try {
		std::vector<char> bytes;
		if (std::filesystem::exists(file)) {
			std::ifstream fileIt(file, std::ios::binary);
        		bytes = std::vector<char>((std::istreambuf_iterator<char>(fileIt)),
                		                (std::istreambuf_iterator<char>()));
        		fileIt.close();
		} else {
			throw 0;
		}

		if (bytes[0] != 0x7F || bytes[1] != 0x45
				|| bytes[2] != 0x4c || bytes[3] != 0x46) {
			throw 1;
		}

		if (bytes[EI_CLASS_offset] == 1) {
                	// 32-bit format
                	return elf_32_parser(bytes);
        	} else if (bytes[EI_CLASS_offset] == 2) {
                	// 64-bit format
                	return elf_64_parser(bytes);
        	} else {
			throw 2;
		}
	}
 	catch (int e) {
		switch(e) {
			case 0:
				std::cout << "Exception: File doesn't exist" << std::endl;
				break;
			case 1:
				std::cout << "Exception: Incorrect magic number for ELF format"
						<< std::endl;
				break;
			case 2:
				std::cout << "Exception: Unexpected value in ELF header" << std::endl;
				break;
		}
	}
}


int elf_parser::join_bytes(std::vector<char>::iterator ptr, int numOfBytes, bool bigEndian) {

	unsigned int result=0;
	for (int i=0; i<numOfBytes; i++) {
		if (bigEndian) {
			result = result << 8;
			result += *ptr;
		} else {
			result += (*ptr) << (8*i);
		}
		ptr++;
	}

	return result;
}


elf_32_parser::elf_32_parser(std::vector<char> bytes) {

	std::cout<<"32"<<std::endl;
	
	// parse file header
	elfHeader.e_ident.EI_OSABI = bytes[EI_OSABI_offset];
        elfHeader.e_ident.EI_ABIVERSION = bytes[EI_ABIVERSION_offset];
	bool bigEndian = bytes[EI_DATA_offset] == 2;
	elfHeader.e_type = 	join_bytes(bytes.begin()+e_type_offset, 	e_type_size, bigEndian);
	elfHeader.e_machine = 	join_bytes(bytes.begin()+e_machine_offset, 	e_machine_size, bigEndian);
	elfHeader.e_version = 	join_bytes(bytes.begin()+e_version_offset, 	e_version_size, bigEndian);
	elfHeader.e_entry = 	join_bytes(bytes.begin()+e_entry_offset, 	e_entry_32_size, bigEndian);
	elfHeader.e_phoff = 	join_bytes(bytes.begin()+e_phoff_32_offset, 	e_phoff_32_size, bigEndian);
	elfHeader.e_shoff = 	join_bytes(bytes.begin()+e_shoff_32_offset, 	e_shoff_32_size, bigEndian);
	elfHeader.e_flags = 	join_bytes(bytes.begin()+e_flags_32_offset, 	e_flags_size, bigEndian);
	elfHeader.e_ehsize = 	join_bytes(bytes.begin()+e_ehsize_32_offset, 	e_ehsize_size, bigEndian);
	elfHeader.e_phentsize = join_bytes(bytes.begin()+e_phentsize_32_offset, e_phentsize_size, bigEndian);
	elfHeader.e_phnum = 	join_bytes(bytes.begin()+e_phnum_32_offset, 	e_phnum_size, bigEndian);
	elfHeader.e_shentsize = join_bytes(bytes.begin()+e_shentsize_32_offset, e_shentsize_size, bigEndian);
	elfHeader.e_shnum = 	join_bytes(bytes.begin()+e_shnum_32_offset, 	e_shnum_size, bigEndian);
	elfHeader.e_shstrndx = 	join_bytes(bytes.begin()+e_shstrndx_32_offset, 	e_shstrndx_size, bigEndian);

	// parse program headers
	for (int i=0; i<elfHeader.e_phnum; i++) {
		int offset = elfHeader.e_phoff + elfHeader.e_phentsize*i;
		std::cout << i << "\t" << offset << std::endl;
	}
	std::cout<<elfHeader.e_phnum<<std::endl;

}

elf_64_parser::elf_64_parser(std::vector<char> bytes) {

	std::cout<<"64"<<std::endl;
	
	// parse file header
        elfHeader.e_ident.EI_OSABI = bytes[7];
        elfHeader.e_ident.EI_ABIVERSION = bytes[8];
        bool bigEndian = bytes[5] == 2;
        elfHeader.e_type = 	join_bytes(bytes.begin()+e_type_offset, 	e_type_size, bigEndian);
        elfHeader.e_machine = 	join_bytes(bytes.begin()+e_machine_offset, 	e_machine_size, bigEndian);
        elfHeader.e_version = 	join_bytes(bytes.begin()+e_version_offset, 	e_version_size, bigEndian);
        elfHeader.e_entry = 	join_bytes(bytes.begin()+e_entry_offset, 	e_entry_64_size, bigEndian);
        elfHeader.e_phoff = 	join_bytes(bytes.begin()+e_phoff_64_offset, 	e_phoff_64_size, bigEndian);
        elfHeader.e_shoff = 	join_bytes(bytes.begin()+e_shoff_64_offset, 	e_shoff_64_size, bigEndian);
        elfHeader.e_flags = 	join_bytes(bytes.begin()+e_flags_64_offset, 	e_flags_size, bigEndian);
        elfHeader.e_ehsize = 	join_bytes(bytes.begin()+e_ehsize_64_offset, 	e_ehsize_size, bigEndian);
        elfHeader.e_phentsize = join_bytes(bytes.begin()+e_phentsize_64_offset, e_phentsize_size, bigEndian);
        elfHeader.e_phnum = 	join_bytes(bytes.begin()+e_phnum_64_offset, 	e_phnum_size, bigEndian);
        elfHeader.e_shentsize = join_bytes(bytes.begin()+e_shentsize_64_offset, e_shentsize_size, bigEndian);
        elfHeader.e_shnum = 	join_bytes(bytes.begin()+e_shnum_64_offset, 	e_shnum_size, bigEndian);
        elfHeader.e_shstrndx = 	join_bytes(bytes.begin()+e_shstrndx_64_offset, 	e_shstrndx_size, bigEndian);

	// parse program headers
        for (int i=0; i<elfHeader.e_phnum; i++) {
                int offset = elfHeader.e_phoff + elfHeader.e_phentsize*i;
                std::cout << i << "\t" << offset << std::endl;
        }
        std::cout<<elfHeader.e_phnum<<std::endl;
}

} // end of namespace elf
