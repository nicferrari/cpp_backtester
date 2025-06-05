#include "strategy.h"
#include "ta.h"
#include <iostream>
#include <fstream>
#include "data.h"

SMA_Strategy::SMA_Strategy(SMA sma): Strategy(sma), sma(sma) {
    int i = this->indicators.ts.timeseries.size();
    choices.resize(i,Choice::NA);
}

Strategy::Strategy(Indicator indicators):indicators(indicators) {}

std::ostream& operator<<(std::ostream& os, Choice choice) {
    switch (choice) {
        case LONG: os << "LONG"; break;
        case SHORT: os << "SHORT"; break;
        case NA: os << "NA"; break;
        default: os << "UNKNOWN"; break;
    }
    return os;
}

void Strategy::saveToCsv(std::string filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return;
    }
    file << "Date,Close,Indicator,Choice\n";  // Header
    //    for (const auto& i : this->indicators) {
    for (int i=0;i<this->indicators.ts.timeseries.size();i++) {
        file << this->indicators.ts.timeseries[i].datetime << "," << this->indicators.ts.timeseries[i].close << ","
        << this->indicators.indicators[i] << "," << this->choices[i] << "\n";
    }
    file.close();
    std::cout << "Data saved to " << filename << std::endl;
}