set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-std=c++17 -D_GLIBCXX_USE_C99)

cmake_minimum_required(VERSION 3.10)
project(stack)

# Указываем путь к заголовкам GTest
# include_directories("C:/msys64/mingw64/include")

# # Указываем путь к библиотекам GTest
# link_directories("C:/msys64/mingw64/lib")

# Линкуем GTest
# target_link_libraries(tests PRIVATE gtest gtest_main)



find_package(GTest REQUIRED)


if(WIN32)
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

add_library(stack stack.cpp)

add_executable(main main.cpp)
target_link_libraries(main stack)


add_executable(tests tests.cpp)
target_link_libraries(tests PRIVATE gtest stack)
target_link_libraries(stack PRIVATE gcov)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(tests PRIVATE --coverage)
    target_link_options(tests PRIVATE --coverage)
    target_compile_options(stack PRIVATE --coverage)
    target_link_options(stack PRIVATE --coverage)
endif()

enable_testing()
# add_test(NAME tests COMMAND tests)
add_test(NAME stack_tests COMMAND tests)


set(BENCHMARK_ENABLE_TESTING OFF)
add_subdirectory(benchmark)
include_directories(benchmark/include)

add_executable(bm bm.cpp)
target_link_libraries(bm PRIVATE benchmark::benchmark stack)
