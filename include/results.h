//
// Created by nicfe on 08/12/2025.
//

#ifndef RESULTS_H
#define RESULTS_H
#include <vector>
#include "risk_manager.h"

class Results {
public:
    int trades_nr;
    std::vector<double> networth;
    std::vector<Order> trade;
    void trade_list() const;
    static double trade_pl(const TimeSeries &ts, const std::string& start_date, const std::string& end_date, Choice side);
    static double trade_duration(const TimeSeries &ts, const std::string &start_date, const std::string &end_date);
    double sharpe_ratio() const;
    double max_drawdown() const;
};
#endif //RESULTS_H
