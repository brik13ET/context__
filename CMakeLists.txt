cmake_minimum_required(VERSION 3.16)
project(context__)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_ASAN "-g -fsanitize=address,undefined,leak -fno-sanitize-recover=all")
set(FORCE)
set(ASAN_OPTIONS "detect_stack_use_after_return=1")

add_executable(context__ main.cpp)
