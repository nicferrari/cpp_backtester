
#ifndef STRATEGY_H_H
#define STRATEGY_H_H
#include "data.h"
#include "strategy.h"

Choice sma_strategy(const TimeSeries& ts, size_t period, size_t index);
#endif //STRATEGY_H_H
