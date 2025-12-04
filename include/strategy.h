#ifndef STRATEGY_H
#define STRATEGY_H
#include "ta.h"
#include <fstream>

enum Choice {
    LONG,
    SHORT,
    NA,
};

std::ostream& operator<<(std::ostream& os, Choice choice);

class Strategy {
public:
    TimeSeries ts;
    std::vector<Choice> choices;
    //void saveToCsv(const std::string& filename) const;
    [[nodiscard]] std::string writeToCsv(size_t index) const;
    explicit Strategy(TimeSeries  ts);
};

class SMA_Strategy : public Strategy {
public:
    SMA sma;
    SMA_Strategy(const TimeSeries& ts,int period);
};

class SMA_Cross_Strategy : public Strategy {
public:
    SMA sma_short;
    SMA sma_long;
    SMA_Cross_Strategy(const TimeSeries& ts, int short_period, int long_period);
};

std::string toString(Choice choice);

#endif //STRATEGY_H
