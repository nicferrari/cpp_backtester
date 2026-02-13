#ifndef RESULTS_H
#define RESULTS_H
#include <vector>
#include "risk_manager.h"

//static version of the same results from Result::print
//useful to print in tabular version
class Metrics{
public:
    std::string startDate;
    std::string endDate;
    double pl = 0;
    size_t trades_nr = 0;
    double max_pl = 0;
    double min_pl = 0;
    double avg_pl = 0;
    int winrate = 0;
    double avg_duration = 0;
    double sharpe_ratio = 0;
    double max_drawdown = 0;
};

class Results {
public:
    int trades_nr;
    std::vector<double> networth;
    std::vector<Order> orders;
    std::vector<Order> trade;
    static double trade_pl(const TimeSeries &ts, const std::string& start_date, const std::string& end_date, Choice side);
    static double trade_duration(const TimeSeries &ts, const std::string &start_date, const std::string &end_date);
    [[nodiscard]] double sharpe_ratio() const;
    [[nodiscard]] double max_drawdown() const;
    void trade_list() const;
    void tradesToCsv(const std::string& filename) const;
    void ordersToCsv(const std::string& filename) const;
    void print(const TimeSeries& ts) const;
    Metrics toMetrics(const TimeSeries& ts) const;
    Results();
};
#endif //RESULTS_H
