#include "strategy.h"
#include "ta.h"
#include <iostream>
#include <fstream>
#include <utility>
#include "data.h"

Strategy::Strategy(TimeSeries  ts):ts(std::move(ts)) {}

SMA_Strategy::SMA_Strategy(const TimeSeries& ts, const int period): Strategy(ts), sma(ts,period) {
    size_t i = ts.timeseries.size();
    choices.resize(i, Choice::NA);
    for (int j = 0; j < i; j++) {
        if (this->sma.indicators[j] == -1) choices[j] = NA;
        else if (this->sma.ts.timeseries[j].close > this->sma.indicators[j]) choices[j] = SHORT;
        else if (this->sma.ts.timeseries[j].close < this->sma.indicators[j]) choices[j] = LONG;
    }
}

SMA_Cross_Strategy::SMA_Cross_Strategy(const TimeSeries& ts, const int short_period, const int long_period): Strategy(ts), sma_short(ts, short_period),sma_long(ts, long_period){
    size_t i = ts.timeseries.size();
    choices.resize(i, NA);
    for (int j = 0; j < i; j++) {
        if (this->sma_long.indicators[j] == -1) choices[j] = NA;
        else if (this->sma_short.indicators[j] >= sma_long.indicators[j]) choices[j] = LONG;
        else choices[j] = SHORT;
    }
}


std::ostream& operator<<(std::ostream& os, const Choice choice) {
    switch (choice) {
        case LONG: os << "LONG"; break;
        case SHORT: os << "SHORT"; break;
        case NA: os << "NA"; break;
        default: os << "UNKNOWN"; break;
    }
    return os;
}
/*
void Strategy::saveToCsv(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return;
    }
    file << "Date,Close,Indicator,Choice\n";
    for (int i=0;i<this->indicators.ts.timeseries.size();i++) {
        file << this->indicators.ts.timeseries[i].datetime << "," << this->indicators.ts.timeseries[i].close << ","
        << this->indicators.indicators[i] << "," << this->choices[i] << "\n";
    }
    file.close();
    std::cout << "Data saved to " << filename << std::endl;
}
*/
std::string toString(const Choice choice) {
    switch (choice) {
        case LONG: return "LONG";
        case SHORT:return "SHORT";
        case NA:return "NA";
    }
    return "something wrong";
}

std::string Strategy::writeToCsv(int index) const {
    return toString(choices[index]);
}
