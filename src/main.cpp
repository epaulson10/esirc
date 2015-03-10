#include <iostream>
#include "main.h"
#include "protocol.h"

int main() {
    std::cout << "Hello, world\n";
    std::cout << "Hi" << "\n";
    Protocol p;
    p.genPrivMessage();
    return 0;
}
