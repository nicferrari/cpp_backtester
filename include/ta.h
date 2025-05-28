#ifndef TA_H
#define TA_H
#include <vector>
#include "data.h"

class Indicator {
protected:
    std::vector<double> indicators;
    void printIndicators() const;
    void saveToCsv(const std::string& filename) const;
};

class SMA:Indicator {
public:
    SMA(const TimeSeries& ts, int period);
    void print() const;
    void save(const std::string& filename) const;
};

#endif //TA_H
