#include "data.h"
#include "strategy.h"
#include "ta.h"



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


std::ostream& operator<<(std::ostream& os, const Choice choice) {
    switch (choice) {
        case LONG: os << "LONG"; break;
        case SHORT: os << "SHORT"; break;
        case NA: os << "NA"; break;
        default: os << "UNKNOWN"; break;
    }
    return os;
}
