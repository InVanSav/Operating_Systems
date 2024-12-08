#include "../include/simulator.hpp"
#include "../include/temperature_reader.hpp"
#include <thread>
#include <chrono>

int main() {
    TemperatureReader reader("logs/measurements.log", "logs/hourly_avg.log", "logs/daily_avg.log");
    Simulator simulator;

    simulator.start([&reader](double temperature) {
        reader.processTemperature(temperature);
    });

    std::chrono::system_clock::time_point lastHourly = std::chrono::system_clock::now();
    std::chrono::system_clock::time_point lastDaily = std::chrono::system_clock::now();

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        auto now = std::chrono::system_clock::now();
        if (std::chrono::duration_cast<std::chrono::hours>(now - lastHourly).count() >= 1) {
            reader.calculateHourlyAverage();
            lastHourly = now;
        }
        if (std::chrono::duration_cast<std::chrono::hours>(now - lastDaily).count() >= 24) {
            reader.calculateDailyAverage();
            lastDaily = now;
        }
    }

    simulator.stop();
    return 0;
}
