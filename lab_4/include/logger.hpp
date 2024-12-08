#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <mutex>
#include <fstream>

class Logger {
public:
    Logger(const std::string& filename);
    void log(const std::string& message);
    static std::string getCurrentTime();

private:
    std::string filename;
    std::ofstream logFile;
    std::mutex logMutex;
};

#endif // LOGGER_HPP
