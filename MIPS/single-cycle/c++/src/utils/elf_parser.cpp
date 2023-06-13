#include "../../inc/utils/elf_parser.hpp"


void elf_parser::read_file(std::string file) {
	
	std::ifstream fileIt(file, std::ios::binary);

	std::vector<char> bytes((std::istreambuf_iterator<char>(fileIt)),
				(std::istreambuf_iterator<char>()));

	int i=0;
	for (char byte : bytes) {
		std::cout<<byte<<"\t"<<std::hex<<(unsigned int) byte<<"\t"<<i<<std::endl;
		elfData.push_back((unsigned int) byte);
		i++;
	}

	fileIt.close();
}
