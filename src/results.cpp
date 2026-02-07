#include "results.h"
#include <iostream>
#include <fstream>
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

void Results::print(const TimeSeries& ts) const {
    std::cout<<"Start Date = "<<ts.timeseries.front().datetime<<std::endl;
    std::cout<<"End Date = "<<ts.timeseries.back().datetime<<std::endl;
    std::cout<<"Return = "<<log(networth.back()/networth.front())*100<<"%"<<std::endl;
    std::cout<<"Trades # = "<<trade.size()<<std::endl;
    double max_pl = 0;
    double min_pl = 0;
    double avg_pl = 0;
    int winrate = 0;
    double avg_duration=0;
    for (const auto& i: trade){
        const double pl = Results::trade_pl(ts,i.open_date,i.end_date,i.choice);
        if (pl >= max_pl) max_pl = pl;
        if (pl < min_pl) min_pl = pl;
        if (pl>=0) winrate++;
        avg_pl += pl;
        const double duration = Results::trade_duration(ts,i.open_date,i.end_date);
        avg_duration += duration;
    };
    std::cout<<"Max pl = "<<max_pl*100<<"%"<<std::endl;
    std::cout<<"Min pl = "<<min_pl*100<<"%"<<std::endl;
    std::cout<<"Avg pl = "<<avg_pl/trades_nr*100<<"%"<<std::endl;
    std::cout<<"Winrate = "<<static_cast<double>(winrate)/trades_nr*100<<"%"<<std::endl;
    std::cout<<"Sharpe ratio = "<<sharpe_ratio()<<std::endl;
    std::cout<<"Max drawdown = "<<max_drawdown()*100<<"%"<<std::endl;
    std::cout<<"Avg duration = "<<avg_duration/trades_nr<<std::endl;
};

Results::Results() {
    trades_nr=0;
}

void Results::tradesToCsv(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file\n";
        return;
    }
    file<<"Open Date,End Date,Choice,Status\n";
    for (const auto & t:trade) {
        file<<t.open_date<<","<<t.end_date<<","<<t.choice<<","<<t.status<<"\n";
    }
    file.close();
}

void Results::ordersToCsv(const std::string &filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file\n";
        return;
    }
    file<<"Choice,Status,Open Date, End date\n";
    for (const auto & o:orders) {
        file<<o.choice<<","<<o.status<<","<<o.open_date<<","<<o.end_date<<"\n";
    }
    file.close();
}