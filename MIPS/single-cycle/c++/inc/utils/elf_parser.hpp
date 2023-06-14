
#ifndef ELF_PARSE_H
#define ELF_PARSE_H


#include <fstream>
#include <iterator>
#include <vector>
#include <string>
#include <iostream>


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


class elf_parser {

	// Factory
	public:
		static elf_parser read_file(std::string file);
		int join_bytes(std::vector<char>::iterator ptr, int numOfBytes, bool bigEndian);

};


class elf_32_parser : public elf_parser {

	private:
                elfHeader_t elfHeader;
                std::vector<unsigned int> programHeaderTable;
                std::vector<unsigned int> sectionHeaderTable;

	public:
		elf_32_parser(std::vector<char> bytes);

};


class elf_64_parser : public elf_parser {

	private:
                elfHeader_t elfHeader;
                std::vector<unsigned int> programHeaderTable;
                std::vector<unsigned int> sectionHeaderTable;

	public:
		elf_64_parser(std::vector<char> bytes);

};


#endif
