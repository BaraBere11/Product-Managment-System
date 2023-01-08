//
//  Station.cpp
//  MS1
//
//  Created by Artem Pankov on 2022-11-15.
//
// Name: Artem Pankov
// Seneca Student ID: 109060210
// Seneca email: apankov@myseneca.ca
// Date of completion: 15 NOV 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Station.h"
#include <iostream>
#include <iomanip>

namespace sdds {

size_t Station::m_widthField;
int Station::id_generator;

Station::Station(const std::string& str) {
    Utilities s;
    bool more;
    size_t pos = 0;
    name = s.extractToken(str, pos, more);
    deleteSpaces(name);
    number = stoi(s.extractToken(str, pos, more));
    items = stoi(s.extractToken(str, pos, more));
    if (s.getFieldWidth() > m_widthField) {
        m_widthField = s.getFieldWidth();
    }
    description = s.extractToken(str, pos, more);
    deleteSpaces(description);
    id_generator ++;
    id = id_generator;
}

void Station::display(std::ostream& os, bool full) const {
    os << std::setfill('0') << std::setw(3) << std::right << id << " | " << std::setfill(' ');
    os << std::setw(int(m_widthField)) << std::left << name << " | ";
    os << std::setfill('0') << std::setw(6) << std::right << number << " | " << std::setfill(' ');
    if (full == true) {
        os << std::setw(4) << items << " | ";
        os << description;
    }
    os << std::endl;
}



}
