#ifndef ENGINE_S_H
#define ENGINE_S_H
#include <cmath>
#include <iostream>

#include "broker.h"
#include "results.h"
#include "strategy_h.h"
#include "ta_s.h"

class Engine {
public:
    template<class Func>
    static void run(const TimeSeries &ts, Results &results, Func f)
{
    auto order = Order(NA, NONE, "");
    Broker broker(100000);
    for (size_t i=0;i<ts.timeseries.size();i++){
        //if an order was SENT during previous period, updates position and account and returns an Order(side, OPEN)
        order = broker.executeOrder(order, ts.timeseries[i].open, ts.timeseries[i].datetime, results);
        std::cout<<i<<" - " << ts.timeseries[i].close<<"<>"<<sma(ts, 10, i)<<" - " << sma_strategy(ts, 10, i)<<" - ";
        //checks if a new Order should be SENT (if strategy suggest a different position)
        order.new_action(f(i));
        std::cout<<broker.currentStance<<" - ";
        std::cout<<order.choice << " - "<<order.status<<" - ";
        std::cout<<broker.position << " - "<<broker.account<<" - ";
        std::cout<<broker.position*ts.timeseries[i].close+broker.account<<std::endl;
        results.networth.push_back(broker.position*ts.timeseries[i].close+broker.account);
    }
    std::cout<<"return = "<<log(results.networth.back()/results.networth.front())<<std::endl;
    std::cout<<"trades# = "<<results.trades_nr<<std::endl;
    double max_pl = 0;
    double min_pl = 0;
    double avg_pl = 0;
    int winrate = 0;
    double avg_duration=0;
    for (const auto& i: results.trade){
        const double pl = Results::trade_pl(ts,i.open_date,i.end_date,i.choice);
        if (pl >= max_pl) max_pl = pl;
        if (pl < min_pl) min_pl = pl;
        if (pl>=0) winrate++;
        avg_pl += pl;
        const double duration = Results::trade_duration(ts,i.open_date,i.end_date);
        avg_duration += duration;
    };
    std::cout<<"max pl = "<<max_pl<<std::endl;
    std::cout<<"min pl = "<<min_pl<<std::endl;
    std::cout<<"avg pl = "<<avg_pl/results.trades_nr<<std::endl;
    std::cout<<"winrate = "<<static_cast<double>(winrate)/results.trades_nr<<std::endl;
    std::cout<<"sharpe ratio = "<<results.sharpe_ratio()<<std::endl;
    std::cout<<"max drawdown = "<<results.max_drawdown()<<std::endl;
    std::cout<<"avg duration = "<<avg_duration/results.trades_nr<<std::endl;
};
};

#endif //ENGINE_S_H
