//
// Created by jds on 3/19/24.
//

#include "../include/Unicore.h"

std::optional<MyPosition> Unicore::BESTPOS(const std::vector<std::string> &packet) {
    if (packet.size() < 16) return std::nullopt;
    if ((*packet.begin()).find("BESTPOSA") == std::string::npos) return std::nullopt;
    MyPosition res;
    try {
        res.latitude = std::stod(packet.at(3), nullptr);
        res.longitude = std::stod(packet.at(4), nullptr);
        res.altitude = std::stod(packet.at(5), nullptr);
        res.cov_type = std::stol(packet.at(15), nullptr, 10);
        auto cov_lon = std::stod(packet.at(9), nullptr);
        auto cov_lat = std::stod(packet.at(8), nullptr);
        auto cov_alt = std::stod(packet.at(10), nullptr);
        res.cov.at(0) = cov_lon;
        res.cov.at(4) = cov_lat;
        res.cov.at(8) = cov_alt;
        auto pos_status = std::stol(packet.at(2), nullptr, 10);
        switch (pos_status) {
            case 0: {
                res.status = -1;
                break;
            }
            case 16: {
                res.status = 0;
                break;
            }
            case 17:
            case 18:
            case 32:
            case 33:
            case 34: {
                res.status = 1;
                break;
            }
            case 48:
            case 49:
            case 50: {
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

std::optional<MyXYZ> Unicore::BESTXYZ(const std::vector<std::string>& packet) {
    if (packet.size() < 6) return std::nullopt;
    if ((*packet.begin()).find("BESTXYZA") == std::string::npos) return std::nullopt;
    MyXYZ res;
    try {
        res.x = std::stod(packet.at(3), nullptr);
        res.y = std::stod(packet.at(4), nullptr);
        res.z = std::stod(packet.at(5), nullptr);
        auto pos_status = std::stol(packet.at(2), nullptr, 10);
        switch (pos_status) {
            case 0: {
                res.status = -1;
                break;
            }
            case 16: {
                res.status = 0;
                break;
            }
            case 17:
            case 18:
            case 32:
            case 33:
            case 34: {
                res.status = 1;
                break;
            }
            case 48:
            case 49:
            case 50: {
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

std::optional<MyHeading> Unicore::HEADINGA(const std::vector<std::string>& packet) {
    if (packet.size() < 6) return std::nullopt;
    if ((*packet.begin()).find("HEADINGA") == std::string::npos) return std::nullopt;
    MyHeading res;
    try {
        res.heading = std::stod(packet.at(4), nullptr);
        res.pitch = std::stod(packet.at(5), nullptr);
        return res;
    } catch (std::invalid_argument& e) {
        return std::nullopt;
    }
}

std::optional<MyVelocity> Unicore::BESTVEL(const std::vector<std::string>& packet) {
    if (packet.size() < 7) return std::nullopt;
    if ((*packet.begin()).find("BESTVEL") == std::string::npos) return std::nullopt;
    MyVelocity res;
    try {
        res.velocity = std::stod(packet[5], nullptr) * 3.6;
        res.direction = std::stod(packet[6], nullptr);
        return res;
    } catch (std::invalid_argument& e) {
        return std::nullopt;
    }
}