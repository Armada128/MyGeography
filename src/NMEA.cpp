//
// Created by jds on 3/19/24.
//

#include "../include/NMEA.h"

std::optional<MyPosition> NMEA::GNGGA(const std::vector<std::string>& packet) {
    if (packet.size() < 10) return std::nullopt;
    if ((*packet.begin()).find("GNGGA") == std::string::npos && (*packet.begin()).find("GPGGA") == std::string::npos) return std::nullopt;
    MyPosition res;
    try {
        double degree = static_cast<int>(std::stod(packet.at(2), nullptr) / 100);
        double minute = (std::stod(packet.at(2), nullptr) - degree * 100) / 60;
        res.latitude = degree + minute;
        degree = static_cast<int>(std::stod(packet.at(4), nullptr) / 100);
        minute = (std::stod(packet.at(4), nullptr) - degree * 100) / 60;
        res.longitude = degree + minute;
        res.altitude = std::stod(packet.at(9), nullptr);
        res.cov_type = std::stol(packet.at(7), nullptr, 10);
        double hdop = std::stod(packet.at(8), nullptr);
        double pos_cov = hdop * hdop / 2.0;
        res.cov.at(0) = pos_cov;
        res.cov.at(4) = pos_cov;
        res.cov.at(8) = pos_cov;
        auto pos_status = std::stol(packet.at(6), nullptr, 10);
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
    } catch (std::invalid_argument& e) {
        return std::nullopt;
    }
}

std::optional<MyVelocity> NMEA::GNVTG(const std::vector<std::string>& packet) {
    if (packet.size() < 9) return std::nullopt;
    if ((*packet.begin()).find("GNVTG") == std::string::npos && (*packet.begin()).find("GPVTG") == std::string::npos) return std::nullopt;
    MyVelocity res;
    try {
        res.velocity = std::stod(packet.at(8), nullptr);
        res.direction = std::stod(packet.at(1), nullptr);
        return res;
    } catch (std::invalid_argument& e) {
        return std::nullopt;
    }
}