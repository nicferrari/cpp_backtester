#ifndef STRATEGY_H
#define STRATEGY_H
#include "ta.h"
#include <fstream>

enum Choice {
    LONG,
    SHORT,
    NA,
};

std::ostream& operator<<(std::ostream& os, const Choice choice);

class Strategy {
public:
    Indicator indicators;
    std::vector<Choice> choices;
    explicit Strategy(Indicator ind);
    void saveToCsv(const std::string& filename) const;
    std::string writeToCsv(int index);
};

class SMA_Strategy : public Strategy {
protected:
    SMA sma;
public:
    explicit SMA_Strategy(const SMA& sma);
};

std::string toString(Choice choice);

#endif //STRATEGY_H
