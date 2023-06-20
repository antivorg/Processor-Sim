#include "../../inc/utils/elf_parser.hpp"

namespace elf {

bool compare_sections_32(const section32_t& a, const section32_t& b) {

        return a.sh_offset < b.sh_offset ? true : (a.sh_offset == b.sh_offset ? a.sh_size < b.sh_size : false);
}


elf_parser* elf_parser::read_file(std::string file) {

	try {
		std::vector<std::uint8_t> bytes;
		if (std::filesystem::exists(file)) {
			std::ifstream fileIt(file, std::ios::binary);
        		bytes = std::vector<std::uint8_t>((std::istreambuf_iterator<char>(fileIt)),
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
                	return new elf_32_parser(bytes);
        	} else if (bytes[EI_CLASS_offset] == 2) {
                	// 64-bit format
                	return new elf_64_parser(bytes);
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
	//return new elf_error();
	}
}

unsigned int elf_parser::join_bytes(std::vector<std::uint8_t>::iterator ptr, int numOfBytes, bool bigEndian) {

	unsigned int result = 0;
	for (int i=0; i<numOfBytes; i++) {
		if (bigEndian) {
			result = result << 8;
			result += (std::uint8_t) *ptr;
		} else {
			result += ((std::uint8_t) *ptr) << (8*i);
        	}
        	ptr++;
	}
	return result;
}

elf_32_parser::elf_32_parser(std::vector<std::uint8_t> bytes) {

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
	for (int i=0x99; i<elfHeader.e_phnum; i++) {
		int offset = elfHeader.e_phoff + elfHeader.e_phentsize * i;
		std::cout << i << "\t" << offset << std::endl;
	}

	// parse section header
	for (int i=0; i<elfHeader.e_shnum; i++) {
		int offset = elfHeader.e_shoff + elfHeader.e_shentsize * i;
		section32_t header;
		header.sh_name = 	join_bytes(bytes.begin()+offset+sh_name_offset,		sh_name_size, bigEndian);
		header.sh_type = 	join_bytes(bytes.begin()+offset+sh_type_offset,		sh_type_size, bigEndian);
		header.sh_flags = 	join_bytes(bytes.begin()+offset+sh_flags_offset,	sh_flags_32_size, bigEndian);
		header.sh_addr = 	join_bytes(bytes.begin()+offset+sh_addr_32_offset,	sh_addr_32_size, bigEndian);
		header.sh_offset = 	join_bytes(bytes.begin()+offset+sh_offset_32_offset,	sh_offset_32_size, bigEndian);
		header.sh_size = 	join_bytes(bytes.begin()+offset+sh_size_32_offset,	sh_size_32_size, bigEndian);
		header.sh_link = 	join_bytes(bytes.begin()+offset+sh_link_32_offset,	sh_link_size, bigEndian);
		header.sh_info = 	join_bytes(bytes.begin()+offset+sh_info_32_offset,	sh_info_size, bigEndian);
		header.sh_addralign = 	join_bytes(bytes.begin()+offset+sh_addralign_32_offset,	sh_addralign_32_size, bigEndian);
		header.sh_entsize = 	join_bytes(bytes.begin()+offset+sh_entsize_32_offset,	sh_entsize_32_size, bigEndian);
		for (int i=header.sh_offset; i-header.sh_offset<header.sh_size; i++) {
			header.bytes.push_back(bytes[i]);
		}
		sectionHeaderTable.push_back(header);
	}

	// parser string table
	sectionHeader32_t stringTableHeader = sectionHeaderTable[elfHeader.e_shstrndx];
	for (section32_t &section : sectionHeaderTable) {
		if (section.sh_type == 0x00) {
			continue;
		}
		int offset = stringTableHeader.sh_offset + section.sh_name;
		std::string sectionName = "";
		while (bytes[offset] != '\0') {
			sectionName += bytes[offset];
			offset++;
		}
		section.name = sectionName;
	}
}


std::vector<std::uint8_t> elf_32_parser::read_section(std::string name) {

	section32_t section;
	for (section32_t sectionHeader : sectionHeaderTable) {
		if (sectionHeader.name == name) {
			section = sectionHeader;
		}
	}

	return section.bytes;
}


void elf_32_parser::print_sections(void) {

	std::cout << std::left << std::setfill(' ') << std::setw(18) << "Name";
	std::cout << std::left << std::setw(15) << "Type";
	std::cout << std::left << std::setw(9) << "Addr";
	std::cout << std::left << std::setw(7) << "Off";
	std::cout << std::left << std::setw(7) << "Size";
	std::cout << std::endl;
	std::vector<section32_t> sections = sectionHeaderTable;
	std::sort(sections.begin(), sections.end(), compare_sections_32);
	for (section32_t section : sections) {
		std::cout << std::left << std::setfill(' ') << std::setw(18) << section.name;
		std::cout << std::left << std::setw(15) << sectionType[section.sh_type];
		std::cout << std::right << std::setfill('0') << std::setw(8) << std::hex << section.sh_addr;
		std::cout << ' ' << std::right << std::setw(6) << std::hex << section.sh_offset;
		std::cout << ' ' << std::right << std::setw(6) << std::hex << section.sh_size;
		//std::cout << ' ' << std::right << std::setw(2) << std::hex << section.e_shstrndx;
		std::cout << std::endl;
	}
}


elf_64_parser::elf_64_parser(std::vector<std::uint8_t> bytes) {

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
