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
    [[nodiscard]] double sharpe_ratio() const;
    [[nodiscard]] double max_drawdown() const;
    void print(const TimeSeries& ts) const;
    Results();
};
#endif //RESULTS_H
