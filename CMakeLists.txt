cmake_minimum_required(VERSION 3.22)
project(convert_vector_t_to_vector_pairs_of_t)

set(CMAKE_CXX_STANDARD 23)
find_package(range-v3 REQUIRED)
find_package(fmt REQUIRED)
find_package(benchmark REQUIRED)

add_executable(convert_vector_t_to_vector_pairs_of_t main.cpp)
target_link_libraries(convert_vector_t_to_vector_pairs_of_t PRIVATE fmt::fmt range-v3::range-v3)

add_executable(bench bench.cpp)
target_link_libraries(bench PRIVATE fmt::fmt range-v3::range-v3 benchmark::benchmark)
