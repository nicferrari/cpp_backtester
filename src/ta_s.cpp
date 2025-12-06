#include <iostream>
#include "data.h"

double sma(const TimeSeries& ts, const size_t period, const size_t index) {
    if (ts.timeseries.size() < period) {
        std::cerr << "Period cannot be lower than timeseries length" << std::endl;
    };
    double sum = 0;
    for (size_t i = index-period+1; i <= index; i++) {
        sum += ts.timeseries[i].close;
    }
    return sum / static_cast<double>(period);
}
