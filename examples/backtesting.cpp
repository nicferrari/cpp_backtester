#include <iostream>
#include "data.h"
#include "ta_s.h"
#include "strategy_h.h"

int main() {
    const TimeSeries ts("../test_data/NVDA.csv");
    for (size_t i=0;i<ts.timeseries.size();i++){
        std::cout<<i<<" - " << ts.timeseries[i].close<<"<>"<<sma(ts, 10, i)<<" - " << sma_strategy(ts, 10, i)<<std::endl;
    }
    return 0;
}