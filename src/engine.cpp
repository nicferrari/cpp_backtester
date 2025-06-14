#include "engine.h"
#include "strategy.h"
#include <iostream>
#include <utility>
#include <cmath>

void Engine::execute(const Strategy& strategy) {
    Results results(strategy);
    Choice previousChoice = NA;
    double networth = results.account[0];
    for (int i=1; i< strategy.indicators.ts.timeseries.size()-1;i++) {
        std::cout << strategy.indicators.ts.timeseries[i].datetime << " " << strategy.choices[i] <<" " << this->results.account[i] << std::endl;
        results.account[i] = results.account[i-1];
        results.positions[i] = results.positions[i-1];
        networth = results.account[i] + results.positions[i] * strategy.indicators.ts.timeseries[i].open;
        if (strategy.choices[i]!=previousChoice) {
            std::cout << "ORDER" << (strategy.choices[i]==LONG?" BUY":" SELL") << std::endl;
            switch (strategy.choices[i]) {
                case LONG:
                    results.positions[i] = std::floor(networth/strategy.indicators.ts.timeseries[i].open);
                    results.account[i] -= (results.positions[i]-results.positions[i-1])*strategy.indicators.ts.timeseries[i].open;
                    break;
                case SHORT:
                    results.positions[i] = std::ceil(-networth/strategy.indicators.ts.timeseries[i].open);
                    results.account[i] -= (results.positions[i]+results.positions[i-1])*strategy.indicators.ts.timeseries[i].open;
                    break;
            }
        }
        std::cout << "account = " << results.account[i] << " - positions = " << results.positions[i] << std::endl;
        previousChoice = strategy.choices[i];
    }
}

Engine::Engine(Strategy strategy): results(std::move(strategy)) {}

Results::Results(const Strategy& strategy) {
    const size_t size = strategy.indicators.ts.timeseries.size();
    account.assign(size,100000);
    positions.assign(size,0);
}