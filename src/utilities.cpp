#include <functional>
#include <iostream>
#include <iomanip>
#include "results.h"

/*
void compareResults(std::vector<Metrics> metrics){
    int wStartDate = 0;
    int wEndDate   = 0;
    int wTradesNr  = 0;

    for (auto& it : metrics) {
        wStartDate = std::max(wStartDate, static_cast<int>(it.startDate.size()));
        wEndDate   = std::max(wEndDate,   static_cast<int>(it.endDate.size()));
        wTradesNr  = std::max(wTradesNr,  static_cast<int>(std::to_string(it.trades_nr).size()));
    }

    // compute label width
    int wLabel = 0;
    wLabel = std::max(wLabel, static_cast<int>(std::string("Start Date = ").size()));
    wLabel = std::max(wLabel, static_cast<int>(std::string("End Date = ").size()));
    wLabel = std::max(wLabel, static_cast<int>(std::string("Trades # = ").size()));

    // Start Date row
    std::cout << std::left << std::setw(wLabel) << "Start Date = ";
    for (auto& it : metrics)
        std::cout << " | " << std::left << std::setw(wStartDate) << it.startDate << " | ";
    std::cout << "\n";

    // End Date row
    std::cout << std::left << std::setw(wLabel) << "End Date = ";
    for (auto& it : metrics)
        std::cout << " | " << std::left << std::setw(wEndDate) << it.endDate << " | ";
    std::cout << "\n";

    // Trades # row
    std::cout << std::left << std::setw(wLabel) << "Trades # = ";
    for (const auto& it : metrics)
        std::cout << " | " << std::right << std::setw(wStartDate) << it.trades_nr << " | ";
    std::cout << "\n";
}
*/
/*
void compareResults(const std::vector<Metrics>& metrics) {
    struct Row {
        std::string label;
        std::function<std::string(const Metrics&)> get;
        int width = 0;
    };

    std::vector<Row> rows = {
        { "Start Date = ", [](const Metrics& m){ return m.startDate; } },
        { "End Date = ",   [](const Metrics& m){ return m.endDate; } },
        { "Trades # = ",   [](const Metrics& m){ return std::to_string(m.trades_nr); } }
    };

    int wLabel = 0;
    for (auto& r : rows)
        wLabel = std::max(wLabel, static_cast<int>(r.label.size()));

    for (auto& r : rows) {
        for (auto& m : metrics) {
            int len = r.get(m).size();
            r.width = std::max(r.width, len);
        }
    }

    for (auto& r : rows) {
        std::cout << std::left << std::setw(wLabel) << r.label;
        for (auto& m : metrics) {
            std::cout << " | "
                      << std::left << std::setw(r.width)
                      << r.get(m)
                      << " | ";
        }
        std::cout << "\n";
    }
}
*/
void compareResults(const std::vector<Metrics>& metrics)
{
    struct Row {
        std::string label;
        std::function<std::string(const Metrics&)> get;
    };

    auto dateOnly = [](const std::string& dt) {
        const auto pos = dt.find(' ');
        return pos == std::string::npos
            ? dt
            : dt.substr(0, pos);
    };

    // --- Define rows ---
    const std::vector<Row> rows = {
        { "Start Date = ", [&](const Metrics& m){return dateOnly(m.startDate);} },
        { "End Date = ",   [&](const Metrics& m){ return dateOnly(m.endDate); } },
        { "Trades # = ",   [](const Metrics& m){ return std::to_string(m.trades_nr); } },
        { "Max P&L = ",   [](const Metrics& m) {std::ostringstream ss;
            ss<<std::fixed<<std::setprecision(2)<< m.max_pl<<"%"; return ss.str();
        } },
        { "Min P&L = ",   [](const Metrics& m) {std::ostringstream ss;
            ss<<std::fixed<<std::setprecision(2)<< m.min_pl<<"%"; return ss.str();
        }},
        { "Avg P&L = ",   [](const Metrics& m) {std::ostringstream ss;
            ss<<std::fixed<<std::setprecision(2)<< m.avg_pl<<"%"; return ss.str();
        }},
        { "Winrate = ",   [](const Metrics& m) {std::ostringstream ss;
            ss<<std::fixed<<std::setprecision(2)<< m.winrate<<"%"; return ss.str();
        }},
{ "Sharpe ratio = ",   [](const Metrics& m) {std::ostringstream ss;
    ss<<std::fixed<<std::setprecision(5)<< m.sharpe_ratio; return ss.str();
}},
{ "Max drawdown = ",   [](const Metrics& m) {std::ostringstream ss;
    ss<<std::fixed<<std::setprecision(2)<< m.max_drawdown<<"%"; return ss.str();
}},
{ "Avg duration = ",   [](const Metrics& m) {std::ostringstream ss;
    ss<<std::fixed<<std::setprecision(5)<< m.avg_duration; return ss.str();
}}


    };

    if (metrics.empty())
        return;

    // --- Cache values + compute column widths ---
    size_t cols = metrics.size();
    size_t rowsCount = rows.size();

    std::vector<std::vector<std::string>> table(rowsCount,
        std::vector<std::string>(cols));

    std::vector<int> colWidth(cols, 0);
    int labelWidth = 0;

    for (size_t r = 0; r < rowsCount; ++r) {
        labelWidth = std::max(labelWidth,
                              (int)rows[r].label.size());

        for (size_t c = 0; c < cols; ++c) {
            table[r][c] = rows[r].get(metrics[c]);
            colWidth[c] = std::max(colWidth[c],
                                   (int)table[r][c].size());
        }
    }

    // --- Print table ---
    for (size_t r = 0; r < rowsCount; ++r) {

        std::cout << std::left
                  << std::setw(labelWidth)
                  << rows[r].label;

        for (size_t c = 0; c < cols; ++c) {
            std::cout << " | "
                      << std::right
                      << std::setw(colWidth[c])
                      << table[r][c];
        }

        std::cout << '\n';
    }
}


