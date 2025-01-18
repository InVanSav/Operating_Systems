#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include <thread>
#include <atomic>
#include <functional>
#include <string>

class Simulator {
public:
    Simulator(const std::string& portName);
    ~Simulator();

    void start();
    void stop();

private:
    void run();

    std::string portName;
    std::atomic<bool> running;
    std::thread simulationThread;
};

#endif // SIMULATOR_HPP
