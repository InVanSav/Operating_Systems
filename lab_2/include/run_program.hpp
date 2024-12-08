#ifndef RUN_PROGRAM_HPP
#define RUN_PROGRAM_HPP

#include <string>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#endif

class RunProgram {
public:
    // Запускает программу в фоновом режиме
    static bool run(const std::string& command, int& exitCode);
};

#endif
