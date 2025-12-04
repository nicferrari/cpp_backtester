
#ifndef UTILITIES_H
#define UTILITIES_H

void writeToCSV(const TimeSeries &ts, const std::vector<Indicator>& indicators, const Strategy& strategy, const Results& results, const std::string& filename);

#endif //UTILITIES_H
