#ifndef _VSTRING_HPP_
#define _VSTRING_HPP_

#include <omp.h>
#include <cstring>
#include <immintrin.h>
#include <emmintrin.h>

#define ALIGNED __attribute__((aligned(64)))
namespace vstring {

static constexpr long kMillion = 1000000;
static constexpr long kBillion = 1000 * kMillion;
static constexpr long kTrillion = 1000 * kBillion;
static constexpr char kZero = '0';
static constexpr int kMultipliers[10] ALIGNED = {
    1, 10, 100, 1000, 10000, 100000, kMillion, 10 * kMillion, 100 * kMillion, kBillion
};

using ymm_i = __m256i;
using xmm_i = __m128i;
#ifdef __AVX2__
#define VEC_WIDTH 8
#else
#define VEC_WIDTH 4
#endif


int stoi(const char* str) {
    int result = 0;
    int sign = str[0] == '-' ? -1 : 1;
    const char* str_ptr = sign < 0 ? str + 1 : str;
    int len = strlen(str_ptr);
    int digits[len] __attribute__((aligned(64)));

    int remainder = len % VEC_WIDTH;
    if (len / VEC_WIDTH) {
        for (int i = 0; i < len / VEC_WIDTH; i++) {
#ifdef __AVX2__
            ymm_i zero = _mm256_set1_epi32(kZero);
            xmm_i string_packed = _mm_loadu_si128((const __m128i_u*)(str_ptr + i * VEC_WIDTH);
            ymm_i chr = _mm256_cvtepi8_epi32(string_packed);
            ymm_i dig = _mm256_sub_epi32(chr, zero);
            _mm256_store_si256((ymm_i*)(digits + i * VEC_WIDTH), dig);
#elif __AVX__
            xmm_i zero = _mm_set1_epi32(kZero);
            xmm_i string_packed = _mm_loadu_si128((const __m128i_u*)(str_ptr + i * VEC_WIDTH));
            xmm_i chr = _mm_cvtepi8_epi32(string_packed);
            xmm_i dig = _mm_sub_epi32(chr, zero);
            _mm_store_si128((xmm_i *)(digits + i * VEC_WIDTH), dig);
#endif
        }
    }

#pragma omp simd aligned(digits : 64)
    for (int i=(len / VEC_WIDTH) * VEC_WIDTH; i < len;i++) {
        digits[i] = (str_ptr[i] - kZero);
    }

#pragma omp simd aligned(kMultipliers: 64) reduction(+ : result)
    for (int i=0; i<len;i++) {
        result = result + (digits[i] * kMultipliers[(len - i - 1)]);
    }
    return result * sign;
}

int atoi(const char* str) {
    int result = 0;
    int sign = str[0] == '-' ? -1 : 1;
    const char* str_ptr = sign < 0 ? str + 1 : str;
    int len = strlen(str_ptr);
    if (len <= 0) return 0;
    int digits[len] ALIGNED;

#pragma omp simd aligned(digits : 64)
    for (int i=0; i < len;i++) {
        digits[i] = (str_ptr[i] - kZero);
    }

#pragma omp simd aligned(kMultipliers: 64) reduction(+ : result)
    for (int i=0; i<len;i++) {
        result = result + (digits[i] * kMultipliers[(len - i - 1)]);
    }
    return result * sign;
}

}
#endif
