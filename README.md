# custom-vector-cpp

Custom implementation of Vector<T> in C++17, built from scratch without STL containers.

## What's implemented

- Dynamic array with manual memory management (operator new / placement new)
- Full iterator support: random access, arithmetic, comparison
- Move semantics (move constructor + move assignment)
- Methods: push_back, pop_back, eserve, esize, t, ront, ack, swap, clear
- 25 unit tests via Google Test (including stress tests and custom types)

## CI/CD Pipeline (Woodpecker CI + Docker)

4 stages run automatically on every push and pull request:

- **build** — compile + run tests via CTest in gcc:15.2.0 Docker image
- **sanitizer** — AddressSanitizer + UndefinedBehaviorSanitizer
- **coverage** — gcovr code coverage, auto-posts report as PR comment
- **static_analysis** — cppcheck, auto-posts results as PR comment

## Build locally

```bash
cmake -B build -DBUILD_TESTING=ON
cmake --build build -j\
cd build && ctest --output-on-failure
```

## Stack

C++17, CMake, Google Test, Woodpecker CI, Docker, gcovr, cppcheck
