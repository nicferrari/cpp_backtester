#ifndef UTILITIES_H
#define UTILITIES_H
#include <string>
#include <fstream>

//void writeToCSV(const TimeSeries &ts, const std::vector<Indicator>& indicators, const Strategy& strategy, const Results& results, const std::string& filename);
//void writeToCsv(const TimeSeries& ts, const std::string& filename);

template <typename Func>
void writeToCsv(const TimeSeries &ts, Func f, std::string filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return;
    }
    file << "Date,Open,High,Low,Close,Choice\n";  // Header
    for (size_t i=0;i<ts.timeseries.size();i++) {
        file << ts.timeseries[i].datetime << "," << ts.timeseries[i].open << "," << ts.timeseries[i].high << "," << ts.timeseries[i].low << "," << ts.timeseries[i].close ;
        file << ","<<f(i) << std::endl;
    }
    file.close();
    std::cout << "\033[34mTimeseries+Indicator saved to " << filename << std::endl;
}

#endif //UTILITIES_H
