//
//  Utilities.cpp
//  MS1
//
//  Created by Artem Pankov on 2022-11-14.
//
// Name: Artem Pankov
// Seneca Student ID: 109060210
// Seneca email: apankov@myseneca.ca
// Date of completion: 15 NOV 2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Utilities.h"
#include <iostream>

namespace sdds {

char Utilities::m_delimiter;

void Utilities::setFieldWidth(size_t newWidth) {
    m_widthField = newWidth;
}

size_t Utilities::getFieldWidth() const {
    return m_widthField;
}

std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
    std::string result;
    if (str[next_pos] == m_delimiter) {
        more = false;
        throw std::string("Exc");
    }
    else {
        size_t pos = str.find(m_delimiter, next_pos);
        if (pos == std::string::npos) {
            more = false;
            result = str.substr(next_pos);
        }
        else {
        result = str.substr(next_pos, pos - next_pos);
        more = true;
        next_pos = pos + 1;
        }
    }
    if (result.size() > m_widthField) {
    m_widthField = result.size();
    }
    deleteSpaces(result);
    return result;
}

void deleteSpaces(std::string& inp) {
    int len = inp.length();
    if (inp[0] == ' ') {
        while(1) {
            inp.erase(0, 1);
            if (inp[0] != ' ') {
                break;
            }
            else continue;
        }
    }
    len = inp.length();
    int j = len - 1;
    if (inp[len - 1] == ' ') {
        while(1) {
            inp.erase(j);
            if (inp[j - 1] != ' ') {
                break;
            }
            else {
                j--;
                continue;
            }
        }
    }
}

}
