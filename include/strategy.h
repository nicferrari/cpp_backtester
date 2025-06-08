#ifndef STRATEGY_H
#define STRATEGY_H
#include "ta.h"
#include <fstream>

enum Choice {
    LONG,
    SHORT,
    NA,
};


class Strategy {
protected:

    std::vector<Choice> choices;
public:
    Indicator indicators;
    explicit Strategy(Indicator ind);
    void saveToCsv(const std::string& filename) const;
};

class SMA_Strategy : public Strategy {
protected:
    SMA sma;
public:
    explicit SMA_Strategy(const SMA& sma);
};

#endif //STRATEGY_H
