cmake_minimum_required(VERSION 3.15)
project(backtester)

add_library(backtester_lib
        src/data.cpp
        src/utilities.cpp
        src/ta.cpp
        src/strategy.cpp
        src/risk_manager.cpp
        src/broker.cpp
)

target_include_directories(backtester_lib PUBLIC include)

# --- Build all examples automatically ---
file(GLOB EXAMPLES "examples/*.cpp")
foreach(EXAMPLE_FILE ${EXAMPLES})
    get_filename_component(EXAMPLE_NAME ${EXAMPLE_FILE} NAME_WE)
    add_executable(${EXAMPLE_NAME} ${EXAMPLE_FILE}
            include/ta.h
            include/strategy.h
            include/risk_manager.h
            include/engine.h
            include/broker.h
            include/Results.h
            src/results.cpp)
    target_link_libraries(${EXAMPLE_NAME} PRIVATE backtester_lib)
endforeach()
