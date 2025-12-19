#include "results.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <iomanip>

void Results::trade_list() const {
    size_t j = 0;
    for (auto & i : trade) {
        std::cout<<"Trade " << j<< ") " <<i.open_date<<" - "<<i.end_date<<" - "<<i.status<<" - "<<i.choice<<std::endl;
        j++;
    }
}

double Results::trade_pl(const TimeSeries &ts, const std::string& start_date, const std::string& end_date, const Choice side) {
    std::vector<std::string> dates;
    dates.reserve(ts.timeseries.size());
    for (auto & i:ts.timeseries){dates.push_back(i.datetime);}
    const auto index1 = std::find(dates.begin(),dates.end(),start_date);
    const auto index2 = std::find(dates.begin(),dates.end(),end_date);
    const size_t d1 = std::distance(dates.begin(),index1);
    const size_t d2 = std::distance(dates.begin(),index2);
    if (side == LONG){return log(ts.timeseries[d2].open/ts.timeseries[d1].open);}
    return -log(ts.timeseries[d2].open/ts.timeseries[d1].open);
}

double Results::trade_duration(const TimeSeries& ts,const std::string& start_date, const std::string& end_date) {
    std::tm tm1 = {};
    std::tm tm2 = {};
    std::istringstream ss1(start_date);
    std::istringstream ss2(end_date);
    ss1 >> std::get_time(&tm1, "%Y-%m-%d %H:%M:%S");
    ss2 >> std::get_time(&tm2, "%Y-%m-%d %H:%M:%S");
    // Convert to time_t (seconds since epoch)
    std::time_t t1 = std::mktime(&tm1);
    std::time_t t2 = std::mktime(&tm2);
    // Difference in seconds
    double diff_seconds = std::difftime(t2, t1);
    // Convert to days
    return diff_seconds / 86400.0;
}

double Results::sharpe_ratio() const {
    constexpr double risk_free_rate = 0;
    std::vector<double> returns;
    returns.reserve(networth.size() - 1);
    // Compute returns
    for (size_t i = 1; i < networth.size(); ++i) {
        double r = log(networth[i] / networth[i - 1]);
        returns.push_back(r);
    }
    // Mean return
    const double mean = std::accumulate(returns.begin(), returns.end(), 0.0)
                  / returns.size();
    // Standard deviation
    double variance = 0.0;
    for (const double r : returns) {
        variance += (r - mean) * (r - mean);
    }
    variance /= returns.size();
    const double stddev = std::sqrt(variance);

    if (stddev == 0.0)
        return 0.0;

    return (mean - risk_free_rate) / stddev*std::sqrt(252);
}

double Results::max_drawdown() const {
    double peak = networth[0];
    double max_dd = 0.0;
    for (const double nw : networth) {
        if (nw > peak) {
            peak = nw;  // new peak
        }
        if (const double dd = (peak - nw) / peak; dd > max_dd) {
            max_dd = dd;
        }
    }
    return max_dd;
}

