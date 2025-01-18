cmake_minimum_required(VERSION 3.10)
project(TemperatureLogger)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_C_COMPILER "gcc")

include_directories(include)

file(GLOB SRCS "src/*.cpp")

add_executable(TemperatureLogger ${SRCS})

# Создание папки для логов
install(DIRECTORY DESTINATION ${CMAKE_BINARY_DIR}/logs)
