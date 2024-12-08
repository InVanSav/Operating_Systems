#include "../include/master.hpp"
#include "../include/logger.hpp"
#include "../include/worker.hpp"
#include <thread>
#include <chrono>

Master::Master(std::atomic<int>& counter) : counter(counter) {}

void Master::run() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        Logger::log("Master running at: " + Logger::getCurrentTime() + ", Counter: " + std::to_string(counter));

        static int cycleCount = 0;
        if (++cycleCount % 3 == 0) {
            if (!runningCopy1 && !runningCopy2) {
                std::thread copy1Thread([this]() {
                    Worker::runCopy1(counter);
                    runningCopy1 = false;
                });
                copy1Thread.detach();
                runningCopy1 = true;

                std::thread copy2Thread([this]() {
                    Worker::runCopy2(counter);
                    runningCopy2 = false;
                });
                copy2Thread.detach();
                runningCopy2 = true;
            } else {
                Logger::log("Copies are still running, skipping...");
            }
        }
    }
}
