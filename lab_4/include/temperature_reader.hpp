#ifndef TEMPERATURE_READER_HPP
#define TEMPERATURE_READER_HPP

#include <vector>
#include <string>
#include <chrono>
#include "logger.hpp"

class TemperatureReader {
public:
    TemperatureReader(const std::string& measurementLog, const std::string& hourlyLog, const std::string& dailyLog);
    void processTemperature(double temperature);
    void calculateHourlyAverage();
    void calculateDailyAverage();

private:
    std::vector<double> hourlyTemperatures;
    std::vector<double> dailyTemperatures;
    std::chrono::system_clock::time_point startOfDay;

    Logger measurementLogger;
    Logger hourlyLogger;
    Logger dailyLogger;
};

#endif // TEMPERATURE_READER_HPP
