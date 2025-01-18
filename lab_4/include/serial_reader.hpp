#ifndef SERIAL_READER_HPP
#define SERIAL_READER_HPP

#include <boost/asio.hpp>
#include <string>
#include <thread>
#include <atomic>
#include <functional>

class SerialReader {
public:
    SerialReader(const std::string& portName);
    ~SerialReader();

    void start();
    void stop();
    void setOnDataReceived(std::function<void(double)> callback);

private:
    void readData();
    
    boost::asio::io_service ioService;
    boost::asio::serial_port serialPort;
    std::atomic<bool> running;
    std::thread ioThread;
    std::function<void(double)> onDataReceived;
};

#endif // SERIAL_READER_HPP
