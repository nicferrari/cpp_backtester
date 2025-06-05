#ifndef STRATEGY_H
#define STRATEGY_H
#include "ta.h"
#include <iostream>
#include <fstream>

enum Choice {
    LONG,
    SHORT,
    NA,
};



class Strategy {
protected:
    Indicator indicators;
    std::vector<Choice> choices;
public:
    Strategy(Indicator ind);
    void saveToCsv(std::string filename);
};

class SMA_Strategy : public Strategy {
protected:
    SMA sma;
public:
    SMA_Strategy(SMA sma);
};

#endif //STRATEGY_H
