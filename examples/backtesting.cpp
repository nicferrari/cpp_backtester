#include "data.h"
#include "engine_s.h"
#include "strategy_h.h"

int main() {
    const TimeSeries ts("../test_data/NVDA.csv");
    Results results;
    Engine::run(ts, results, [&](const size_t i){return sma_strategy(ts,10,i);});
    results.print(ts);
    Results results2;
    Engine::run(ts, results2, [](size_t){return buy_and_hold();});
    results2.print(ts);
    Results results3;
    Engine::run(ts, results3, [&](const size_t i){return sma_cross_strategy(ts, 10, 20, i);});
    results3.print(ts);
    return 0;
}