#ifndef DATA_H
#define DATA_H

#include <vector>
#include <string>

class Data {
public:
    std::string datetime;
    double open, high, low, close;
    Data(std::string  dt, float o, float h, float l, float c);
    [[nodiscard]] std::string toCsv() const {
        return datetime + "," + std::to_string(open) + "," + std::to_string(high) + "," + std::to_string(low) + "," + std::to_string(close);
    }
};

class TimeSeries {
public:
    std::vector<Data> timeseries;
    explicit TimeSeries(const std::string& filename);
    void printData() const;
    void saveToCsv(const std::string& filename) const;
};

void print(std::ostream& out, const std::string& formattedMessage);

#endif // DATA_H
