#include "vstring.hpp"
#include <gtest/gtest.h>
#include "tests/vstring_strlen_test.hpp"

static constexpr int kArgs = 10;
static const char* pos_str[kArgs] = {
    "1",
    "12",
    "123",
    "1234",
    "12345",
    "123456",
    "1234567",
    "12345678",
    "123456789",
    "1234567890",
};

static int pos_results[kArgs] = {
    1,
    12,
    123,
    1234,
    12345,
    123456,
    1234567,
    12345678,
    123456789,
    1234567890
};

static const char* neg_str[kArgs] = {
    "-1",
    "-12",
    "-123",
    "-1234",
    "-12345",
    "-123456",
    "-1234567",
    "-12345678",
    "-123456789",
    "-1234567890",
};

static int neg_results[kArgs] = {
    -1,
    -12,
    -123,
    -1234,
    -12345,
    -123456,
    -1234567,
    -12345678,
    -123456789,
    -1234567890
};

TEST(VStringTest, PositiveNumbers) {
    for (int i=0; i<kArgs; i++) {
        int result = vstring::atoi(pos_str[i]);
        EXPECT_EQ(result, pos_results[i]);
    }
}


TEST(VStringTest, NegativeNumbers) {
    for (int i=0; i<kArgs; i++) {
        int result = vstring::atoi(neg_str[i]);
        EXPECT_EQ(result, neg_results[i]);
    }
}

TEST(VStringTest, ZeroNumber) {
    {
        int result = vstring::atoi("0");
        EXPECT_EQ(result, 0);
    }

    {
        int result = vstring::atoi("-0");
        EXPECT_EQ(result, 0);
    }
}

TEST(VStringTest, PositiveNumbersIntrinsics) {
    for (int i=0; i<kArgs; i++) {
        int result = vstring::stoi(pos_str[i]);
        EXPECT_EQ(result, pos_results[i]);
    }
}


TEST(VStringTest, NegativeNumbersIntrinsics) {
    for (int i=0; i<kArgs; i++) {
        int result = vstring::stoi(neg_str[i]);
        EXPECT_EQ(result, neg_results[i]);
    }
}

TEST(VStringTest, ZeroNumberInstrinsics) {
    {
        int result = vstring::stoi("0");
        EXPECT_EQ(result, 0);
    }

    {
        int result = vstring::atoi("-0");
        EXPECT_EQ(result, 0);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}   
