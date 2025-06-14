
#ifndef ENGINE_H
#define ENGINE_H

#include "strategy.h"


class Results {
public:
    std::vector<double> account;
    std::vector<double> positions;
    std::vector<double> networth;
    explicit Results(const Strategy& strategy);
    std::string writeToCsv(int index);
};

class Engine {
public:
    void execute(const Strategy& strategy);
    Results results;
    explicit Engine(Strategy strategy);
};


#endif //ENGINE_H
