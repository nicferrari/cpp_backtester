#include "data.h"
#include "engine_s.h"

#include <cmath>
#include <iomanip>
#include <iostream>
#include "broker.h"
#include "risk_manager.h"
#include "strategy.h"
#include "strategy_h.h"
#include "ta_s.h"

void Engine::run(const TimeSeries &ts) {
    auto order = Order(NA, NONE);
    Broker broker(100000);
    Results results{0};
    for (size_t i=0;i<ts.timeseries.size();i++){
        //if an order was SENT during previous period, updates position and account and returns an Order(side, OPEN)
        order = broker.executeOrder(order, ts.timeseries[i].open, results);
        std::cout<<i<<" - " << ts.timeseries[i].close<<"<>"<<sma(ts, 10, i)<<" - " << sma_strategy(ts, 10, i)<<" - ";
        //checks if a new Order should be SENT (if strategy suggest a different position)
        order.new_action(sma_strategy(ts, 10, i));
        std::cout<<broker.currentStance<<" - ";
        std::cout<<order.choice << " - "<<order.status<<" - ";
        std::cout<<broker.position << " - "<<broker.account<<" - ";
        std::cout<<broker.position*ts.timeseries[i].close+broker.account<<std::endl;
    }
    std::cout<<"return = "<<log((ts.timeseries.back().close*broker.position+broker.account)/100000)<<std::endl;
    std::cout<<"trades# = "<<results.trades_nr<<std::endl;
};
