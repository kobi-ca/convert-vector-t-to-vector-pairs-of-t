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

Note the Release build type that is needed for the Release cmake build dir

    conan install -pr:b=default  --profile default-abi11 -s build_type=Release ../conanfile.txt                

### Profile

    (venv) ➜  cmake-build-release git:(main) ✗ cat ~/.conan/profiles/default-abi11
    [settings]
    os=Linux
    os_build=Linux
    arch=x86_64
    arch_build=x86_64
    compiler=gcc
    compiler.version=10
    compiler.libcxx=libstdc++11
    build_type=Release
    [options]
    [build_requires]
    [env]


## CMake additonal flag
    -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake

# Links

## Godbolt compiler explorer
https://godbolt.org/z/sGrcjzb35

##  quick-bench and
https://quick-bench.com/q/LEmEP3OVhO4svwgO5bGDOOKHoJ0 \
Accumulate with reserve https://quick-bench.com/q/DEopRPxQhtN25jaRAb3g5txSObM \
Adj with reserve https://quick-bench.com/q/d4d0clXnnS6UQocFy0m-xB4nnDI \
With bigger input https://quick-bench.com/q/a_ZLPWLE02LJrwlguxU201PoWn4 

### Cpu adjust performance vs foverner
    sudo cpupower frequency-set --governor performance
when done

    sudo cpupower frequency-set --governor powersave

using https://stackoverflow.com/questions/38395070/google-microbenchmarking-cpu-scaling-warning

# Runs

    (venv) ➜  cmake-build-release git:(main) ✗ ./bench
    2022-04-10T19:24:55-07:00
    Running ./bench
    Run on (8 X 4690.28 MHz CPU s)
    CPU Caches:
    L1 Data 32 KiB (x8)
    L1 Instruction 32 KiB (x8)
    L2 Unified 256 KiB (x8)
    L3 Unified 12288 KiB (x1)
    Load Average: 0.96, 0.85, 0.87
    -----------------------------------------------------
    Benchmark           Time             CPU   Iterations
    -----------------------------------------------------
    ranges1           147 ns          147 ns      4717225
    ranges2           134 ns          134 ns      5158905
    accum             183 ns          183 ns      3835753
    adj               156 ns          156 ns      4480722
    plain             133 ns          133 ns      5202833
    (venv) ➜  cmake-build-release git:(main) ✗ ./bench
    2022-04-10T20:19:57-07:00
    Running ./bench
    Run on (8 X 4669.65 MHz CPU s)
    CPU Caches:
    L1 Data 32 KiB (x8)
    L1 Instruction 32 KiB (x8)
    L2 Unified 256 KiB (x8)
    L3 Unified 12288 KiB (x1)
    Load Average: 0.02, 0.04, 0.07
    -----------------------------------------------------
    Benchmark           Time             CPU   Iterations
    -----------------------------------------------------
    ranges1           158 ns          158 ns      4395165
    ranges2           143 ns          143 ns      4842724
    accum             183 ns          183 ns      3799456
    adj               169 ns          169 ns      4104701
    plain             134 ns          134 ns      5190721
    (venv) ➜  cmake-build-release git:(main) ✗ ./bench
    2022-04-10T20:20:06-07:00
    Running ./bench
    Run on (8 X 4686.23 MHz CPU s)
    CPU Caches:
    L1 Data 32 KiB (x8)
    L1 Instruction 32 KiB (x8)
    L2 Unified 256 KiB (x8)
    L3 Unified 12288 KiB (x1)
    Load Average: 0.09, 0.06, 0.08
    -----------------------------------------------------
    Benchmark           Time             CPU   Iterations
    -----------------------------------------------------
    ranges1           146 ns          146 ns      4757735
    ranges2           135 ns          135 ns      5172786
    accum             187 ns          187 ns      3697074
    adj               156 ns          156 ns      4463735
    plain             133 ns          133 ns      5200916

# Ninja
few helper tips

    ninja clean
    ninja -v # for verbosity
