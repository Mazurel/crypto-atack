#pragma once

#include "helpers.hpp"
#include "polynomial.hpp"

#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <cstdio>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <string>

template <size_t Size> class PolyMatrix {
  public:
    constexpr PolyMatrix<Size>() {
        for (std::size_t i = 0; i < Size * Size; i++) {
            this->data[i] = 0;
        }
    }

    constexpr PolyMatrix<Size>(const std::initializer_list<Polynomial> &arr) {
        assert(arr.size() == (Size * Size));
        auto it = arr.begin();
        for (std::size_t i = 0; i < Size * Size; i++) {
            this->data[i] = *it;
            it++;
        }
    }

    constexpr PolyMatrix<Size>(const PolyMatrix<Size> &other) {
        for (std::size_t i = 0; i < Size * Size; i++) {
            this->data[i] = other.data[i];
        }
    }

    static PolyMatrix<Size> from_string(const std::string &input_str) {
        assert(input_str.length() >= 16);
        auto mat = PolyMatrix<Size>();
        for (auto i = 0; i < (Size * Size); i++) {
            mat.data[i] = input_str[i];
        }
        return mat;
    }

    void print() const {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                std::cout << "0x" << std::hex << std::setw(2) << std::left
                          << (int)this->at(i, j) << " ";
            }
            std::cout << std::endl;
        }
    }

    const Polynomial &at(const size_t y, const size_t x) const {
        return this->data[y * Size + x];
    }

    Polynomial &at(const size_t y, const size_t x) {
        return this->data[y * Size + x];
    }

    void matmul(const PolyMatrix<Size> &b, PolyMatrix<Size> &c) const {
        assert(this != &c && &b != &c);

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                Polynomial res = 0;
                for (int k = 0; k < 4; k++) {
                    res = res + (this->at(i, k) * b.at(k, j));
                }
                c.at(i, j) = res;
            }
        }
    }

    void matadd(const PolyMatrix<Size> &b, PolyMatrix<Size> &c) const {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                c.at(i, j) = this->at(i, j) + b.at(i, j);
            }
        }
    }

    void fill(const Polynomial n) {
        for (std::size_t i = 0; i < Size * Size; i++) {
            this->data[i] = n;
        }
    }

  private:
    Polynomial data[Size * Size];
};