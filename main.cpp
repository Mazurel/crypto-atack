#include <cstddef>
#include <iostream>

#include "include/engine.hpp"
#include "include/helpers.hpp"


int main() {
    Engine e;
    std::string input;
    input.reserve(60000);

    size_t n = 0;
    std::cout << "180352" << std::endl;
    std::cin >> n;
    for (auto i = 0; i < n; i++) {
        std::cin >> input;
        const auto res = e.encrypt(input);

        for (const auto c: res) {
            std::cout << Helpers::to_hex(c);
        }
        std::cout << std::endl;
    }
    return 0;
}