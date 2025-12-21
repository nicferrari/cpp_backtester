#ifndef ENGINE_S_H
#define ENGINE_S_H
#include <chrono>
#include <iostream>

#include "broker.h"
#include "results.h"
#include "strategy_h.h"

class Engine {
public:
    template<class Func>
    static void run(const TimeSeries &ts, Results &results, Func f)
    {
        const auto start = std::chrono::high_resolution_clock::now();
        auto order = Order(NA, NONE, "");
        Broker broker(100000);
        for (size_t i=0;i<ts.timeseries.size();i++){
            //if an order was SENT during previous period, updates position and account and returns an Order(side, OPEN)
            order = broker.executeOrder(order, ts.timeseries[i].open, ts.timeseries[i].datetime, results);
            //checks if a new Order should be SENT (if strategy suggest a different position)
            order.new_action(f(i));
            results.networth.push_back(broker.position*ts.timeseries[i].close+broker.account);
        }
        //force close last trade
        broker.forceCloseLastTrade(order, ts.timeseries.back().close, ts.timeseries.back().datetime, results);

        const auto end = std::chrono::high_resolution_clock::now();
        const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "\033[34mBacktesting calculated in " <<duration.count() << " microseconds\033[0m" << std::endl;
    };
};

#endif //ENGINE_S_H
