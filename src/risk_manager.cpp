#include "data.h"
#include "strategy.h"

enum order_status {
    SENT,
    OPEN,
    CLOSED,
    NONE,
};

class Order {
    Choice choice;
    order_status status;
};

Order action(const TimeSeries& ts, Choice choice){
    return {Choice::LONG,SENT};
}