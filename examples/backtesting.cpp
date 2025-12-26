#include "data.h"
#include "engine.h"
#include "strategy.h"
#include "utilities.h"
#include "results.h"
#include "data.h"

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
    ts.saveToCsv("ts.csv");
    results3.tradesToCsv("trades.csv");
    results3.ordersToCsv("orders.csv");
    return 0;
}