//
//  LineManager.h
//  MS3
//
//  Created by Artem Pankov on 2022-11-28.
//
// Name: Artem Pankov
// Student Number: 109060210
// Email: apankov@myseneca.ca
// Date: 29 NOV 2022
#ifndef LineManager_h
#define LineManager_h

#include <vector>
#include "Workstation.h"

namespace sdds {

class LineManager {
private:
    std::vector<Workstation*> m_activeLine;
    size_t m_cntCustomerOrder;
    Workstation* m_firstStation;
public:
    LineManager(const std::string& ws, const std::vector<Workstation*>& stations);
    
    void reorderStations();
    bool run(std::ostream& os);
    void display(std::ostream& os) const;
};

}


#endif /* LineManager_h */
