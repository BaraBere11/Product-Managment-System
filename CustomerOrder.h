//
//  CustomerOrder.h
//  MS2
//
//  Created by Artem Pankov on 2022-11-18.
//
// Name: Artem Pankov
// Student Number: 109060210
// Email: apankov@myseneca.ca
// Date: 20 NOV 2022

#ifndef CustomerOrder_h
#define CustomerOrder_h

#include "Utilities.h"
#include "Station.h"
#include <iostream>
#include <iomanip>

namespace sdds {

struct Item
{
    std::string m_itemName;
    size_t m_serialNumber{0};
    bool m_isFilled{false};

    Item(const std::string& src) : m_itemName(src) {};
};

class CustomerOrder {
private:
    std::string m_name {};
    std::string m_product {};
    size_t m_cntItem {0};
    Item** m_lstItem;
    static size_t m_widthField;
public:
    CustomerOrder() {m_lstItem = nullptr;};
    CustomerOrder(const std::string& str);
    CustomerOrder(const CustomerOrder& other);
    CustomerOrder& operator=(CustomerOrder&& other);
    CustomerOrder(CustomerOrder&& other) noexcept;
    ~CustomerOrder();
    bool isOrderFilled() const;
    bool isItemFilled(const std::string& itemName) const;
    void fillItem(Station& station, std::ostream& os);
    void display(std::ostream& os) const;
};

}

#endif /* CustomerOrder_h */
