cmake_minimum_required(VERSION 3.10)
project(Lab-11 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic")

option(BUILD_TESTING "Build tests" ON)

if(BUILD_TESTING)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
    )
    FetchContent_MakeAvailable(googletest)

    add_executable(VectorTest test.cpp Vector.hpp)
    target_link_libraries(VectorTest gtest_main)
    enable_testing()
    add_test(NAME VectorTest COMMAND VectorTest)
endif()