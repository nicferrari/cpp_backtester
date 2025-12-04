#ifndef TA_H
#define TA_H
#include <vector>
#include "data.h"

class Indicator {
protected:
    explicit Indicator(TimeSeries ts);
public:
    TimeSeries ts;
    std::vector<double> indicators;
    void printIndicators() const;
    void saveToCsv(const std::string& filename) const;
    [[nodiscard]] std::string writeToCsv(size_t index) const;
};

class SMA:public Indicator {
public:
    SMA(const TimeSeries& ts, int period);
};

#endif //TA_H
