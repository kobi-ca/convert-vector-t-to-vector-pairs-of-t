#include <vector>
#include <cassert>
#include <numeric>
#include "fmt/format.h"
#include "range/v3/all.hpp"

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

namespace plain {
    auto get(const auto &c) {
        auto output = std::vector<std::pair<int, int>>();
        output.reserve(c.size()/2);
        for(size_t i = 0; i < c.size(); i+=2)
            output.emplace_back(c[i], c[i+1]);
        return output;
    }
}

int main() {
    const std::vector<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    assert(values.size() % 2 == 0);
    const std::vector<std::pair<int,int>> result = { {1, 2}, {3, 4} , {5, 6}, {7, 8} ,{9, 10} };

    {
        fmt::print("with ranges 1\n");
        const auto r = with_ranges1::get(values);
        for(const auto [p1, p2] : r) {
            fmt::print("{} {}\n", p1, p2);
        }
    }

    {
        fmt::print("with ranges 2\n");
        const auto r = with_ranges2::get(values);
        for(const auto [p1, p2] : r) {
            fmt::print("{} {}\n", p1, p2);
        }
    }

    {
        fmt::print("with accumulate\n");
        auto r = std::accumulate(values.begin(),values.end(), with_accumulate::pair_accumulator{}).result;
        for(const auto [p1, p2] : r) {
            fmt::print("{} {}\n", p1, p2);
        }
    }

    {
        fmt::print("with adj_find\n");
        auto r = with_adj_find::get(values);
        for(const auto [p1, p2] : r) {
            fmt::print("{} {}\n", p1, p2);
        }
    }

    {
        fmt::print("with plain\n");
        auto r = plain::get(values);
        for(const auto [p1, p2] : r) {
            fmt::print("{} {}\n", p1, p2);
        }
    }

    return 0;
}
