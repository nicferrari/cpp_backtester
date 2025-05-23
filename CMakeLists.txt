cmake_minimum_required(VERSION 3.15)
project(backtester)

include_directories(include)

add_executable(MyExecutable src/main.cpp src/data.cpp)
