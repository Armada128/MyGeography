//
// Created by jds on 3/19/24.
//

#include "../include/Unicore.h"

std::optional<MyPosition> Unicore::BESTPOS(const std::vector<std::string> &packet) {
    if (packet.size() < 16) return std::nullopt;
    if (!(*packet.begin()).find("BESTPOS")) return std::nullopt;
    MyPosition res;
    res.latitude = strtod(packet.at(3).c_str(), nullptr);
    res.longitude = strtod(packet.at(4).c_str(), nullptr);
    res.altitude = strtod(packet.at(5).c_str(), nullptr);
    res.cov_type = strtol(packet.at(15).c_str(), nullptr, 10);
    auto cov_lon = strtod(packet.at(9).c_str(), nullptr);
    auto cov_lat = strtod(packet.at(8).c_str(), nullptr);
    auto cov_alt = strtod(packet.at(10).c_str(), nullptr);
    res.cov.at(0) = cov_lon;
    res.cov.at(4) = cov_lat;
    res.cov.at(8) = cov_alt;
    auto pos_status = strtol(packet.at(2).c_str(), nullptr, 10);
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
}

std::optional<MyHeading> Unicore::HEADINGA(const std::vector<std::string>& packet) {
    if (packet.size() < 6) return std::nullopt;
    if (!(*packet.begin()).find("HEADINGA")) return std::nullopt;
    MyHeading res;
    res.heading = strtod(packet.at(4).c_str(), nullptr);
    res.pitch = strtod(packet.at(5).c_str(), nullptr);
    return res;
}

std::optional<MyVelocity> Unicore::BESTVEL(const std::vector<std::string>& packet) {
    if (packet.size() < 7) return std::nullopt;
    if (!(*packet.begin()).find("BESTVEL")) return std::nullopt;
    MyVelocity res;
    res.velocity = strtod(packet[5].c_str(), nullptr) * 3.6;
    res.direction = strtod(packet[6].c_str(), nullptr);
    return res;
}