//
//  Station.h
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

#ifndef Station_h
#define Station_h

#include <string>
#include "Utilities.h"

namespace sdds {

class Station {
private:
    int id;
    std::string name;
    std::string description;
    unsigned int number;
    unsigned int items;
    static int id_generator;
    static size_t m_widthField;
public:
    Station(const std::string&);
    const std::string& getItemName() const {return name;};
    size_t getNextSerialNumber() {number++; return number - 1;};
    size_t getQuantity() const {return items;};
    void updateQuantity() {if (items >= 1) items--;};
    void display(std::ostream& os, bool full) const;
};

}

#endif /* Station_h */
