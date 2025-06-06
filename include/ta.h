#ifndef TA_H
#define TA_H
#include <vector>
#include "data.h"

class Indicator {
protected:


    explicit Indicator(TimeSeries ts);
public:
    TimeSeries ts;  //better protected?
    std::vector<double> indicators; //better protected?
    void printIndicators() const;
    void saveToCsv(const std::string& filename) const;
};

class SMA:public Indicator {
public:
    SMA(const TimeSeries& ts, int period);
};

#endif //TA_H
