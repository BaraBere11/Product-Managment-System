//
//  Workstation.h
//  MS3
//
//  Created by Artem Pankov on 2022-11-26.
//
// Name: Artem Pankov
// Student Number: 109060210
// Email: apankov@myseneca.ca
// Date: 29 NOV 2022

#ifndef Workstation_h
#define Workstation_h

#include <deque>
#include "CustomerOrder.h"
#include "Station.h"

namespace sdds {

extern std::deque<CustomerOrder> g_pending ;
extern std::deque<CustomerOrder> g_completed ;
extern std::deque<CustomerOrder> g_incomplete ;

class Workstation : public Station {
private:
    std::deque<CustomerOrder> m_orders {};
    Workstation* m_pNextStation {};
public:
    Workstation(const std::string& str) : Station(str) {};
    
    void fill(std::ostream& os);
    bool attemptToMoveOrder();
    void setNextStation(Workstation* st = nullptr);
    Workstation* getNextStation() const;
    void display(std::ostream& os) const;
    
    Workstation& operator+=(CustomerOrder&& other);
    
    Workstation(const Workstation& c) = delete;
    Workstation& operator=(const Workstation& c) = delete;
    Workstation(Workstation&& m) = delete;
    Workstation& operator=(Workstation&& m) = delete;
};

}

#endif /* Workstation_h */
