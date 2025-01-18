#ifndef TEMPERATURE_READER_HPP
#define TEMPERATURE_READER_HPP

#include "logger.hpp"
#include <vector>
#include <string>
#include <chrono>

class TemperatureReader {
public:
    TemperatureReader(const std::string& portName,
                      const std::string& measurementLog,
                      const std::string& hourlyLog,
                      const std::string& dailyLog);
    void processTemperature();
    void calculateHourlyAverage();
    void calculateDailyAverage();

private:
    std::string portName;
    std::vector<double> hourlyTemperatures;
    std::vector<double> dailyTemperatures;
    std::chrono::system_clock::time_point startOfDay;

    Logger measurementLogger;
    Logger hourlyLogger;
    Logger dailyLogger;
};

#endif // TEMPERATURE_READER_HPP
