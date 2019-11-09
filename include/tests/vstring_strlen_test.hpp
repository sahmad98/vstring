#include "vstrlen.hpp"
#include <gtest/gtest.h>
#include <cstring>

TEST(VStrlenTest, RandomTest1) {
	const char* data = "My saleefwhjifiof chasduifhso  adsouifshf asdfjiof \
			    This causes a parse error, because literal newline \
			    characters are not allowed within the quote.";
	EXPECT_EQ(std::strlen(data), vstring::strlen(data));
}

TEST(VStrlenTest, RandomTest2) {
	const char* data = "My saleefwhjifiof chasduifhso  adsouifshf asdfjiof \
			    The Intel Intrinsics Guide is an interactive reference\
			    tool for Intel intrinsic instructions, which are C\
			    style functions that provide access to many Intel \
			    instructions - including I";
	EXPECT_EQ(std::strlen(data), vstring::strlen(data));
}
