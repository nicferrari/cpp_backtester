#ifndef DATA_H
#define DATA_H

#include <vector>
#include <string>

class Data {
public:
    std::string datetime;
    double open, high, low, close;
    Data(const std::string& dt, float o, float h, float l, float c);
};

class TimeSeries {
public:
    std::vector<Data> timeseries;
    explicit TimeSeries(const std::string& filename);
    void printData() const;
    void saveToCsv(const std::string& filename) const;
};

#endif // DATA_H
