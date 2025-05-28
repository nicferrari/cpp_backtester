#include <fstream>
#include "data.h"
#include "ta.h"

int main() {
    const TimeSeries ts("data.csv");
    ts.printData();
    const auto sma = SMA(ts, 5);
    sma.print();
    sma.save("test.csv");
    ts.saveToCsv("data_test.csv");
    return 0;
}
