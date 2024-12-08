cmake_minimum_required(VERSION 3.10)
project(RunProgram)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_C_COMPILER "gcc")

set(CMAKE_CXX_FLAGS "-Wall -Wextra -O2")

include_directories(include)

file(GLOB SRCS "src/*.cpp")

add_executable(RunProgram ${SRCS})