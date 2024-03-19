//
// Created by jds on 3/18/24.
//

#ifndef MYGEOGRAPHY_GEODETIC_H
#define MYGEOGRAPHY_GEODETIC_H

#include <cmath>
#include "eigen3/Eigen/Core"

class ECEF;

constexpr double a = 6378137;
constexpr double b = 6356752;
constexpr double f = 1 / 298.257;
constexpr double e_square = f * (2 - f);
constexpr double thresLatitude = 1E-10;
constexpr double D2R = M_PI / 180;
constexpr double R2D = 180 / M_PI;

class Geodetic {
public:
//    Geodetic();
    Geodetic(double longitude, double latitude, double altitude);
    double Longitude() const;
    double Latitude() const;
    double Altitude() const;
    Eigen::Matrix3d R() const;
    void setLongitude(double longitude);
    void setLatitude(double latitude);
    void setAltitude(double altitude);
    ECEF toECEF() const;

private:
    double m_longitude, m_latitude, m_altitude;
    Eigen::Matrix3d m_r;
};


#endif //MYGEOGRAPHY_GEODETIC_H
