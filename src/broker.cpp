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
            results.trade.back().status=CLOSED;
            results.trade.back().end_date=date;
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
            results.trade.push_back(Order{order.choice, OPEN,date});
            results.trades_nr++;
        } else if (order.choice == SHORT) {
            this->position = -account/price;
            this->account += account;
            results.trade.push_back(Order{order.choice, OPEN,date});
            results.trades_nr++;
        }
        //update stance and status
        this->currentStance = order.choice;
        //results.trades_nr++;
        //results.trade.push_back(Order{order.choice, OPEN,date});
        return {order.choice, OPEN, date};
    }
    return order;
}

Broker::Broker(const double account) {
    this->currentStance=NA;
    this->position=0;
    this->account=account;
}

void Broker::forceCloseLastTrade(double price, std::string date, Results &results) {
    results.trade.back().end_date = date;
    results.trade.back().status = CLOSED;
    if (results.trade.back().choice== LONG) {
        this->account = this->position*price;
        this->position=0;
    } else if (results.trade.back().choice == SHORT){
        this->account -= -this->position*price;
        this->position=0;
    }
}

