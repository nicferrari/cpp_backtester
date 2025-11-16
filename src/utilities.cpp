
#include <fstream>
#include <iostream>
#include <string>
#include "data.h"
#include "engine.h"
#include "ta.h"

void writeToCSV(TimeSeries ts, std::vector<Indicator> indicators, Strategy& strategy, Results results, const std::string& filename) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file\n";
        return;
    }

    // Write headers dynamically based on the number of indicators
    file << "Date,Open,High,Low,Close";
    for (size_t j = 0; j < indicators.size(); ++j) {
        file << ",Indicator" << j;  // Naming indicators like Indicator0, Indicator1...
    }
    file << ",Choice,Account,Position,Networth\n";

    // Write data
    for (size_t i = 0; i < ts.timeseries.size(); ++i) {
        file << ts.timeseries[i].toCsv();  // Start with time series data

        // Append CSV data for each indicator
        for ( auto& indicator : indicators) {
            file << "," << indicator.writeToCsv(i);
        }

        // Append strategy and results data
        file << "," << strategy.writeToCsv(i) << "," << results.writeToCsv(i) << "\n";
    }

    file.close();
}

