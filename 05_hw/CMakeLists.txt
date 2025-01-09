set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-std=c++17 -D_GLIBCXX_USE_C99 -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++)

cmake_minimum_required(VERSION 3.10)
project(stack)


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

if(CMAKE_EXPORT_COMPILE_COMMANDS)
    find_program(CLANG_EXECUTABLE "C:/msys64/mingw64/bin/clang.exe")
    add_custom_target(analyze
        COMMAND
          analyze-build --cdb ${PROJECT_BINARY_DIR}/compile_commands.json
            --use-analyzer ${CLANG_EXECUTABLE}
            --output ${PROJECT_BINARY_DIR}/analyzer
    )
endif()

target_compile_options(tests PRIVATE --coverage)
target_link_options(tests PRIVATE --coverage)
target_compile_options(stack PRIVATE --coverage)
target_link_options(stack PRIVATE --coverage)


if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(tests PRIVATE -fsanitize=address -fno-omit-frame-pointer)
    target_link_options(tests PRIVATE -fsanitize=address)
endif()

enable_testing()
# add_test(NAME tests COMMAND tests)
add_test(NAME stack_tests COMMAND tests)


set(BENCHMARK_ENABLE_TESTING OFF)
add_subdirectory(benchmark)
include_directories(benchmark/include)

add_executable(bm bm.cpp)
target_link_libraries(bm PRIVATE benchmark::benchmark stack)
