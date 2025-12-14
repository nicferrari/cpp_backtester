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
    void get_trade(const TimeSeries& ts, std::string start_date, std::string end_date);
};
#endif //RESULTS_H
