#include "serial_reader.hpp"
#include <boost/asio.hpp>
#include <iostream>

SerialReader::SerialReader(const std::string& portName)
    : serialPort(ioService), running(false) {
    serialPort.open(portName);
    serialPort.set_option(boost::asio::serial_port_base::baud_rate(9600));
    serialPort.set_option(boost::asio::serial_port_base::character_size(8));
    serialPort.set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one));
    serialPort.set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none));
    serialPort.set_option(boost::asio::serial_port_base::flow_control(boost::asio::serial_port_base::flow_control::none));
}

SerialReader::~SerialReader() {
    stop();
}


void SerialReader::start() {
    running = true;
    ioThread = std::thread([this]() { ioService.run(); });
    readData();
}

void SerialReader::stop() {
    running = false;
    if (ioThread.joinable()) {
        ioThread.join();
    }
}

void SerialReader::setOnDataReceived(std::function<void(double)> callback) {
    onDataReceived = callback;
}

void SerialReader::readData() {
    boost::asio::streambuf buf;
    while (running) {
        boost::asio::read_until(serialPort, buf, '\n');
        std::istream is(&buf);
        double temp;
        is >> temp;

        if (onDataReceived) {
            onDataReceived(temp);
        }
    }
}
