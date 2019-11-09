#include <benchmark/benchmark.h>
// #include <string>
#include <cstring>
#include <omp.h>
#include "vstring.hpp"
#include "tests/vstring_strlen_bench.hpp"

static const int kArgs = 10;
static const char* str[kArgs] = {
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

template<int idx>
void Atoi(benchmark::State& state) {
    int x= 0;
    for (auto _ : state) {
        benchmark::DoNotOptimize(x = atoi(str[idx]));
    }
}

template<int idx>
void Stoi(benchmark::State& state) {
    int x= 0;
    for (auto _ : state) {
        benchmark::DoNotOptimize(x = std::stoi(str[idx]));
    }
}

template<int idx>
void VStoi(benchmark::State& state) {
    int x =0;
    for (auto _ : state) {
        benchmark::DoNotOptimize(x = vstring::atoi(str[idx]));
    }
}

template<int idx>
void VStoiIntrinsics(benchmark::State& state) {
    int x =0;
    for (auto _ : state) {
        benchmark::DoNotOptimize(x = vstring::stoi(str[idx]));
    }
}

#define BENCH(x) BENCHMARK_TEMPLATE(x, 0); \
                 BENCHMARK_TEMPLATE(x, 1); \
                 BENCHMARK_TEMPLATE(x, 2); \
                 BENCHMARK_TEMPLATE(x, 3); \
                 BENCHMARK_TEMPLATE(x, 4); \
                 BENCHMARK_TEMPLATE(x, 5); \
                 BENCHMARK_TEMPLATE(x, 6); \
                 BENCHMARK_TEMPLATE(x, 7); \
                 BENCHMARK_TEMPLATE(x, 8); \
                 BENCHMARK_TEMPLATE(x, 9); \

BENCH(Atoi);
BENCH(Stoi);
BENCH(VStoi);
BENCH(VStoiIntrinsics);

BENCHMARK_MAIN();
