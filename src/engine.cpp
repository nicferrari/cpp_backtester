#include "engine.h"
#include "strategy.h"
#include <iostream>
#include <cmath>
#include <chrono>

void Engine::execute(const Strategy& strategy) {
    Results results(strategy);
//    Choice previousChoice = NA;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i=1; i< strategy.ts.timeseries.size();i++) {
        //std::cout << strategy.ts.timeseries[i].datetime << " " << strategy.choices[i] <<" " << this->results.account[i] << std::endl;
        results.account[i] = results.account[i-1];
        results.positions[i] = results.positions[i-1];
        //initial period networth
        results.networth[i] = results.account[i] + results.positions[i] * strategy.ts.timeseries[i].open;
        if (strategy.choices[i-1]!=strategy.choices[i-2]) {
            //std::cout << "ORDER" << (strategy.choices[i-1]==LONG?" BUY":" SELL") << std::endl;
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
                default: ;
            }
        }
        //end of period networth (to be written to file)
        results.networth[i] = results.account[i] + results.positions[i] * strategy.ts.timeseries[i].close;
        //std::cout << "account = " << results.account[i] << " - positions = " << results.positions[i] << " - networth = " << results.networth[i] <<std::endl;
//        previousChoice = strategy.choices[i];
        this->results = results;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "\033[34mBacktesting calculated in " <<duration.count() << "ms\033[0m" << std::endl;
    std::cout << std::string(80, '-') << "\n";
    std::cout << "Start Date = " << strategy.ts.timeseries.front().datetime.substr(0,10)<<std::endl;
    std::cout << "End Date = " << strategy.ts.timeseries.back().datetime.substr(0,10)<<std::endl;
    std::cout << "Return = " << log(this->results.networth.back()/this->results.networth.front())*100<<"%"<<std::endl;
}

Engine::Engine(const Strategy& strategy): results(strategy) {}

Results::Results(const Strategy& strategy) {
    const size_t size = strategy.ts.timeseries.size();
    account.assign(size,100000);
    positions.assign(size,0);
    networth.assign(size, 100000);
}

std::string Results::writeToCsv(size_t index) const {
    return std::to_string(account[index]) + "," + std::to_string(positions[index]) + "," + std::to_string(networth[index]);
}
