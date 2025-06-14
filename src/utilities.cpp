
#include <fstream>
#include <iostream>
#include <string>
#include "data.h"
#include "engine.h"
#include "ta.h"

void writeToCSV(TimeSeries ts, Indicator indicator, Strategy strategy, Results results, const std::string& filename) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file\n";
        return;
    }

    // Write headers
    file << "Date,Open,High,Low,Close,Indicator,Choice,Account,Position,Networth\n";

    // Write data
    for (size_t i = 0; i < ts.timeseries.size(); ++i) {
        file << ts.timeseries[i].toCsv() + "," + indicator.writeToCsv(i) + "," + strategy.writeToCsv(i) + "," + results.writeToCsv(i) + "\n";
    }
    file.close();
}
