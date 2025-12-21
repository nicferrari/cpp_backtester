[![License](https://img.shields.io/badge/license-Apache%202.0-blue?style=flat-square)](ttps://github.com/nicferrari/backtester/blob/master/LICENSE-APACHE-2.0)
# backtester

Backtester is a financial backtesting library entirely written in C++.

## Quick start
- Import necessary modules:
```cpp
#include "data.h"
#include "engine_s.h"
#include "strategy_h.h"
```
- Load data via the constructor of TimeSeries:
```cpp
const TimeSeries ts("data.csv");
```
- Define an instance of class Results to store metrics and logs:
```cpp
Results results;
```
- Run the backtesting Engine by passing a user defined strategy (which returns a Choice for every index i):
```cpp
Engine::run(ts, results, [&](size_t i){return sma_strategy(ts,10,i);});
```
- Now you can print the results:
```cpp
results.print(ts);
```