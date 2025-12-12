#include "ta.h"
#include <iostream>
#include <fstream>
#include <utility>
#include "data.h"

void Indicator::printIndicators() const {
    for (const auto i:this->indicators) {
        std::cout<<i<<" "<<std::endl;
    }
}

void Indicator::saveToCsv(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return;
    }
    file << "Date,Close,Indicator\n";

    for (int i=0;i<this->ts.timeseries.size();i++) {
        file << this->ts.timeseries[i].datetime << "," << this->ts.timeseries[i].close << "," << this->indicators[i] <<"\n";
    }
    file.close();
    std::cout << "Data saved to " << filename << std::endl;
}


SMA::SMA(const TimeSeries& ts, const int period): Indicator(ts) {
    if (ts.timeseries.size() < period) {
        std::cerr << "Period cannot be lower than timeseries length" << std::endl;
    };
    std::vector<double> result;
    double sum = 0;
    for (int i = 0; i < period; i++) {
        sum += ts.timeseries[i].close;
        if (i!=period-1) result.push_back(-1);
    }
    result.push_back(sum / period);
    for (int i = period; i < ts.timeseries.size(); i++) {
        sum += ts.timeseries[i].close - ts.timeseries[i - period].close;
        result.push_back(sum / period);
    }
    this->indicators = result;
}

Indicator::Indicator(TimeSeries ts): ts(std::move(ts)) {}

std::string Indicator::writeToCsv(const size_t index) const {
    return std::to_string(indicators[index]);
}
