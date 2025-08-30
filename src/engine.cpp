#include "engine.h"
#include "strategy.h"
#include <iostream>
#include <utility>
#include <cmath>

void Engine::execute(const Strategy& strategy) {
    Results results(strategy);
//    Choice previousChoice = NA;
    for (int i=1; i< strategy.ts.timeseries.size();i++) {
        std::cout << strategy.ts.timeseries[i].datetime << " " << strategy.choices[i] <<" " << this->results.account[i] << std::endl;
        results.account[i] = results.account[i-1];
        results.positions[i] = results.positions[i-1];
        //initial period networth
        results.networth[i] = results.account[i] + results.positions[i] * strategy.ts.timeseries[i].open;
        if (strategy.choices[i-1]!=strategy.choices[i-2]) {
            std::cout << "ORDER" << (strategy.choices[i-1]==LONG?" BUY":" SELL") << std::endl;
            switch (strategy.choices[i-1]) {
                case LONG:
                    results.positions[i] = std::floor(results.networth[i]/strategy.ts.timeseries[i].open);
                    //results.account[i] -= (results.positions[i]-results.positions[i-1])*strategy.indicators.ts.timeseries[i].open;
                    results.account[i] = results.networth[i] - results.positions[i]*strategy.ts.timeseries[i].open;
                    break;
                case SHORT:
                    results.positions[i] = std::ceil(-results.networth[i]/strategy.ts.timeseries[i].open);
                    //results.account[i] += (-results.positions[i]+results.positions[i-1])*strategy.indicators.ts.timeseries[i].open;
                    results.account[i] = results.networth[i] - results.positions[i]*strategy.ts.timeseries[i].open;
                    break;
            }
        }
        //end of period networth (to be written to file)
        results.networth[i] = results.account[i] + results.positions[i] * strategy.ts.timeseries[i].close;
        std::cout << "account = " << results.account[i] << " - positions = " << results.positions[i] << " - networth = " << results.networth[i] <<std::endl;
//        previousChoice = strategy.choices[i];
        this->results = results;
    }
}

Engine::Engine(Strategy strategy): results(std::move(strategy)) {}

Results::Results(const Strategy& strategy) {
    const size_t size = strategy.ts.timeseries.size();
    account.assign(size,100000);
    positions.assign(size,0);
    networth.assign(size, 100000);
}

std::string Results::writeToCsv(int index) {
    return std::to_string(account[index]) + "," + std::to_string(positions[index]) + "," + std::to_string(networth[index]);
}
