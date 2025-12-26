#ifndef STRATEGY_H
#define STRATEGY_H

#include "data.h"
#include <ostream>

enum Choice {
    LONG,
    SHORT,
    NA,
};

std::ostream& operator<<(std::ostream& os, Choice choice);

Choice sma_strategy(const TimeSeries& ts, size_t period, size_t index);
Choice buy_and_hold();
Choice sma_cross_strategy(const TimeSeries& ts, size_t short_period, size_t long_period, size_t index);
#endif //STRATEGY_H
