#include "data.h"
#include "strategy.h"
#include "ta_s.h"

//todo! strategy shouldn't ask parameters of the indicator
Choice sma_strategy(const TimeSeries& ts, const size_t period, const size_t index)
{
    if (index<period-1){return NA;}
    if (ts.timeseries[index].close>sma(ts, period, index)) {
        return LONG;
    }
    return SHORT;
}

Choice buy_and_hold() {
    return LONG;
}

Choice sma_cross_strategy(const TimeSeries& ts, size_t short_period, size_t long_period, size_t index) {
    if (index<long_period){return NA;}
    if (sma(ts, short_period, index)>sma(ts, long_period, index)){return LONG;}
    return SHORT;
}