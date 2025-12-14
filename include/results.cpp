#include "results.h"
#include <iostream>
#include <algorithm>

void Results::trade_list() const {
    size_t j = 0;
    for (auto & i : trade) {
        std::cout<<"Trade " << j<< ") " <<i.open_date<<" - "<<i.end_date<<" - "<<i.status<<" - "<<i.choice<<std::endl;
        j++;
    }
}
void Results::get_trade(const TimeSeries &ts, std::string start_date, std::string end_date) {
    std::vector<std::string> dates;
    for (auto & i:ts.timeseries){dates.push_back(i.datetime);}
    auto index = std::find(dates.begin(),dates.end(),start_date);
    std::cout<<std::distance(dates.begin(),index);
}

