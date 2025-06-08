#include "engine.h"
#include "strategy.h"
#include <iostream>

void Engine::execute(const Strategy& strategy) {
    for (auto & timeserie : strategy.indicators.ts.timeseries) {
        std::cout << timeserie.datetime << std::endl;
    }
}
