#include "../include/simulator.hpp"
#include <random>
#include <chrono>
#include <thread>

Simulator::Simulator() : running(false) {}

Simulator::~Simulator() {
    stop();
}

void Simulator::start(std::function<void(double)> callback) {
    running = true;
    simulationThread = std::thread([this, callback]() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dist(-10.0, 35.0);

        while (running) {
            double simulatedTemp = dist(gen);
            callback(simulatedTemp);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });
}

void Simulator::stop() {
    running = false;
    if (simulationThread.joinable()) {
        simulationThread.join();
    }
}
