#include <fstream>
#include "data.h"
#include "strategy.h"
#include "ta.h"
#include "engine.h"
#include "utilities.h"

int main() {
    const TimeSeries ts("../test_data/NVDA.csv");

    SMA_Strategy sma_strategy(ts,10);
    Engine engine(sma_strategy);
    engine.execute(sma_strategy);
    writeToCSV(ts, {sma_strategy.sma}, sma_strategy,engine.results,"serial_test.csv");

    SMA_Cross_Strategy sma_cross_strategy(ts,10,20);
    Engine engine_cross(sma_cross_strategy);
    engine_cross.execute(sma_cross_strategy);
    writeToCSV(ts, {sma_cross_strategy.sma_short,sma_cross_strategy.sma_long},sma_cross_strategy,engine_cross.results,"serial_test2.csv");
    return 0;
}
