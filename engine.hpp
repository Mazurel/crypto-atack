#pragma once

#include <array>
#include <cassert>
#include <cstdint>
#include <string>

#include "matrix.hpp"
#include "helpers.hpp"
#include "polynomial.hpp"

class Engine {
  public:
    void reset() { this->state.fill(0); }

    std::string encrypt(const std::string &input) {
        std::string rest_input = std::string(input);
        this->fill_str(rest_input);

        this->reset();
        while (rest_input.length() > 0) {
            auto input = PolyMatrix<4>::from_string(rest_input);
            rest_input = rest_input.substr(16);
            this->encrypt_input(input);
        }

        std::string res;
        res.reserve(16);
        for (auto i = 0; i < 16; i++) {
            res.push_back(this->state.at(i / 4, i % 4));
        }
        return res;
    }

  private:
    PolyMatrix<4> k, m, k_p, m_p, state;

    void fill_str(std::string &s) {
        constexpr std::array<Polynomial, 32> str_template = {
            0xB3, 0xC5, 0x44, 0x97, 0x42, 0x70, 0x9D, 0x88, 0x1B, 0x6A, 0xCE,
            0x10, 0x13, 0xA8, 0x5F, 0x57, 0x8F, 0x0C, 0x24, 0xF1, 0x9F, 0xE9,
            0xA5, 0xCD, 0xD1, 0xDC, 0xD2, 0x6E, 0x16, 0xA7, 0xBB, 0xE5,
        };

        std::size_t to_be_emplaced_size =
            (s.length() % 16) == 0 ? 16 : (16 - s.length() % 16);
        s.reserve(s.length() + to_be_emplaced_size);
        assert((s.length() + to_be_emplaced_size) % 16 == 0);

        for (std::size_t i = 0; i < to_be_emplaced_size; i++) {
            s.push_back(str_template[i]);
        }
    }

    void encrypt_input(const PolyMatrix<4> &input) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                this->k.at(i, j) = this->state.at(i, j);
                this->m.at(i, j) = this->state.at(i, j) + input.at(i, j);
            }
        }

        for (int i = 0; i < 6; i++) {
            this->step(input, i);
        }

        this->state.matadd(this->m, this->state);
        this->state.matadd(input, this->state);
    }

    void step(const PolyMatrix<4> &input, const int id) {
        assert(id >= 0 && id <= 6);

        // clang-format off
        constexpr std::array<std::array<Polynomial, 4>, 6> rs = {
            0x05, 0x8c, 0xB5, 0x60,
            0x31, 0x60, 0xB2, 0xA3,
            0x42, 0xDA, 0x56, 0x1B,
            0x95, 0x6D, 0x09, 0x7F,
            0x20, 0x40, 0x5B, 0xCB,
            0xAB, 0x60, 0xB8, 0xDB};
        // clang-format on
        constexpr PolyMatrix<4> T = {1, 5, 3, 2, 2, 1, 5, 3,
                                     3, 2, 1, 5, 5, 3, 2, 1};

        // Step - SB
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                this->k.at(i, j) = Helpers::S(this->k.at(i, j));
                this->m.at(i, j) = Helpers::S(this->m.at(i, j));
            }
        }

        // Step - SC
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                this->k_p.at(i, j) = this->k.at(i, (j + i) % 4);
                this->m_p.at(i, j) = this->m.at(i, (j + i) % 4);
            }
        }

        // Step - MR
        T.matmul(this->k_p, this->k);
        T.matmul(this->m_p, this->m);

        // Step - AR
        for (int i = 0; i < 4; i++) {
            this->k.at(0, i) = this->k.at(0, i) + rs[id][i];
        }
        m.matadd(this->k, this->m);
    }
};