#include "data.h"
#include "engine_s.h"
#include <iostream>
#include "broker.h"
#include "risk_manager.h"
#include "strategy.h"
#include "strategy_h.h"
#include "ta_s.h"

void Engine::run(const TimeSeries &ts) {
    auto order = Order(NA, NONE);
    Broker broker(100000);
    for (size_t i=0;i<ts.timeseries.size();i++){
        order = broker.executeOrder(order, ts.timeseries[i].open);
        std::cout<<i<<" - " << ts.timeseries[i].close<<"<>"<<sma(ts, 10, i)<<" - " << sma_strategy(ts, 10, i)<<" - ";
        order.new_action(sma_strategy(ts, 10, i));
        std::cout<<broker.currentStance<<" - ";
        std::cout<<order.choice << " - "<<order.status<<" - ";
        std::cout<<broker.position << " - "<<broker.account<<" - ";
        std::cout<<broker.position*ts.timeseries[i].close+broker.account<<std::endl;
    }
};
