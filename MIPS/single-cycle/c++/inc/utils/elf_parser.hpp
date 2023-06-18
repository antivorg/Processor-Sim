
#ifndef ELF_PARSE_H
#define ELF_PARSE_H


#include <fstream>
#include <filesystem>
#include <iterator>
#include <vector>
#include <string>
#include <iostream>


namespace elf {

// elf header
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
typedef std::int32_t Elf32_Sword;
typedef std::uint32_t Elf32_Word;

typedef std::uint64_t Elf64_Addr;
typedef std::uint16_t Elf64_Half;
typedef std::uint64_t Elf64_Off;
typedef std::int64_t Elf64_Sword;
typedef std::uint32_t Elf64_Word;
typedef std::uint64_t Elf64_Xword;

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

typedef struct programHeader32_t {
	Elf32_Word p_type;
	Elf32_Off p_offset;
	Elf32_Addr p_vaddr;
	Elf32_Addr p_paddr;
	Elf32_Word p_filesz;
	Elf32_Word p_memsz;
	Elf32_Word p_flags;
	Elf32_Word p_align;
} programHeader32_t;

typedef struct programHeader64_t {
        Elf64_Word p_type;
        Elf64_Off p_offset;
        Elf64_Addr p_vaddr;
        Elf64_Addr p_paddr;
        Elf64_Xword p_filesz;
        Elf64_Xword p_memsz;
        Elf64_Word p_flags;
        Elf64_Xword p_align;
} programHeader64_t;

typedef struct sectionHeader32_t {
	Elf32_Word sh_name;
	Elf32_Word sh_type;
	Elf32_Word sh_flags;
	Elf32_Addr sh_addr;
	Elf32_Off sh_offset;
	Elf32_Word sh_size;
	Elf32_Word sh_link;
	Elf32_Word sh_info;
	Elf32_Word sh_addralign;
	Elf32_Word sh_entsize;
} sectionHeader32_t;

typedef struct sectionHeader64_t {
	Elf64_Word sh_name;
        Elf64_Word sh_type;
        Elf64_Xword sh_flags;
        Elf64_Addr sh_addr;
        Elf64_Off sh_offset;
        Elf64_Xword sh_size;
        Elf64_Word sh_link;
        Elf64_Word sh_info;
        Elf64_Xword sh_addralign;
        Elf64_Xword sh_entsize;
} sectionHaeder64_t;

typedef struct section32_t : sectionHeader32_t {
	std::string name;
	std::vector<char> bytes;
} section32_t;

typedef struct section64_t : sectionHeader64_t {
	std::string name;
	std::vector<char> bytes;
} section64_t;

class elf_parser {

	// Factory
	public:
		static elf_parser read_file(std::string file);
		unsigned int join_bytes(std::vector<char>::iterator ptr, int numOfBytes, bool bigEndian);
};


class elf_32_parser : public elf_parser {

	private:
                elf32Header_t elfHeader;
		std::vector<programHeader32_t> programHeaders;
                std::vector<section32_t> sectionHeaderTable;

	public:
		elf_32_parser(std::vector<char> bytes);
		std::vector<char> read_section(std::string name);
};


class elf_64_parser : public elf_parser {

	private:
                elf64Header_t elfHeader;
		std::vector<programHeader64_t> programHeaders;
                std::vector<sectionHeader64_t> sectionHeaderTable;

	public:
		elf_64_parser(std::vector<char> bytes);
};


class elf_error : public elf_parser {
	// Factory error
};


} // end of namespace elf

#endif
