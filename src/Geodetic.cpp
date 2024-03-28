//
// Created by jds on 3/18/24.
//

#include "../include/Geodetic.h"
#include "../include/ECEF.h"

Geodetic::Geodetic(double longitude, double latitude, double altitude) : m_longitude(longitude), m_latitude(latitude), m_altitude(altitude) {
    double phi = MyGeography::D2R * m_longitude;
    double lambda = MyGeography::D2R * m_latitude;
    m_r << -sin(phi), cos(phi), 0,
           -cos(phi) * sin(lambda), -sin(phi) * sin(lambda), cos(lambda),
            cos(phi) * cos(lambda), sin(phi) * cos(lambda), sin(lambda);
}

double Geodetic::Longitude() const { return m_longitude; }

double Geodetic::Latitude() const { return m_latitude; }

double Geodetic::Altitude() const { return m_altitude; }

Eigen::Matrix3d Geodetic::R() const { return m_r; }

void Geodetic::setLongitude(double longitude) { m_longitude = longitude; }

void Geodetic::setLatitude(double latitude) { m_latitude = latitude; }

void Geodetic::setAltitude(double altitude) { m_altitude = altitude; }

ECEF Geodetic::toECEF() const {
    double phi = MyGeography::D2R * m_longitude;
    double lambda = MyGeography::D2R * m_latitude;
    double sin_lambda = sin(lambda);
    double cos_lambda = cos(lambda);
    double N = MyGeography::a / sqrt(1 - MyGeography::e_square * pow(sin_lambda, 2));
    double c = m_altitude + N;
    return {c * cos_lambda * cos(phi), c * cos_lambda * sin(phi), (c - MyGeography::e_square * N) * sin_lambda};
}