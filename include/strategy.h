#ifndef STRATEGY_H
#define STRATEGY_H
#include "ta.h"

class SMA_Strategy{
protected:
    TimeSeries data;
    SMA sma;
public:
    SMA_Strategy(TimeSeries data, SMA sma);
    void saveToCsv(std::string filename);
};

#endif //STRATEGY_H
