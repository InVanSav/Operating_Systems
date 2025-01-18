#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <fstream>
#include <mutex>

class Logger {
public:
    Logger(const std::string& filename, size_t maxEntries);
    void log(const std::string& message);
    static std::string getCurrentTime();

private:
    void truncateLog();

    std::string filename;
    std::ofstream logFile;
    std::mutex logMutex;
    size_t maxEntries;
};

#endif // LOGGER_HPP
