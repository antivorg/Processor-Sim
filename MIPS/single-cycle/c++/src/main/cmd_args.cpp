#include "../../inc/main/cmd_args.hpp"


cmd_args::cmd_args(int argc, char *argv[]) {
        for (int i=1; i<argc; i++) {
                args.push_back(argv[i]);
        }
}


std::string cmd_args::pop_arg(void) {
        std::string top = args.back();
        args.pop_back();
        return top;
}


std::string cmd_args::read_arg(int number) {
        return args[number];
}


void cmd_args::remove_arg(int number) {
        args.erase(args.begin()+number);
}


int cmd_args::find(std::string token) {
        auto index = std::find(args.begin(), args.end(), token);
        if (index != args.end()) {
                return std::distance(args.begin(), index);
        } else {
                return -1;
        }
}


int cmd_args::number(void) {
        if (args.empty()) {
                return 0;
        } else {
                return args.size();
        }
}


void cmd_args_help::print_help(void) {
        std::cout<<descriptionMsg<<std::endl<<std::endl;
        for (std::vector<std::string> line : helpMsg) {
                if (line[0] == "heading") {
                        std::cout<<std::endl<<line[1]<<":"<<std::endl;
                } else if (line[0] == "paragraph") {
                        std::cout<<std::endl<<line[1]<<std::endl;
                } else {
                        std::cout<<std::right<<std::setw(4)<<line[0];
                        if (line[0]=="" || line[1]=="") {
                                std::cout<<"  ";
                        } else {
                                std::cout<<", ";
                        }
                        std::cout<<std::left<<std::setw(28)<<line[1];
                        std::cout<<std::setw(line[2].size())<<line[2]<<std::endl;
                }
        }
        std::cout<<std::endl;
}

