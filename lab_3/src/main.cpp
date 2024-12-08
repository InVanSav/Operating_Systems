#include "../include/logger.hpp"
#include "../include/master.hpp"
#include <atomic>
#include <thread>

std::atomic<int> counter(0);

void counterIncrementer(std::atomic<int>& counter) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        ++counter;
    }
}

int main() {
    Logger::log("Program started at: " + Logger::getCurrentTime());

    std::thread counterThread(counterIncrementer, std::ref(counter));
    Master master(counter);

    master.run();

    counterThread.join();
    return 0;
}
