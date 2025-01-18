#include "simulator.hpp"
#include <random>
#include <fstream>
#include <chrono>
#include <thread>

Simulator::Simulator(const std::string& portName) : portName(portName), running(false) {}

Simulator::~Simulator() {
    stop();
}

void Simulator::start() {
    running = true;
    simulationThread = std::thread(&Simulator::run, this);
}

void Simulator::stop() {
    running = false;
    if (simulationThread.joinable()) {
        simulationThread.join();
    }
}

void Simulator::run() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(-10.0, 35.0);

    std::ofstream portFile(portName, std::ios::trunc);

    while (running) {
        double simulatedTemp = dist(gen);
        portFile << simulatedTemp << std::endl;
        portFile.flush();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    portFile.close();
}
