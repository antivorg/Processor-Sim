
#ifndef ELF_PARSE_H
#define ELF_PARSE_H


#include <fstream>
#include <iterator>
#include <vector>
#include <string>
#include <iostream>


#include "elf_defines.hpp"


typedef struct e_ident_t {
	int EI_OSABI;
	int EI_ABIVERSION;
} e_ident_t;

typedef struct elfHeader_t {
	e_ident_t e_ident;
	int e_type;
	int e_machine;
	int e_version;
	int e_entry;
	int e_phoff;
	int e_shoff;
	int e_flags;
	int e_ehsize;
	int e_phentsize;
	int e_phnum;
	int e_shentsize;
	int e_shnum;
	int e_shstrndx;
} elfHeader_t;

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
                elfHeader_t elfHeader;
		std::vector<programHeader_t> programHeaders;
                std::vector<unsigned int> sectionHeaderTable;

	public:
		elf_32_parser(std::vector<char> bytes);

};


class elf_64_parser : public elf_parser {

	private:
                elfHeader_t elfHeader;
		std::vector<programHeader_t> programHeaders;
                std::vector<unsigned int> sectionHeaderTable;

	public:
		elf_64_parser(std::vector<char> bytes);

};


#endif
