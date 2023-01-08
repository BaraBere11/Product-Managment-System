//
//  Workstation.cpp
//  MS3
//
//  Created by Artem Pankov on 2022-11-26.
//
// Name: Artem Pankov
// Student Number: 109060210
// Email: apankov@myseneca.ca
// Date: 29 NOV 2022
#include <iostream>
#include "Workstation.h"

namespace sdds {

std::deque<CustomerOrder> g_pending {};
std::deque<CustomerOrder> g_completed {};
std::deque<CustomerOrder> g_incomplete {};

void Workstation::fill(std::ostream& os) {
    if (m_orders.size() > 0) {
        m_orders.front().fillItem(*this, os);
    }
}

bool Workstation::attemptToMoveOrder() {
    bool check = false;
    if (m_orders.size() > 0) {
        if (m_orders.front().isItemFilled(getItemName())) {
            if (m_pNextStation == nullptr) {
                if (m_orders.front().isOrderFilled()) {
                    g_completed.push_back(std::move(m_orders.front()));
                }
                else {
                    g_incomplete.push_back(std::move(m_orders.front()));
                }
            }
            else {
                *m_pNextStation += std::move(m_orders.front());
            }
            m_orders.pop_front();
            check = true;
        }
        else if (getQuantity() == 0) {
            if (m_pNextStation == nullptr) {
                g_incomplete.push_back(std::move(m_orders.front()));
            }
            else {
                *m_pNextStation += std::move(m_orders.front());
            }
            m_orders.pop_front();
            check = true;
        }
    }
    return check;
}

void Workstation::setNextStation(Workstation *st) {
    if (m_pNextStation != nullptr) {
        delete m_pNextStation;
        m_pNextStation = nullptr;
    }
    m_pNextStation = st;
}

Workstation* Workstation::getNextStation() const {
    return m_pNextStation;
}

void Workstation::display(std::ostream& os) const {
    os << getItemName() << " --> ";
    if (m_pNextStation != nullptr) {
        os << m_pNextStation->getItemName() << std::endl;
    }
    else {
        os << "End of Line" << std::endl;
    }
}

Workstation& Workstation::operator+=(CustomerOrder&& other) {
    m_orders.push_back(std::move(other));
    return *this;
}
}
