# Prerequisites

C++20 compiler, CMake 3.15 or newer, Git

# Compiling

```
git submodule update --init --recursive
cmake -S . -B build -DCMAKE_CXX_COMPILER=$(which g++) -DCMAKE_C_COMPILER=$(which gcc)
cmake --build build
```

# Running

Use [Themisto](https://github.com/algbio/themisto) to create a colored
de Bruijn graph and then use `themisto
dump-distinct-color-sets-to-binary` to serialize the color sets in the
binary format.

Sorting color sets:
```
build/sort_asc [color sets file] [sorted color sets file]
```

Finding parents:
```
OMP_NUM_THREADS=[number of threads] build/find_parents [sorted color sets file] [parents file]
```

Top-down depth limited construction:
```
build/top_down [sorted color sets file] [parents file] [depth limit] [HCS file]
```

Bottom-up depth limited construction:
```
build/bottom_up [sorted color sets file] [parents file] [depth limit] [HCS file]
```

Benchmarking accesses:
```
build/benchmark [HCS file] [number of accesses]
```
