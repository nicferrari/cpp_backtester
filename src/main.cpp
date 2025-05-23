#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "data.h"

int main() {
    TimeSeries ts("data.csv");
    ts.printData();
    return 0;
}
