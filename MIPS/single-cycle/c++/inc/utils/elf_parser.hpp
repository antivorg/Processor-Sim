
#ifndef ELF_PARSE_H
#define ELF_PARSE_H


#include <fstream>
#include <filesystem>
#include <iterator>
#include <vector>
#include <string>
#include <iostream>


namespace elf {

constexpr int EI_MAG_offset =		0x00;
constexpr int EI_CLASS_offset =   	0x04;
constexpr int EI_DATA_offset =    	0x05;
constexpr int EI_VERSION_offset = 	0x06;
constexpr int EI_OSABI_offset =   	0x07;
constexpr int EI_ABIVERSION_offset =	0x08;
constexpr int EI_PAD_offset = 		0x09;
constexpr int e_type_offset = 		0x10;
constexpr int e_machine_offset =  	0x12;
constexpr int e_version_offset =  	0x14;
constexpr int e_entry_offset =    	0x18;
constexpr int e_phoff_32_offset = 	0x1C;
constexpr int e_phoff_64_offset = 	0x20;
constexpr int e_shoff_32_offset = 	0x20;
constexpr int e_shoff_64_offset = 	0x28;
constexpr int e_flags_32_offset = 	0x24;
constexpr int e_flags_64_offset = 	0x30;
constexpr int e_ehsize_32_offset =    	0x28;
constexpr int e_ehsize_64_offset =    	0x34;
constexpr int e_phentsize_32_offset = 	0x2A;
constexpr int e_phentsize_64_offset = 	0x36;
constexpr int e_phnum_32_offset = 	0x2C;
constexpr int e_phnum_64_offset = 	0x38;
constexpr int e_shentsize_32_offset = 	0x2E;
constexpr int e_shentsize_64_offset = 	0x3A;
constexpr int e_shnum_32_offset = 	0x30;
constexpr int e_shnum_64_offset = 	0x3C;
constexpr int e_shstrndx_32_offset =  	0x32;
constexpr int e_shstrndx_64_offset =  	0x3E;

constexpr int EI_MAG_size = 		4;
constexpr int EI_CLASS_size = 		1;
constexpr int EI_DATA_size = 		1;
constexpr int EI_VERSION_size = 	1;
constexpr int EI_OSABI_size = 		1;
constexpr int EI_ABIVERSION_size = 	1;
constexpr int EI_PAD_size = 		7;
constexpr int e_type_size = 		2;
constexpr int e_machine_size = 		2;
constexpr int e_version_size = 		4;
constexpr int e_entry_32_size = 	4;
constexpr int e_entry_64_size = 	8;
constexpr int e_phoff_32_size = 	4;
constexpr int e_phoff_64_size = 	8;
constexpr int e_shoff_32_size = 	4;
constexpr int e_shoff_64_size = 	8;
constexpr int e_flags_size = 		4;
constexpr int e_ehsize_size = 		2;
constexpr int e_phentsize_size = 	2;
constexpr int e_phnum_size = 		2;
constexpr int e_shentsize_size = 	2;
constexpr int e_shnum_size = 		2;
constexpr int e_shstrndx_size = 	2;

// Program Header
constexpr int p_type_offset =		0x00;
constexpr int p_flags_32_offset =	0x18;
constexpr int p_flags_64_offset =	0x04;
constexpr int p_offset_32_offset =	0x04;
constexpr int p_offset_64_offset = 	0x08;
constexpr int p_vaddr_32_offset = 	0x08;
constexpr int p_vaddr_64_offset = 	0x10;
constexpr int p_paddr_32_offset = 	0x0C;
constexpr int p_paddr_64_offset = 	0x18;
constexpr int p_filesz_32_offset = 	0x10;
constexpr int p_filesz_64_offset = 	0x20;
constexpr int p_memsz_32_offset = 	0x14;
constexpr int p_memsz_64_offset = 	0x28;
constexpr int p_align_32_offset = 	0x1C;
constexpr int p_align_64_offset = 	0x30;

constexpr int p_type_size =		4;
constexpr int p_flags_size =		4;
constexpr int p_offset_32_size =	4;
constexpr int p_offset_64_size =	8;
constexpr int p_vaddr_32_size =		4;
constexpr int p_vaddr_64_size =		8;
constexpr int p_paddr_32_size =		4;
constexpr int p_paddr_64_size =		8;
constexpr int p_filesz_32_size =	4;
constexpr int p_filesz_64_size =	8;
constexpr int p_memsz_32_size =		4;
constexpr int p_memsz_64_size =		8;
constexpr int p_align_32_size =		4;
constexpr int p_align_64_size =		8;

// Section Header
constexpr int sh_name_offset =		0x00;
constexpr int sh_type_offset =		0x04;
constexpr int sh_flags_offset =		0x08;
constexpr int sh_addr_32_offset =	0x0C;
constexpr int sh_addr_64_offset =	0x10;
constexpr int sh_offset_32_offset =	0x10;
constexpr int sh_offset_64_offset =	0x18;
constexpr int sh_size_32_offset =	0x14;
constexpr int sh_size_64_offset =	0x20;
constexpr int sh_link_32_offset =	0x18;
constexpr int sh_link_64_offset =	0x28;
constexpr int sh_info_32_offset =	0x1C;
constexpr int sh_info_64_offset =	0x2C;
constexpr int sh_addralign_32_offset =	0x20;
constexpr int sh_addralign_64_offset =	0x30;
constexpr int sh_entsize_32_offset =	0x24;
constexpr int sh_entsize_64_offset =	0x38;

constexpr int sh_name_size =		4;
constexpr int sh_type_size =		4;
constexpr int sh_flags_32_size =	4;
constexpr int sh_flags_64_size =	8;
constexpr int sh_addr_32_size =		4;
constexpr int sh_addr_64_size =		8;
constexpr int sh_offset_32_size =	4;
constexpr int sh_offset_64_size =	8;
constexpr int sh_size_32_size =		4;
constexpr int sh_size_64_size =		8;
constexpr int sh_link_size =		4;
constexpr int sh_info_size =		4;
constexpr int sh_addralign_32_size =	4;
constexpr int sh_addralign_64_size =	8;
constexpr int sh_entsize_32_size =	4;
constexpr int sh_entsize_64_size =	8;

typedef std::uint32_t Elf32_Addr;
typedef std::uint16_t Elf32_Half;
typedef std::uint32_t Elf32_Off;
typedef std::uint32_t Elf32_Sword;
typedef std::uint32_t Elf32_Word;

typedef std::uint64_t Elf64_Addr;
typedef std::uint16_t Elf64_Half;
typedef std::uint64_t Elf64_Off;
typedef std::uint64_t Elf64_Sword;
typedef std::uint32_t Elf64_Word;

typedef struct e_ident_t {
	std::uint8_t EI_OSABI;
	std::uint8_t EI_ABIVERSION;
} e_ident_t;

typedef struct elf32Header_t {
	e_ident_t e_ident;
	Elf32_Half e_type;
	Elf32_Half e_machine;
	Elf32_Word e_version;
	Elf32_Addr e_entry;
	Elf32_Off e_phoff;
	Elf32_Off e_shoff;
	Elf32_Word e_flags;
	Elf32_Half e_ehsize;
	Elf32_Half e_phentsize;
	Elf32_Half e_phnum;
	Elf32_Half e_shentsize;
	Elf32_Half e_shnum;
	Elf32_Half e_shstrndx;
} elf32Header_t;

typedef struct elf64Header_t {
        e_ident_t e_ident;
        Elf64_Half e_type;
        Elf64_Half e_machine;
        Elf64_Word e_version;
        Elf64_Addr e_entry;
        Elf64_Off e_phoff;
        Elf64_Off e_shoff;
        Elf64_Word e_flags;
        Elf64_Half e_ehsize;
        Elf64_Half e_phentsize;
        Elf64_Half e_phnum;
        Elf64_Half e_shentsize;
        Elf64_Half e_shnum;
        Elf64_Half e_shstrndx;
} elf64Header_t;

typedef struct programHeader_t {
	int p_type;
	int p_flags;
	int p_offset;
	int p_vaddr;
	int p_paddr;
	int p_filesz;
	int p_memsz;
	int p_flags_seg;
	int p_align;
} programHeader_t;


class elf_parser {

	// Factory
	public:
		static elf_parser read_file(std::string file);
		int join_bytes(std::vector<char>::iterator ptr, int numOfBytes, bool bigEndian);

};


class elf_32_parser : public elf_parser {

	private:
                elf32Header_t elfHeader;
		std::vector<programHeader_t> programHeaders;
                std::vector<unsigned int> sectionHeaderTable;

	public:
		elf_32_parser(std::vector<char> bytes);

};


class elf_64_parser : public elf_parser {

	private:
                elf64Header_t elfHeader;
		std::vector<programHeader_t> programHeaders;
                std::vector<unsigned int> sectionHeaderTable;

	public:
		elf_64_parser(std::vector<char> bytes);

};

} // end of namespace elf

#endif
