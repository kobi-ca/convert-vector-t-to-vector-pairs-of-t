//
// Created by kobi on 4/8/22.
//

#include <vector>
#include <cassert>
#include <numeric>
#include "range/v3/all.hpp"
#include "benchmark/benchmark.h"

namespace with_ranges1 {
    // returning std::vector would force the transformation
    // std::vector<std::pair<int, int>>
    auto get(const auto& c) {
        auto odds = c | ranges::views::drop(0) | ranges::views::stride(2);
        auto evens = c | ranges::views::drop(1) | ranges::views::stride(2);
        return ranges::views::zip(odds, evens) | ranges::to<std::vector>();
    }
}

namespace with_ranges2 {
    // returning std::vector would force the transformation
    // std::vector<std::pair<int, int>>
    auto get(const auto& c) {
        auto chunk_to_pair = [](auto chunk)
        {
            return std::pair(*chunk.begin(), *std::next(chunk.begin()));
        };
        return c | ranges::views::chunk(2) | ranges::views::transform(chunk_to_pair) | ranges::to<std::vector>();
    }
}

namespace with_accumulate {
    struct pair_accumulator final {
        explicit pair_accumulator(const int v) {
            result.reserve(v);
        }
        std::vector<std::pair<int,int>> result;
        int temp = 0;
        bool set = false;
        pair_accumulator& operator+(int x){
            if (set) {
                result.emplace_back(temp, x);
                set = false;
            } else {
                temp = x;
                set = true;
            }
            return *this;
        }
    };
}

namespace with_adj_find {
    auto get(const auto &c) {
        std::vector<std::pair<int, int>> result;
        result.reserve(c.size()/2);
        // save flag
        bool save_it = true;
        const auto f{[&](int n1, int n2) {
            if (save_it) result.emplace_back(n1, n2);
            save_it = !save_it;
            return false;
        }};
        std::adjacent_find(c.cbegin(), c.cend(), f);
        return result;
    }
}

namespace with_plain {
    auto get(const auto &c) {
        auto output = std::vector<std::pair<int, int>>();
        output.reserve(c.size()/2);
        for(size_t i = 0; i < c.size(); i+=2)
            output.emplace_back(c[i], c[i+1]);
        return output;
    }
}

static void ranges1(benchmark::State& state) {
    // Code inside this loop is measured repeatedly
    for (auto _ : state) {
        const std::vector<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        const auto r = with_ranges1::get(values);
        benchmark::DoNotOptimize(r);
    }
}

static void ranges2(benchmark::State& state) {
    // Code inside this loop is measured repeatedly
    for (auto _ : state) {
        const std::vector<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10};    const auto r = with_ranges2::get(values);
        benchmark::DoNotOptimize(r);
    }
}

static void accum(benchmark::State& state) {
    // Code inside this loop is measured repeatedly
    for (auto _ : state) {
        const std::vector<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10};    auto r = std::accumulate(values.begin(),values.end(), with_accumulate::pair_accumulator(values.size()/2)).result;
        benchmark::DoNotOptimize(r);
    }
}

static void adj(benchmark::State& state) {
    // Code inside this loop is measured repeatedly
    for (auto _ : state) {
        const std::vector<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10};    auto r = with_adj_find::get(values);
        benchmark::DoNotOptimize(r);
    }
}

static void plain(benchmark::State& state) {
    // Code inside this loop is measured repeatedly
    for (auto _ : state) {
        const std::vector<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10};    auto r = with_plain::get(values);
        benchmark::DoNotOptimize(r);
    }
}


BENCHMARK(ranges1);
BENCHMARK(ranges2);
BENCHMARK(accum);
BENCHMARK(adj);
BENCHMARK(plain);
