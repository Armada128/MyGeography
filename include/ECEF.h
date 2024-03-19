//
// Created by jds on 3/18/24.
//

#ifndef MYGEOGRAPHY_ECEF_H
#define MYGEOGRAPHY_ECEF_H

#include "Geodetic.h"

class ENU;

class ECEF {
public:
//    ECEF();
    ECEF(double x, double y, double z);
    double x() const;
    double y() const;
    double z() const;
    void setX(double x);
    void setY(double y);
    void setZ(double z);
    ECEF operator +(const ECEF& ecef) const;
    ECEF operator -(const ECEF& ecef) const;
    Geodetic toGeodetic(double initLatitude) const;
    ENU toENU(const Geodetic& origin) const;

private:
    double m_x, m_y, m_z;
};


#endif //MYGEOGRAPHY_ECEF_H
