#include "../include/worker.hpp"
#include "../include/logger.hpp"
#include <thread>
#include <chrono>

void Worker::runCopy1(std::atomic<int>& counter) {
    Logger::log("Copy 1 started at: " + Logger::getCurrentTime());
    counter.fetch_add(10, std::memory_order_relaxed);
    Logger::log("Copy 1 ended at: " + Logger::getCurrentTime());
}

void Worker::runCopy2(std::atomic<int>& counter) {
    Logger::log("Copy 2 started at: " + Logger::getCurrentTime());

    // Увеличиваем значение в 2 раза
    int current = counter.load(std::memory_order_relaxed);
    counter.store(current * 2, std::memory_order_relaxed);

    // Ждем 2 секунды
    std::this_thread::sleep_for(std::chrono::seconds(2));

    // Уменьшаем значение в 2 раза
    current = counter.load(std::memory_order_relaxed);
    counter.store(current / 2, std::memory_order_relaxed);

    Logger::log("Copy 2 ended at: " + Logger::getCurrentTime());
}
