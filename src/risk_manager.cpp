#include "strategy.h"
#include "risk_manager.h"



Order::Order(Choice choice, order_status status) {
    this->choice = choice;
    this->status = status;
}

void Order::new_action(Choice choice){
    if (this->choice!=choice){this->choice=choice;this->status=SENT;}
}

std::ostream& operator<<(std::ostream& os, const order_status status) {
    switch (status) {
        case SENT: os << "SENT"; break;
        case OPEN: os << "OPEN"; break;
        case CLOSED: os << "CLOSED"; break;
        case NONE: os << "NONE"; break;
    }
    return os;
}