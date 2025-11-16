[![License](https://img.shields.io/badge/license-Apache%202.0-blue?style=flat-square)](ttps://github.com/nicferrari/backtester/blob/master/LICENSE-APACHE-2.0)
# backtester

Backtester is a financial backtesting library entirely written in C++.

## Quick start
- Import necessary modules:
```cpp
#include "data.h"
#include "strategy.h"
#include "engine.h"
#include "utilities.h"
```
- Load data via the constructor of TimeSeries:
```cpp
const TimeSeries ts("data.csv");
```
- Define a strategy:
```cpp
SMA_Strategy sma_strategy(ts,5);
```
- Create and run backtesting Engine:
```cpp
Engine engine(sma_strategy);
engine.execute(sma_strategy);
```
- Now you can save to csv:
```cpp
writeToCSV(ts, {sma_strategy.sma}, sma_strategy,engine.results,"bt.csv");
```