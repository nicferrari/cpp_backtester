#ifndef RISK_MANAGER_H
#define RISK_MANAGER_H

#include "strategy.h"

enum order_status {
    SENT,
    OPEN,
    CLOSED,
    NONE,
};

class Order {
public:
    Choice choice;
    order_status status;
    std::string open_date;
    std::string end_date;
    Order(Choice choice, order_status status, std::string date);
    void new_action(Choice choice);
};

std::ostream& operator<<(std::ostream& os, order_status status);

#endif //RISK_MANAGER_H
