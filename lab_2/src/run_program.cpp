#include "../include/run_program.hpp"
#include <iostream>
#include <cstdlib>

bool RunProgram::run(const std::string& command, int& exitCode) {
#ifdef _WIN32
    STARTUPINFO si = { sizeof(STARTUPINFO) };
    PROCESS_INFORMATION pi;

    if (!CreateProcess(
            NULL,
            const_cast<char*>(command.c_str()),
            NULL, NULL, FALSE,
            CREATE_NO_WINDOW,
            NULL, NULL,
            &si, &pi)) {
        return false;
    }

    // Ожидаем завершения
    WaitForSingleObject(pi.hProcess, INFINITE);

    DWORD status;
    if (!GetExitCodeProcess(pi.hProcess, &status)) {
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        return false;
    }

    exitCode = static_cast<int>(status);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

#else
    pid_t pid = fork();
    if (pid == 0) {
        // Дочерний процесс
        execl("/bin/sh", "sh", "-c", command.c_str(), (char*)NULL);
        _exit(EXIT_FAILURE);
    } else if (pid < 0) {
        return false;
    } else {
        // Родительский процесс
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            exitCode = WEXITSTATUS(status);
        } else {
            return false;
        }
    }
#endif
    return true;
}
