#include "simulator.hpp"
#include "temperature_reader.hpp"
#include <thread>
#include <chrono>

int main() {
    Simulator simulator("serial_port.txt");
    simulator.start();

    TemperatureReader reader("serial_port.txt", "logs/measurements.log", "logs/hourly_avg.log", "logs/daily_avg.log");

    std::chrono::system_clock::time_point lastHourly = std::chrono::system_clock::now();
    std::chrono::system_clock::time_point lastDaily = std::chrono::system_clock::now();

    while (true) {
        reader.processTemperature();

        auto now = std::chrono::system_clock::now();
        if (std::chrono::duration_cast<std::chrono::hours>(now - lastHourly).count() >= 1) {
            reader.calculateHourlyAverage();
            lastHourly = now;
        }

        if (std::chrono::duration_cast<std::chrono::hours>(now - lastDaily).count() >= 24) {
            reader.calculateDailyAverage();
            lastDaily = now;
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    simulator.stop();
    return 0;
}
