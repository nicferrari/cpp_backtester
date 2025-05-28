#include "ta.h"
#include <iostream>
#include <fstream>
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
    file << "Indicator\n";  // Header
    for (const auto& i : this->indicators) {
        file << i << "\n";
    }
    file.close();
    std::cout << "Data saved to " << filename << std::endl;
}


SMA::SMA(const TimeSeries& ts, const int period) {
    if (ts.timeseries.size()<period) {
        std::cerr<<"Period cannot be lower than timeseries length"<<std::endl;
    };
    std::vector<double> result;
    double sum = 0;
    for (int i=0; i<period; i++) {
        sum += ts.timeseries[i].close;
    }
    result.push_back(sum/period);
    for (int i=period; i<ts.timeseries.size(); i++) {
        sum += ts.timeseries[i].close - ts.timeseries[i-period].close;
        result.push_back(sum/period);
    }
    this->indicators =  result;
}
void SMA::print() const {
    printIndicators();
}
void SMA::save(const std::string& filename) const {
    saveToCsv(filename);
}

