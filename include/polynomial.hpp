#pragma once

#include <cstdint>
#include <iostream>
#include <cassert>
#include <stdint.h>

constexpr uint16_t GF2_POLY = 0b100101011;

class MultiplicationLookup {
  public:
    constexpr MultiplicationLookup() : lookup_table() {
        for (int index = 0; index < 0xFFFF; index++) {
            this->lookup_table[index] = this->multiplication(index & 0xFF, (index >> 8) & 0xFF);
        }
    }

    inline constexpr uint8_t lookup(const uint8_t _x, const uint8_t _y) const {
        const uint16_t x = _x;
        const uint16_t y = _y;
        const uint16_t index = (y << 8) | x;
        assert(index <= 0xFFFF);
        return this->lookup_table[index];
    }

  private:
    constexpr uint8_t multiplication(const uint16_t x, uint16_t y) const {
        uint16_t m = 0;
        for (auto i = 0; i < 8; i++) {
            m <<= 1;
            if (m & (1 << 8)) {
                m ^= GF2_POLY;
            }
            if (y & (1 << 7)) {
                m ^= x;
            }
            y <<= 1;
        }
        return static_cast<uint8_t>(m & 0xFF);
    }

    uint8_t lookup_table[0xFFFF + 1];
};


class Polynomial {
  public:
    constexpr Polynomial() : number(0xFF){};
    constexpr Polynomial(const uint8_t number) : number(number){};
    constexpr operator uint8_t() const { return this->number; }

    constexpr Polynomial operator+(const Polynomial &other) const {
        return Polynomial(this->number ^ other.number);
    }

    constexpr Polynomial operator-(const Polynomial &other) const {
        return Polynomial(this->number ^ other.number);
    }

    const Polynomial operator*(const Polynomial &other) const {
        constexpr MultiplicationLookup multiplication_lookup;
        const uint8_t x = this->number;
        const uint8_t y = other.number;
        return multiplication_lookup.lookup(x, y);
    }

  private:
    uint8_t number;
};