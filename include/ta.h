#ifndef TA_H
#define TA_H
#include "data.h"

double sma(const TimeSeries& ts, size_t period, size_t index);
double rsi(const TimeSeries& ts, size_t period, size_t index);

struct RSI {
public:
    std::vector<double> values;
    RSI(const TimeSeries& ts, size_t period);
    double operator()(size_t index) const;
};

#endif //TA_H
