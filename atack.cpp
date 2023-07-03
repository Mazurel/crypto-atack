#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <functional>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "include/engine.hpp"
#include "include/helpers.hpp"

#include <omp.h>

#define CONCAT_(A, B) A ## B
#define CONCAT(A, B) CONCAT_(A, B)

#ifndef CODE_ID
#define CODE_ID 3
#endif

constexpr char possible_characters[] =
    "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890!@#$%^&*-_=+"
    "([{<)]}>'";

void find_the_input(const std::string &output, const std::size_t len) {
    const uint64_t last_index = std::pow(sizeof(possible_characters), len);
    const uint64_t log_step = last_index / 10000;
    uint64_t iter_counter = 0;
    bool finished = false;
    
    double last_time = omp_get_wtime();

    std::cout << std::endl;

    // Thread private variables
    Engine e;
    std::string input;
    input.reserve(len);
#pragma omp parallel for private(input, e) schedule(static, 100)
    for (uint64_t index = 0; index < last_index; index++) {
#pragma omp atomic
        iter_counter++;
        if (finished) {
            continue;
        }
        if (iter_counter % (log_step == 0 ? 1 : log_step) == 0) {
            double perc = (static_cast<double>(iter_counter) /
                           static_cast<double>(last_index)) *
                          100;
#pragma omp critical
            {
                if (!finished) {
                    std::printf("\033[A\33[2K\rBreaking: %0.2f %%\n", perc);
                }
            }
        }

        uint64_t tmp = index;
        input.clear();
        for (auto i = 0; i < len; i++) {
            input.push_back(
                possible_characters[tmp % sizeof(possible_characters)]);
            tmp /= sizeof(possible_characters);
        }
        if (e.encrypt(input) == output) {
#pragma omp critical
            {
                finished = true;
                std::cout << "\n\033[A\33[2K\r"
                          << "f(" << input
                          << ") = " << Helpers::string_as_hex(output)
                          << std::endl;
            }
            continue;
        }
    }
}

int main() {
    Engine e;
    unsigned char output_len_2[] = {0x58, 0xD4, 0xAA, 0x81, 0xDE, 0x26,
                                    0x48, 0x64, 0xBB, 0x74, 0x14, 0xD1,
                                    0x55, 0xA9, 0x76, 0x14};
    unsigned char output_len_3[] = {0x3E, 0x76, 0x47, 0x4E, 0xBD, 0x2C,
                                    0xA9, 0x6A, 0x8F, 0xFF, 0xFD, 0x67,
                                    0x10, 0xAE, 0x8A, 0x70};
    unsigned char output_len_4[] = {0xB8, 0xE4, 0x65, 0xD7, 0x67, 0xC5,
                                    0xA0, 0x86, 0x55, 0x21, 0x8A, 0x75,
                                    0x62, 0xFA, 0x77, 0x8B};
    unsigned char output_len_5[] = {0xAC, 0x4B, 0x11, 0x14, 0x0B, 0x79,
                                    0xC0, 0x52, 0x39, 0x9C, 0x7D, 0xBD,
                                    0x52, 0x91, 0x0C, 0x60};
    unsigned char output_len_6[] = {
        0x46, 0xF6, 0x59, 0xB1, 0xDE, 0xDE, 0x98, 0x74,
        0xA6, 0x15, 0x55, 0xDF, 0xE9, 0xA8, 0xD6, 0x46,
    };

    std::string output;
    output.reserve(16);

    for (auto i = 0; i < 16; i++) {
        output.push_back(CONCAT(output_len_, CODE_ID)[i]);
    }
    find_the_input(output, CODE_ID);

    return 0;
}