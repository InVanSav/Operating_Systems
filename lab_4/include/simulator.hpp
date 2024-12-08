#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include <atomic>
#include <thread>
#include <functional>

class Simulator {
public:
    Simulator();
    ~Simulator();

    void start(std::function<void(double)> callback);
    void stop();

private:
    std::atomic<bool> running;
    std::thread simulationThread;
};

#endif // SIMULATOR_HPP
