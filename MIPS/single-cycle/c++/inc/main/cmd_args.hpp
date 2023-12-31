#ifndef PARSE_ARGS_H
#define PARSE_ARGS_H

#include <vector>
#include <string>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <iomanip>


class cmd_args {

        private:
                std::vector<std::string> args;

        public:
                cmd_args(int argc, char *argv[]);

                std::string pop_arg(void);
                std::string read_arg(int number);
                void remove_arg(int number);

                int find(std::string token);
                int number(void);
};


class cmd_args_help : public cmd_args {

	 private:
                std::string descriptionMsg = "mips-emul [source] [options]...\nA single-cycle MIPS emulator.";
                std::vector<std::vector<std::string>> helpMsg = {
                        {"-h", "--help", "view options"},
                        {"heading", "Source"},
                        {"-f", "--file <filename>", "specify source file for the program to be simulated"},
			{"heading", "Options"},
			{"-a", "--assembly", "envoke a basic assembler for a newline seperated MIPS assembly file"},
			{"-b", "--binary", "file is a newline seperated ascii binary file"},
			{"-e", "--elf32", "can read the .text section of a MIPS elf32 executable (i.e. a.out)"}
                };

        public:
                using cmd_args::cmd_args;
                void print_help(void);
};


#endif
