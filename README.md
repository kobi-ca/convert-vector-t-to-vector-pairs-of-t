# How to convert std::vector<T> to a vector of pairs std::vector<std::pair<T,T>> using STL algorithm?

https://stackoverflow.com/questions/71707122/how-to-convert-stdvectort-to-a-vector-of-pairs-stdvectorstdpairt-t-u

# Env
    python -m venv venv                             

## Conanfile 
    [requires]
    gtest/1.11.0
    fmt/8.0.1
    range-v3/0.11.0

    [generators]
    CMakeDeps
    CMakeToolchain


# Pip installing conan
    pip install conan

## Conan install
    conan install -pr:b=default  --profile default-abi11 -s build_type=Debug ../conanfile.txt                

## CMake additonal flag
    -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake

# Links

## Godbolt compiler explorer
https://godbolt.org/z/sGrcjzb35

##  quick-bench
https://quick-bench.com/q/LEmEP3OVhO4svwgO5bGDOOKHoJ0
