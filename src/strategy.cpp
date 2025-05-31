#include "strategy.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>


SMA_Strategy::SMA_Strategy(TimeSeries data, SMA sma):data(data),sma(sma){};

void SMA_Strategy::saveToCsv(std::string filename) {
        std::ifstream inputFile("data_test.csv"); // Open original CSV file
        std::ofstream outputFile("data_test2.csv"); // Output modified file
        std::string line;
        int i=0;
        while (getline(inputFile, line)) { // Read each row
            line += "," + std::to_string(this->sma.indicators[i]); // Append new column value
            outputFile << line << std::endl; // Write to new file
            i++;
        }
        inputFile.close();
        outputFile.close();
        std::cout << "Column added successfully!" << std::endl;
}
