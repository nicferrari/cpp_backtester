#include <fstream>
#include "data.h"
#include "strategy.h"
#include "ta.h"
#include "engine.h"
#include <iostream>

int main() {
    const TimeSeries ts("data.csv");
    const auto sma = SMA(ts, 5);
    sma.printIndicators();
    sma.saveToCsv("test.csv");
    const auto sma_strategy = SMA_Strategy(sma);
    sma_strategy.saveToCsv("test2.csv");
    Engine engine;
    engine.execute(sma_strategy);

    const std::string msg ="test";
    print(std::cout,msg);
    std::ofstream file("message.csv");
    print(file, msg);
    return 0;
}
