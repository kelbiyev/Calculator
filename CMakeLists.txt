cmake_minimum_required(VERSION 3.29)
project(TestDoctest)

set(CMAKE_CXX_STANDARD 20)

add_executable(main main.cpp calc.cpp)

add_executable(test calc.cpp test.cpp)