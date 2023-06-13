#include "../../inc/main/main.hpp"


int main(int argc, char *argv[]) {

        cmd_args_help args(argc, argv);

        if (args.number() == 0) {
                args.print_help();
                return EXIT_FAILURE;
        }

        if (args.find("--help") != -1 || args.find("-h") != -1) {
                args.print_help();
                return EXIT_SUCCESS;
        }

        int index;
        if (index=args.find("--file") != -1) {
		std::string file = args.read_arg(index);
        } else if (index=args.find("-f") != -1) {
		std::string file = args.read_arg(index);
	} else {
		args.print_help();
		return EXIT_FAILURE;
	}

	program_memory prog;
	//if (args.find("--binary") != -1) {
	//	prog.from_file(file, "binary");
	//} else if (index=args.find("--assembly")
	//	prog.from_file(file, "assembly");
	//} else {
	//	// Infer --binary default
	//	prog.from_file(file, "binary");
	//}

	//mips_engine simEngine;
	//simEngine.load(prog);
	//simEngine.logging(true);
	//simEngine.run();
	//simEngine.write_log("sim_log.csv");
	
	elf_parser elf;
	elf.read_file("a.out");	

        return EXIT_SUCCESS;
}
