#ifndef WORKER_HPP
#define WORKER_HPP

#include <atomic>

class Worker {
public:
    static void runCopy1(std::atomic<int>& counter);
    static void runCopy2(std::atomic<int>& counter);
};

#endif // WORKER_HPP
