#ifndef TEMPERATURE_READER_HPP
#define TEMPERATURE_READER_HPP

#include "logger.hpp"
#include "serial_reader.hpp"
#include <vector>
#include <string>
#include <chrono>

class TemperatureReader {
public:
    TemperatureReader(const std::string& portName,
                      const std::string& measurementLog,
                      const std::string& hourlyLog,
                      const std::string& dailyLog);
    void start();
    void stop();
    void processTemperature(double temperature);
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
    SerialReader serialReader;
};

#endif // TEMPERATURE_READER_HPP
