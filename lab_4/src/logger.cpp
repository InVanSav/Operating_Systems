#include "logger.hpp"
#include <chrono>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <deque>
#include <algorithm>

Logger::Logger(const std::string& filename, size_t maxEntries)
    : filename(filename), maxEntries(maxEntries), logFile(filename, std::ios::app) {}

void Logger::log(const std::string& message) {
    std::lock_guard<std::mutex> lock(logMutex);
    if (logFile.is_open()) {
        logFile << message << std::endl;
        truncateLog();
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

void Logger::truncateLog() {
    std::ifstream inFile(filename);
    std::deque<std::string> lines;

    std::string line;
    while (std::getline(inFile, line)) {
        lines.push_back(line);
        if (lines.size() > maxEntries) {
            lines.pop_front();
        }
    }

    inFile.close();
    std::ofstream outFile(filename, std::ios::trunc);
    for (const auto& l : lines) {
        outFile << l << std::endl;
    }
}
