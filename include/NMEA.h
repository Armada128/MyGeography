//
// Created by jds on 3/19/24.
//

#ifndef MYGEOGRAPHY_NMEA_H
#define MYGEOGRAPHY_NMEA_H

#include <optional>
#include <vector>
#include "MyPosition.h"
#include "MyVelocity.h"

class NMEA {
public:
    static std::optional<MyPosition> GNGGA(const std::vector<std::string>& packet);
    static std::optional<MyVelocity> GNVTG(const std::vector<std::string>& packet);
};


#endif //MYGEOGRAPHY_NMEA_H
