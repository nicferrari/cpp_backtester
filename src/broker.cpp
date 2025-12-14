#include "broker.h"

#include "results.h"
#include "risk_manager.h"

//updates account and position and then returns an Order(side, OPEN) if any was SENT; otherwise returns previous Order
Order Broker::executeOrder(Order order, const double price, std::string date, Results& results) {
    if (order.status == SENT) {
        //close any existing position
        if (this->position!=0) {
            order.end_date=date;
            order.status = CLOSED;
            results.trade.push_back(order);
        }
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
        results.trades_nr++;
        return {order.choice, OPEN, date};
    }
    return order;
}

Broker::Broker(const double account) {
    this->currentStance=NA;
    this->position=0;
    this->account=account;
}