#include "temperature_reader.hpp"
#include <chrono>
#include <thread>

int main() {
    TemperatureReader reader("COM1", "logs/measurements.log", "logs/hourly_avg.log", "logs/daily_avg.log");
    reader.start();

    std::chrono::system_clock::time_point lastHourly = std::chrono::system_clock::now();
    std::chrono::system_clock::time_point lastDaily = std::chrono::system_clock::now();

    while (true) {
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

    reader.stop();
    return 0;
}
