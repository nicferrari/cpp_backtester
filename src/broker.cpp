#include "broker.h"
#include "risk_manager.h"

Order Broker::executeOrder(Order order, double price) {
    if (order.status == SENT) {
        //close any existing position
        if (this->currentStance ==LONG) {
            this->account = this->position*price;
            this->position=0;
        } else if (this->currentStance == SHORT){
            this->account -= -this->position*price;
            this->position=0;
        }
        //fill new order
        if (order.choice == LONG) {
            this->position = account/price;
            this->account = 0;
        } else if (order.choice == SHORT) {
            this->position = -account/price;
            this->account += account;
        }
        //update stance and status
        this->currentStance = order.choice;
        return {order.choice, OPEN};
    }
    return order;
}

Broker::Broker(const double account) {
    this->currentStance=NA;
    this->position=0;
    this->account=account;
}



