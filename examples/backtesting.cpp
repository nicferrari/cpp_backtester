#include "data.h"
#include "engine_s.h"
#include "strategy_h.h"

int main() {
    const TimeSeries ts("../test_data/NVDA.csv");
    Results results;
    Engine engine;
    engine.run(ts, results, [&](size_t i){return sma_strategy(ts,10,i);});
    return 0;
}