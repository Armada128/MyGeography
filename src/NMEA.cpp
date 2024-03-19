//
// Created by jds on 3/19/24.
//

#include "../include/NMEA.h"

std::optional<MyPosition> NMEA::GNGGA(const std::vector<std::string>& packet) {
    if (packet.size() < 10) return std::nullopt;
    if (!(*packet.begin()).find("GNGGA") && !(*packet.begin()).find("GPGGA")) return std::nullopt;
    MyPosition res;
    double degree = static_cast<int>(strtod(packet.at(2).c_str(), nullptr) / 100);
    double minute = (strtod(packet.at(2).c_str(), nullptr) - degree * 100) / 60;
    res.latitude = degree + minute;
    degree = static_cast<int>(strtod(packet.at(4).c_str(), nullptr) / 100);
    minute = (strtod(packet.at(4).c_str(), nullptr) - degree * 100) / 60;
    res.longitude = degree + minute;
    res.altitude = strtod(packet.at(9).c_str(), nullptr);
    res.cov_type = strtol(packet.at(7).c_str(), nullptr, 10);
    double hdop = strtod(packet.at(8).c_str(), nullptr);
    double pos_cov = hdop * hdop / 2.0;
    res.cov.at(0) = pos_cov;
    res.cov.at(4) = pos_cov;
    res.cov.at(8) = pos_cov;
    auto pos_status = strtol(packet.at(6).c_str(), nullptr, 10);
    switch (pos_status) {
        case 0: {
            res.status = -1;
            break;
        }
        case 1: {
            res.status = 0;
            break;
        }
        case 2:
        case 5: {
            res.status = 1;
            break;
        }
        case 4: {
            res.status = 2;
            break;
        }
        default:
            break;
    }
    return res;
}

std::optional<MyVelocity> NMEA::GNVTG(const std::vector<std::string>& packet) {
    if (packet.size() < 9) return std::nullopt;
    if (!(*packet.begin()).find("GNVTG") && !(*packet.begin()).find("GPVTG")) return std::nullopt;
    MyVelocity res;
    res.velocity = strtod(packet.at(8).c_str(), nullptr);
    res.direction = strtod(packet.at(1).c_str(), nullptr);
    return res;
}