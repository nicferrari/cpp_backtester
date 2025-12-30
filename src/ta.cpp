#include "ta.h"

#include <iostream>
#include "data.h"
#include <cmath>
#include <limits>


double sma(const TimeSeries& ts, const size_t period, const size_t index) {
    if (ts.timeseries.size() < period) {
        std::cerr << "Period cannot be lower than timeseries length" << std::endl;
    };
    double sum = 0;
    for (size_t i = index-period+1; i <= index; i++) {
        sum += ts.timeseries[i].close;
    }
    return sum / static_cast<double>(period);
}


double rsi(const TimeSeries& ts, const size_t period, const size_t index)
{
    const auto& data = ts.timeseries;
/*
    // Not enough data
    if (const size_t n = data.size(); index < period || index >= n)
        return std::numeric_limits<double>::quiet_NaN();
*/
    if (ts.timeseries.size() < period) {
        std::cerr << "Period cannot be lower than timeseries length" << std::endl;
    };


    // --- 1. Compute initial average gain/loss (simple average) ---
    double gain = 0;
    double loss = 0;

    for (size_t i = index - period + 1; i <= index; ++i) {
        if (const double diff = data[i].close - data[i - 1].close; diff > 0) gain += diff;
        else            loss -= diff;   // loss is positive
    }

    double avgGain = gain / static_cast<double>(period);
    double avgLoss = loss / static_cast<double>(period);

    // --- 2. If index == period, return first RSI ---
    if (index == period) {
        if (avgLoss == 0) return 100;
        const double rs = avgGain / avgLoss;
        return 100 - 100 / (1 + rs);
    }

    // --- 3. Wilder smoothing for all candles up to index ---
    for (size_t i = period + 1; i <= index; ++i) {
        const double diff = data[i].close - data[i - 1].close;

        const double g = diff > 0.0 ? diff : 0.0;
        const double l = diff < 0.0 ? -diff : 0.0;

        avgGain = (avgGain * static_cast<double>(period - 1) + g) / static_cast<double>(period);
        avgLoss = (avgLoss * static_cast<double>(period - 1) + l) / static_cast<double>(period);
    }

    // --- 4. Final RSI ---
    if (avgLoss == 0) return 100;

    const double rs = avgGain / avgLoss;
    return 100- 100 / (1 + rs);
}


     RSI::RSI(const TimeSeries& ts, size_t period) {
        const auto& data = ts.timeseries;
        size_t n = data.size();
        values.resize(n, std::numeric_limits<double>::quiet_NaN());

        if (n <= period) return;

        double gain = 0.0, loss = 0.0;

        // Initial averages
        for (size_t i = 1; i <= period; ++i) {
            double diff = data[i].close - data[i - 1].close;
            if (diff > 0) gain += diff;
            else          loss -= diff;
        }

        double avgGain = gain / period;
        double avgLoss = loss / period;

        // First RSI
        values[period] = avgLoss == 0 ? 100.0 :
            100.0 - 100.0 / (1.0 + avgGain / avgLoss);

        // Wilder smoothing
        for (size_t i = period + 1; i < n; ++i) {
            double diff = data[i].close - data[i - 1].close;
            double g = diff > 0 ? diff : 0.0;
            double l = diff < 0 ? -diff : 0.0;

            avgGain = (avgGain * (period - 1) + g) / period;
            avgLoss = (avgLoss * (period - 1) + l) / period;

            values[i] = avgLoss == 0 ? 100.0 :
                100.0 - 100.0 / (1.0 + avgGain / avgLoss);
        }
    }

    double RSI::operator()(size_t index) const {
        return values[index];
    }
