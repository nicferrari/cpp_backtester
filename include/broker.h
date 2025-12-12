#ifndef BROKER_H
#define BROKER_H

#include "Results.h"
#include "risk_manager.h"

class Broker {
public:
    Choice currentStance;
    double account;
    double position;
    Order executeOrder(Order order, double price, Results& results);
    explicit Broker(double account);
};

#endif //BROKER_H
