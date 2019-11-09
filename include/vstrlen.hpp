#ifndef _VSTRING_STRLEN_HPP_
#define _VSTRING_STRLEN_HPP_

#include <immintrin.h>
#include <cstring>
#include <limits>

namespace vstring {
//#define ALIGNED(x) __attribute__((aligned(x)))

using Mask16 = __mmask16;
using Mask64 = __mmask64;
using Register = __m512i;

static constexpr auto kMaxCharInZmm = 64;
static constexpr auto kCharVectorWidth = 64;
static constexpr Mask64 kNoMask = std::numeric_limits<Mask64>::max();
static constexpr int8_t kIndex[kMaxCharInZmm] ALIGNED = {
    0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
    32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
    48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63};

template <typename T>
int LSB(T data) {
	data = data ^ (data - 1);
	return __builtin_popcountll(data);
}

int strlen(const char* data) {
  int popcount = 0;
  int iteration = 0;
  const Register kNullTerminator = _mm512_set1_epi8('\0');
  const Register kIndexRegister = _mm512_maskz_loadu_epi8(kNoMask, kIndex);
  while (true) {
    Register chars =
        _mm512_maskz_loadu_epi8(kNoMask, data + iteration * kCharVectorWidth);
    Mask64 is_null =
        _mm512_cmp_epi8_mask(chars, kNullTerminator, _MM_CMPINT_EQ);
    if (is_null) {
      const auto index = _cvtmask64_u64(is_null);
      return iteration * kCharVectorWidth + LSB(is_null) - 1;
    }
    iteration++;
  }
}

}  // namespace vstring
#endif
