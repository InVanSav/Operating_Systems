#include "../include/greeter.hpp"
#include "../include/farewell.hpp"

int main() {
    Greeter::sayHello("World");
    Farewell::sayGoodbye("World");
    return 0;
}
