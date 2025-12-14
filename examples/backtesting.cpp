#include "data.h"
#include "engine_s.h"

int main() {
    const TimeSeries ts("../test_data/NVDA.csv");
    Results results;
    Engine::run(ts, results);
    return 0;
}