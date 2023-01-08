//
//  LineManager.cpp
//  MS3
//
//  Created by Artem Pankov on 2022-11-28.
//
// Name: Artem Pankov
// Student Number: 109060210
// Email: apankov@myseneca.ca
// Date: 29 NOV 2022

#include <stdio.h>
#include <fstream>
#include <algorithm>
#include "Utilities.h"
#include "LineManager.h"

namespace sdds {

LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
    std::ifstream ffile(file);
    if (ffile) {
        Utilities u;
        std::string str;
        std::string cStName;
        std::string nStName;
        Workstation* next = nullptr;
        Workstation* curr = nullptr;
        Workstation* first = nullptr;
        while (!ffile.eof()) {
            std::getline(ffile, str);
            size_t npos = 0;
            bool more = false;
            cStName = u.extractToken(str, npos, more);
            curr = *std::find_if(stations.begin(), stations.end(), [&](Workstation* exm) {
                if (exm->getItemName() == cStName) {
                    return true;
                }
                return false;
            });
            m_activeLine.push_back(curr);
            if (more == true) {
                nStName = u.extractToken(str, npos, more);
                next = *std::find_if(stations.begin(), stations.end(), [&](Workstation* exm) {
                    if (exm->getItemName() == nStName) {
                        return true;
                    }
                    return false;
                });
                curr->setNextStation(next);
            }
        }
        for_each(stations.begin(), stations.end(), [&](Workstation* exm) {
            first = *find_if(stations.begin(), stations.end(), [&](Workstation* st) {
                if (st->getNextStation() == first) {
                    return true;
                }
                return false;
            });
        });
        m_firstStation = first;
    }
    else {
        throw std::string("No file..");
    }
    ffile.close();
    m_cntCustomerOrder = g_pending.size();
}

void LineManager::reorderStations() {
    Workstation* exm = m_firstStation;
    size_t i = 0;
    while (exm != nullptr) {
        m_activeLine[i] = exm;
        exm = exm->getNextStation();
        i++;
    }
}

void LineManager::display(std::ostream& os) const {
    if (m_activeLine.size() > 0) {
        for (auto& exm : m_activeLine) {
            exm->display(os);
        }
    }
}

bool LineManager::run(std::ostream& os){
    static size_t i = 0;
    i++;
    os << "Line Manager Iteration: " << i << std::endl;
    if (g_pending.size() > 0) {
        *m_firstStation += std::move(g_pending.front());
        g_pending.pop_front();
    }
    std::for_each(m_activeLine.begin(),m_activeLine.end(), [&os](Workstation* exm){
        exm->fill(os);
    });
    std::for_each(m_activeLine.begin(),m_activeLine.end(), [](Workstation* exm){
        exm->attemptToMoveOrder();
    });
    if (m_cntCustomerOrder == (g_completed.size() + g_incomplete.size())) {
        return true;
    }
    else {
        return false;
    }
}

}
