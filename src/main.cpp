#include <fstream>
#include "data.h"
#include "strategy.h"
#include "ta.h"
#include "engine.h"
#include "utilities.h"

int main() {
    const TimeSeries ts("data.csv");
//    const auto sma = SMA(ts, 5);
//    sma.printIndicators();
//    sma.saveToCsv("test.csv");
    //const auto sma_strategy = SMA_Strategy(ts,5);
    SMA_Strategy sma_strategy(ts,5);
//    sma_strategy.saveToCsv("test2.csv");
    Engine engine(sma_strategy);
    engine.execute(sma_strategy);

    writeToCSV(ts, {sma_strategy.sma}, sma_strategy,engine.results,"serial_test.csv");
    //const auto sma_cross_strategy = SMA_Cross_Strategy(ts,5,10);
    SMA_Cross_Strategy sma_cross_strategy(ts,5,10);
    Engine engine_cross(sma_cross_strategy);
    engine.execute(sma_cross_strategy);
    writeToCSV(ts, {sma_cross_strategy.sma_short,sma_cross_strategy.sma_long},sma_cross_strategy,engine.results,"serial_test2.csv");
    return 0;
}
