#include "../include/run_program.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <command>" << std::endl;
        return 1;
    }

    std::string command = argv[1];
    for (int i = 2; i < argc; ++i) {
        command += " ";
        command += argv[i];
    }

    int exitCode;
    if (RunProgram::run(command, exitCode)) {
        std::cout << "Program completed successfully with exit code: " << exitCode << std::endl;
    } else {
        std::cerr << "Failed to run program." << std::endl;
    }

    return 0;
}
