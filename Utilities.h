//
//  Utilities.h
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

#ifndef Utilities_h
#define Utilities_h

#include <string>

namespace sdds {

class Utilities {
private:
    size_t m_widthField {1};
    static char m_delimiter;
public:
    void setFieldWidth(size_t newWidth);
    size_t getFieldWidth() const;
    std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
    static void setDelimiter(char newDelimiter) {m_delimiter = newDelimiter;};
    static char getDelimiter() {return m_delimiter;};
};

void deleteSpaces(std::string& inp);

}


#endif /* Utilities_h */
