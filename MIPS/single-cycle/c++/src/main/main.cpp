#include "../../inc/main/main.hpp"


int main(int argc, char *argv[]) {

        graph_cmd_args args(argc, argv);

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
                std::cout<<args.read_arg(index)<<std::endl;
        }

        return EXIT_SUCCESS;
}
