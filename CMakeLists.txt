cmake_minimum_required(VERSION 3.15)
project(backtester)


add_library(backtester_lib
        src/data.cpp
        src/ta.cpp
        src/strategy.cpp
        src/engine.cpp
        src/utilities.cpp
        src/ta_s.cpp
        src/strategy_s.cpp
        src/risk_manager.cpp
        src/broker.cpp
)

target_include_directories(backtester_lib PUBLIC include)

# --- Build all examples automatically ---
file(GLOB EXAMPLES "examples/*.cpp")
foreach(EXAMPLE_FILE ${EXAMPLES})
    get_filename_component(EXAMPLE_NAME ${EXAMPLE_FILE} NAME_WE)
    add_executable(${EXAMPLE_NAME} ${EXAMPLE_FILE}
            include/ta_s.h
            include/strategy_h.h
            include/risk_manager.h
            include/engine_s.h
            include/broker.h
            include/Results.h
            include/results.cpp)
    target_link_libraries(${EXAMPLE_NAME} PRIVATE backtester_lib)
endforeach()
