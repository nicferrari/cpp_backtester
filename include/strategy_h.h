
#ifndef STRATEGY_H_H
#define STRATEGY_H_H
#include "data.h"
#include "strategy.h"

Choice sma_strategy(const TimeSeries& ts, size_t period, size_t index);
Choice buy_and_hold();
Choice sma_cross_strategy(const TimeSeries& ts, size_t short_period, size_t long_period, size_t index);
#endif //STRATEGY_H_H
