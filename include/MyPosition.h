//
// Created by jds on 3/18/24.
//

#ifndef MYGEOGRAPHY_MYPOSITION_H
#define MYGEOGRAPHY_MYPOSITION_H

#include <array>

class MyPosition {
public:
    char status{-1};
    double longitude{0}, latitude{0}, altitude{0};
    long cov_type{0};
    std::array<double, 9> cov{};
};


#endif //MYGEOGRAPHY_MYPOSITION_H
