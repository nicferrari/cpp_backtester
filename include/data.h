#ifndef DATA_H
#define DATA_H

#include <vector>
#include <string>

class Data {
public:
    std::string datetime;
    float open, high, low, close;
    Data(const std::string& dt, float o, float h, float l, float c);
};

class TimeSeries {
private:
    std::vector<Data> timeseries;
public:
    explicit TimeSeries(const std::string& filename);
    void printData() const;
};

#endif // DATA_H
