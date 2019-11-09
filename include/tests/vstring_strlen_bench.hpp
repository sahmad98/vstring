#ifndef _VSTRING_STRLEN_BENCH_HPP_
#define _VSTRING_STRLEN_BENCH_HPP_

#include <benchmark/benchmark.h>
#include <cstring>
#include <omp.h>
#include "vstrlen.hpp"

const char * str_1 = "In 12 operations, this code computes the next highest\
		    power of 2 for a 32-bit integer. The result may be expressed\
		    by the formula 1U << (lg(v - 1) + 1). Note that in the edge\
		    case where v is 0, it returns 0, which isn't a power of 2;\
		    you might append the expression v += (v == 0) to remedy this\
		    if it matters. It would be faster by 2 operations to use the\
		    formula and the log base 2 method that uses a lookup table,\
		    but in some situations, lookup tables are not suitable, so the \
		    above code may be best. XP 2100+ I've foun above shift-left \
		    and then OR code is as fast as using a single BSR assembly \
		    language instruction, which scans in reverse to find the \
		    highest set bit.) It works by copying the highest set bit \
		    to all of the lower bits, and then adding one, which results \
		    in carries that set all of the lower bits to 0 and one bit \
		    beyond the highest set bit to 1. If the original number was \
		    a power of 2, then the decrement will reduce it to one less, \
		    so that we round up to the same original value.";

static void BM_Strlen(benchmark::State& st) {
	int len = 0;
	for (auto _ : st) {
		benchmark::DoNotOptimize(len = std::strlen(str_1));
	}
}

static void BM_VStrlen(benchmark::State& st) {
	int len = 0;
	for (auto _ : st) {
		benchmark::DoNotOptimize(len = vstring::strlen(str_1));
	}
}

BENCHMARK(BM_Strlen);
BENCHMARK(BM_VStrlen);

#endif
