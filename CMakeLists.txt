cmake_minimum_required(VERSION 3.15)
project(backtester)

include_directories(include)

add_executable(MyExecutable src/main.cpp
        include/data.h
        src/data.cpp
        include/ta.h
        src/ta.cpp
        include/strategy.h
        src/strategy.cpp
        include/engine.h
        src/engine.cpp
        src/utilities.cpp
        include/utilities.h
)
