#include "include/engine.hpp"
#include "include/helpers.hpp"
#include "include/utest.h"

#include <cstdint>

UTEST(Check_engine_encryption, basic_cases) {
    Engine e;
    {
        auto got = Helpers::string_as_hex(e.encrypt(""));
        auto exp ="{ 31 D4 C2 ED 9B DA 2B 96 58 1D 96 4A AD 66 A8 86 }";
        ASSERT_STREQ(got.c_str(), exp);
    }
    {
        auto got = Helpers::string_as_hex(e.encrypt("AbCxYz"));
        auto exp ="{ 14 29 E1 10 45 AC FB E0 1C 81 B8 8D 84 10 CE 29 }";
        ASSERT_STREQ(got.c_str(), exp);
    }
    {
        auto got = Helpers::string_as_hex(e.encrypt("1234567890"));
        auto exp ="{ 9A 0E 52 64 FB 62 9F E8 5F 51 97 6A 3C 48 C6 E5 }";
        ASSERT_STREQ(got.c_str(), exp);
    }
}

UTEST(Check_engine_encryption, longer_sentences) {
    Engine e;
    {
        auto got = Helpers::string_as_hex(e.encrypt("Ala ma kota, kot ma ale."));
        auto exp ="{ D1 1E E4 8C 9E B7 13 3F 84 4F 0F 41 DE 6E FC 4F }";
        ASSERT_STREQ(got.c_str(), exp);
    }
    {
        auto got = Helpers::string_as_hex(e.encrypt("Ty, ktory wchodzisz, zegnaj sie z nadzieja."));
        auto exp ="{ AB 33 98 BF AB 48 57 99 47 7E 9E C8 91 BC DA 45 }";
        ASSERT_STREQ(got.c_str(), exp);
    }
    {
        auto got = Helpers::string_as_hex(e.encrypt("Litwo, Ojczyzno moja! ty jestes jak zdrowie;"));
        auto exp ="{ 32 80 4D A7 F9 A5 28 51 8D 7F CE 9A 3B 33 24 D3 }";
        ASSERT_STREQ(got.c_str(), exp);
    }
}

UTEST(Check_engine_encryption, longer_inputs) {
    Engine e;
    {
        const auto len = 48000;
        std::string input;
        input.reserve(len);
        for (auto i = 0; i < len; i++) {
            input.push_back('a');
        }
        auto got = Helpers::string_as_hex(e.encrypt(input));
        auto exp ="{ A6 9D 18 4E FA 10 C3 8D A7 15 D0 3F 01 60 3E 21 }";
        ASSERT_STREQ(got.c_str(), exp);
    }
    {
        const auto len = 48479;
        std::string input;
        input.reserve(len);
        for (auto i = 0; i < len; i++) {
            input.push_back('a');
        }
        auto got = Helpers::string_as_hex(e.encrypt(input));
        auto exp ="{ D7 1D 8B F1 3E ED CB A9 4E 8A 72 99 3A D0 4F F5 }";
        ASSERT_STREQ(got.c_str(), exp);
    }
    {
        const auto len = 48958;
        std::string input;
        input.reserve(len);
        for (auto i = 0; i < len; i++) {
            input.push_back('a');
        }
        auto got = Helpers::string_as_hex(e.encrypt(input));
        auto exp ="{ A6 38 D5 BB 4D 4E C1 21 F3 CE F7 5D C8 DA 93 4A }";
        ASSERT_STREQ(got.c_str(), exp);
    }
}

UTEST(Check_engine_encryption, found_keys) {
    Engine e;
    // Key for N = 2
    {
        auto got = Helpers::string_as_hex(e.encrypt("t%"));
        auto exp ="{ 58 D4 AA 81 DE 26 48 64 BB 74 14 D1 55 A9 76 14 }";
        ASSERT_STREQ(got.c_str(), exp);
    }
    // Key for N = 3
    {
        auto got = Helpers::string_as_hex(e.encrypt("<V}"));
        auto exp ="{ 3E 76 47 4E BD 2C A9 6A 8F FF FD 67 10 AE 8A 70 }";
        ASSERT_STREQ(got.c_str(), exp);
    }
    // Key for N = 4
    {
        auto got = Helpers::string_as_hex(e.encrypt("&-)D"));
        auto exp ="{ B8 E4 65 D7 67 C5 A0 86 55 21 8A 75 62 FA 77 8B }";
        ASSERT_STREQ(got.c_str(), exp);
    }
    // Key for N = 5
    {
        auto got = Helpers::string_as_hex(e.encrypt(">(i5<"));
        auto exp ="{ AC 4B 11 14 0B 79 C0 52 39 9C 7D BD 52 91 0C 60 }";
        ASSERT_STREQ(got.c_str(), exp);
    }
    // Key for N = 6
    {
        auto got = Helpers::string_as_hex(e.encrypt("17u<8("));
        auto exp ="{ 46 F6 59 B1 DE DE 98 74 A6 15 55 DF E9 A8 D6 46 }";
        ASSERT_STREQ(got.c_str(), exp);
    }
}

UTEST_MAIN();