#include "temperature_reader.hpp"
#include <fstream>
#include <numeric>

TemperatureReader::TemperatureReader(const std::string& portName,
                                     const std::string& measurementLog,
                                     const std::string& hourlyLog,
                                     const std::string& dailyLog)
    : portName(portName),
      measurementLogger(measurementLog, 86400), // 24 hours
      hourlyLogger(hourlyLog, 720), // 30 days (24 * 30)
      dailyLogger(dailyLog, 365), // 1 year
      serialReader(portName) {

    serialReader.setOnDataReceived([this](double temperature) {
        processTemperature(temperature);
    });
}

void TemperatureReader::start() {
    serialReader.start();
}

void TemperatureReader::stop() {
    serialReader.stop();
}

void TemperatureReader::processTemperature(double temperature) {
    measurementLogger.log(Logger::getCurrentTime() + " Temperature: " + std::to_string(temperature));
    hourlyTemperatures.push_back(temperature);
}

void TemperatureReader::calculateHourlyAverage() {
    if (hourlyTemperatures.empty()) return;

    double avg = std::accumulate(hourlyTemperatures.begin(), hourlyTemperatures.end(), 0.0) / hourlyTemperatures.size();
    hourlyLogger.log(Logger::getCurrentTime() + " Hourly Average: " + std::to_string(avg));
    dailyTemperatures.push_back(avg);
    hourlyTemperatures.clear();
}

void TemperatureReader::calculateDailyAverage() {
    if (dailyTemperatures.empty()) return;

    double avg = std::accumulate(dailyTemperatures.begin(), dailyTemperatures.end(), 0.0) / dailyTemperatures.size();
    dailyLogger.log(Logger::getCurrentTime() + " Daily Average: " + std::to_string(avg));
    dailyTemperatures.clear();
}
