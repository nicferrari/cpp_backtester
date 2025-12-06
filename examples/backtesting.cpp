#include "data.h"
#include "engine_s.h"

int main() {
    const TimeSeries ts("../test_data/NVDA.csv");
    Engine::run(ts);
    return 0;
}