#include "data.h"
#include "engine.h"
#include "strategy.h"
#include "utilities.h"
#include "results.h"
#include "ta.h"

int main() {
    const TimeSeries ts("../test_data/NVDA.csv");
    Results results;
    Engine::run(ts, results, [&](const size_t i){return sma_strategy(ts,10,i);});
    results.print(ts);
    Results results2;
    Engine::run(ts, results2, [](size_t){return buy_and_hold();});
    results2.print(ts);
    results2.trade_list();
    Results results3;
    Engine::run(ts, results3, [&](const size_t i){return sma_cross_strategy(ts, 10, 20, i);});
    results3.print(ts);
    Results results4;
    Engine::run(ts, results4, [&](const size_t i){return rsi_strategy(ts, 15, i);});
    results4.print(ts);
    //save data for inspection
    ts.saveToCsv("ts.csv");
    results3.tradesToCsv("trades.csv");
    results3.ordersToCsv("orders.csv");
    //writeToCsv(ts, [&](const size_t i){return rsi(ts, 15, i);},"rsi_data.csv");
    Results results5;
    RSI rsi_(ts, 15);
    Engine::run(ts, results5, [&](const size_t i){return rsi_strategy__(rsi_,i);});
    results5.print(ts);
    return 0;
}