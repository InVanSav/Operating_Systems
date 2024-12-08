#ifndef MASTER_HPP
#define MASTER_HPP

#include <atomic>

class Master {
public:
    Master(std::atomic<int>& counter);
    void run();
private:
    std::atomic<int>& counter;
    bool runningCopy1 = false;
    bool runningCopy2 = false;
};

#endif // MASTER_HPP
