#include "ta.h"

#include <iostream>

#include "data.h"



std::vector<double> SMA(const TimeSeries& ts, const int period) {
    if (ts.timeseries.size()<period) {
        std::cerr<<"Period cannot be lower than timeseries length"<<std::endl;
        return {};
    };
    std::vector<double> result;
    double sum = 0;
    for (int i=0; i<period; i++) {
        sum += ts.timeseries[i].close;
    }
    result.push_back(sum/period);
    for (int i=period; i<ts.timeseries.size(); i++) {
        sum += ts.timeseries[i].close - ts.timeseries[i-period].close;
        result.push_back(sum/period);
    }
    return result;
}
