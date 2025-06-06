#include <fstream>
#include "data.h"
#include "strategy.h"
#include "ta.h"

int main() {
    const TimeSeries ts("data.csv");
    const auto sma = SMA(ts, 5);
    sma.printIndicators();
    sma.saveToCsv("test.csv");
    const auto sma_strategy = SMA_Strategy(sma);
    sma_strategy.saveToCsv("test2.csv");
    return 0;
}
