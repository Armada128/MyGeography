//
// Created by jds on 3/19/24.
//

#ifndef MYGEOGRAPHY_UNICORE_H
#define MYGEOGRAPHY_UNICORE_H

#include <optional>
#include <vector>
#include "MyPosition.h"
#include "MyHeading.h"
#include "MyVelocity.h"
#include "MyXYZ.h"

class Unicore {
public:
    static std::optional<MyPosition> BESTPOS(const std::vector<std::string>& packet);
    static std::optional<MyXYZ> BESTXYZ(const std::vector<std::string>& packet);
    static std::optional<MyHeading> HEADINGA(const std::vector<std::string>& packet);
    static std::optional<MyVelocity> BESTVEL(const std::vector<std::string>& packet);
};


#endif //MYGEOGRAPHY_UNICORE_H
