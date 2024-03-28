//
// Created by jds on 3/18/24.
//

#include "../include/ECEF.h"
#include "../include/ENU.h"

ECEF::ECEF(double x, double y, double z) : m_x(x), m_y(y), m_z(z) {}

double ECEF::x() const { return m_x; }

double ECEF::y() const { return m_y; }

double ECEF::z() const { return m_z; }

void ECEF::setX(double x) { m_x = x; }

void ECEF::setY(double y) { m_y = y; }

void ECEF::setZ(double z) { m_z = z; }

ECEF ECEF::operator +(const ECEF& ecef) const { return {m_x + ecef.m_x, m_y + ecef.m_y, m_z + ecef.m_z}; }

ECEF ECEF::operator -(const ECEF& ecef) const { return {m_x - ecef.m_x, m_y - ecef.m_y, m_z - ecef.m_z}; }

Geodetic ECEF::toGeodetic(double initLatitude) const {
    double longitude = MyGeography::R2D * atan2(m_y, m_x) + 180;
    double latitude;
    double latitude_last = initLatitude;
    double altitude;
    double p = sqrt(pow(m_x, 2) + pow(m_y, 2));
    int count_goodlatitude = 0;
    int count_iteration = 0;
    do{
        double L = MyGeography::D2R * latitude_last;
        double N = MyGeography::a / sqrt(1 - MyGeography::e_square * pow(sin(L), 2));
        altitude = p / cos(L) - N;
        latitude = MyGeography::R2D * atan2(m_z, p * (1 - MyGeography::e_square * N / (N + altitude)));
        if(std::abs(latitude_last - latitude) < MyGeography::thresLatitude) count_goodlatitude++;
        count_iteration++;
        latitude_last = latitude;
    } while(count_goodlatitude < 3 && count_iteration <= 20);
    return {longitude, latitude_last, altitude};
}

ENU ECEF::toENU(const Geodetic& origin) const {
    ECEF originECEF = origin.toECEF();
    ECEF relative = *this - originECEF;
    Eigen::Vector3d v_relative{relative.m_x, relative.m_y, relative.m_z};
    auto mat_enu = origin.R() * v_relative;
    return {mat_enu[0], mat_enu[1], mat_enu[2]};
}