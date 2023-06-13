
#ifndef ELF_PARSE_H
#define ELF_PARSE_H


#include <fstream>
#include <iterator>
#include <vector>
#include <string>
#include <iostream>


class elf_parser {

	private:
		std::vector<unsigned int> elfHeader;
		std::vector<unsigned int> programHeaderTable;
		std::vector<unsigned int> sectionHeaderTable;
	
	public:
		void read_file(std::string file);

};


class elf_32_parser : elf_parser {

};


class elf_64_parser : elf_parser {

};


#endif
