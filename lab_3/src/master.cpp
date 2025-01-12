#include "../include/master.hpp"
#include "../include/logger.hpp"
#include "../include/worker.hpp"

#include <thread>
#include <iostream>
#include <chrono>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#endif

Master::Master(std::atomic<int>& counter) : counter(counter) {}

void Master::run()
{
    Logger::log("Master started at: " + Logger::getCurrentTime());

    int cycleCount = 0;

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        Logger::log("Master running at: " + Logger::getCurrentTime()
                    + ", Counter: " + std::to_string(counter.load()));

        if (++cycleCount % 3 == 0) {
#ifdef _WIN32
            STARTUPINFO si = {sizeof(STARTUPINFO)};
            PROCESS_INFORMATION pi1, pi2;

            if (CreateProcess(nullptr,
                              (LPSTR) "worker1.exe",
                              nullptr,
                              nullptr,
                              FALSE,
                              0,
                              nullptr,
                              nullptr,
                              &si,
                              &pi1)) {
                CloseHandle(pi1.hProcess);
                CloseHandle(pi1.hThread);
            } else {
                Logger::log("Failed to start worker1 process");
            }

            if (CreateProcess(nullptr,
                              (LPSTR) "worker2.exe",
                              nullptr,
                              nullptr,
                              FALSE,
                              0,
                              nullptr,
                              nullptr,
                              &si,
                              &pi2)) {
                CloseHandle(pi2.hProcess);
                CloseHandle(pi2.hThread);
            } else {
                Logger::log("Failed to start worker2 process");
            }
#else
            pid_t pid1 = fork();
            if (pid1 == 0) {
                Worker::runCopy1(counter);
                exit(0);
            } else if (pid1 < 0) {
                Logger::log("Failed to fork worker1");
            }

            pid_t pid2 = fork();
            if (pid2 == 0) {
                Worker::runCopy2(counter);
                exit(0);
            } else if (pid2 < 0) {
                Logger::log("Failed to fork worker2");
            }
#endif
        }
    }
}
