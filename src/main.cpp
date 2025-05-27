#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "data.h"
#include "ta.h"

int main() {
    TimeSeries ts("data.csv");
    ts.printData();
    std::vector<double> const sma = SMA(ts, 5);
    for (const auto i : sma) {
        std::cout << i << " "<<std::endl;
    }
    return 0;
}
