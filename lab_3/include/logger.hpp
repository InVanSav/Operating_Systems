#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <mutex>

class Logger {
public:
    static void log(const std::string& message);
    static std::string getCurrentTime();
private:
    static std::mutex logMutex;
};

#endif // LOGGER_HPP
