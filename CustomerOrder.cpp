//
//  CustomerOrder.cpp
//  MS2
//
//  Created by Artem Pankov on 2022-11-19.
//
// Name: Artem Pankov
// Student Number: 109060210
// Email: apankov@myseneca.ca
// Date: 29 NOV 2022

#include "CustomerOrder.h"

namespace sdds {

size_t CustomerOrder::m_widthField;

CustomerOrder::CustomerOrder(const std::string& str) {
    Utilities s;
    bool more;
    size_t pos = 0;
    m_name = s.extractToken(str, pos, more);
    deleteSpaces(m_name);
    m_product = s.extractToken(str, pos, more);
    deleteSpaces(m_product);
    size_t p = pos;
    bool m = more;
    int counter = 0;
    while (m) {
        s.extractToken(str, p, m);
        counter++;
    }
    m_lstItem = new Item*[counter];
    m_cntItem = 0;
    while (more) {
        m_lstItem[m_cntItem] = new Item(s.extractToken(str, pos, more));
        deleteSpaces(m_lstItem[m_cntItem]->m_itemName);
        m_cntItem++;
    }
    if (s.getFieldWidth() > m_widthField) {
        m_widthField = s.getFieldWidth();
    }
}

CustomerOrder::CustomerOrder(const CustomerOrder& other) {
    throw std::string("Cannot make copies.");
}

CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept{
    m_name = other.m_name;
    m_product = other.m_product;
    m_cntItem = other.m_cntItem;
    m_lstItem = other.m_lstItem;
    other.m_lstItem = nullptr;
    other.m_lstItem = 0;
}

CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) {
    if (m_lstItem != other.m_lstItem) {
    if (m_lstItem != nullptr) {
        for (size_t i = 0; i < m_cntItem; i++) {
            delete m_lstItem[i];
        }
        delete[] m_lstItem;
        m_lstItem = nullptr;
    }
    m_name = other.m_name;
    m_product = other.m_product;
    m_cntItem = other.m_cntItem;
    m_lstItem = other.m_lstItem;
    other.m_lstItem = nullptr;
    other.m_lstItem = 0;
    return *this;
    }
    else {
        other.m_lstItem = nullptr;
        other.m_lstItem = 0;
        return *this;
    }
}


CustomerOrder::~CustomerOrder() {
    if (m_lstItem != nullptr) {
        for (size_t i = 0; i < m_cntItem; i++) {
            delete m_lstItem[i];
        }
        delete[] m_lstItem;
        m_lstItem = nullptr;
    }
}

bool CustomerOrder::isOrderFilled() const {
    for (size_t i = 0; i < m_cntItem; i++) {
        if (m_lstItem[i]->m_isFilled == false) {
            return false;
        }
    }
    return true;
}

bool CustomerOrder::isItemFilled(const std::string& itemName) const {
    for (size_t i = 0; i < m_cntItem; i++) {
        if (m_lstItem[i]->m_isFilled == false && m_lstItem[i]->m_itemName == itemName) {
            return false;
        }
    }
    return true;
}

void CustomerOrder::fillItem(Station& station, std::ostream& os) {
    bool check = true;
    for (size_t i = 0; i < m_cntItem; i++) {
        if (station.getItemName() == m_lstItem[i]->m_itemName && check && m_lstItem[i]->m_isFilled == false ) {
            if (station.getQuantity() > 0 ) {
                    station.updateQuantity();
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    m_lstItem[i]->m_isFilled = true;
                    os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                        check = false;
            }
            else {
                os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
            }
        }
    }
}

void CustomerOrder::display(std::ostream& os) const {
    os << m_name << " - " << m_product << std::endl;
    if (m_lstItem != nullptr) {
    for (size_t i = 0; i < m_cntItem; i++) {
        os << '[' << std::setw(6) << std::setfill('0') << std::right << m_lstItem[i]->m_serialNumber << std::setfill(' ') << "] ";
        os << std::setw(int(m_widthField)) << std::left << m_lstItem[i]->m_itemName;
        if (m_lstItem[i]->m_isFilled == true) {
            os << " - FILLED" << std::endl;
        }
        else {
            os << " - TO BE FILLED" << std::endl;
        }
    }
    }
}

}
