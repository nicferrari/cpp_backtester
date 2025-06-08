#include "data.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>

Data::Data(std::string  dt, float o, float h, float l, float c)
    : datetime(std::move(dt)), open(o), high(h), low(l), close(c) {}

TimeSeries::TimeSeries(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    // Skip header if present
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string datetime;
        float open, high, low, close;

        std::getline(ss, datetime, ',');
        ss >> open;
        ss.ignore();
        ss >> high;
        ss.ignore();
        ss >> low;
        ss.ignore();
        ss >> close;

        timeseries.emplace_back(datetime, open, high, low, close);
    }

    file.close();
}

void TimeSeries::printData() const {
    for (const auto& d : timeseries) {
        std::cout << d.datetime << " | " << d.open << " " << d.high
                  << " " << d.low << " " << d.close << std::endl;
    }
}
void TimeSeries::saveToCsv(const std::string &filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return;
    }
    file << "Date,Open,High,Low,Close\n";  // Header
    for (const auto& i : this->timeseries) {
        file << i.datetime << "," << i.open << "," << i.high << "," << i.low << "," << i.close <<"\n";
    }
    file.close();
    std::cout << "Data saved to " << filename << std::endl;
}

void print(std::ostream& out, const std::string& formattedMessage ) {
    out << formattedMessage << std::endl;
}
