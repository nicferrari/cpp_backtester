#ifndef ENGINE_S_H
#define ENGINE_S_H
#include "results.h"

class Engine {
public:
    static void run(const TimeSeries &ts, Results& results);
};

#endif //ENGINE_S_H
