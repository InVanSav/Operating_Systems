#include "../include/logger.hpp"
#include <sstream>
#include <iomanip>
#include <chrono>
#include <ctime>

Logger::Logger(const std::string& filename) : filename(filename), logFile(filename, std::ios::app) {}

void Logger::log(const std::string& message) {
    std::lock_guard<std::mutex> lock(logMutex);
    if (logFile.is_open()) {
        logFile << message << std::endl;
    }
}

std::string Logger::getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm* tm = std::localtime(&now_c);

    std::ostringstream oss;
    oss << std::put_time(tm, "%Y-%m-%d %H:%M:%S.") << millis.count();
    return oss.str();
}
