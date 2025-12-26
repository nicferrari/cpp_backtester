#ifndef RISK_MANAGER_H
#define RISK_MANAGER_H

#include <string>
#include "strategy.h"

enum order_status {
    SENT,
    OPEN,
    CLOSED,
    NONE,
};

std::ostream& operator<<(std::ostream& os, order_status status);

class Order {
public:
    std::string update;
    Choice choice;
    order_status status;
    std::string open_date;
    std::string end_date;
    Order(Choice choice, order_status status, const std::string &date);
    void new_action(Choice choice);
};

#endif //RISK_MANAGER_H
