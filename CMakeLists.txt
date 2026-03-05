cmake_minimum_required(VERSION 3.20)
project(embedded_cpp_fundamentals CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Wconversion
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-fsanitize=address,undefined)
    add_link_options(-fsanitize=address,undefined)
endif()

add_executable(demo src/main.cpp)
target_include_directories(demo PRIVATE include)

# Google Test — fetched automatically
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

# Test executable
enable_testing()
add_executable(tests tests/test_fixed_queue.cpp)
target_include_directories(tests PRIVATE include)
target_link_libraries(tests GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(tests)
