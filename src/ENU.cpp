//
// Created by jds on 3/18/24.
//

#include "../include/ENU.h"

ENU::ENU(double east, double north, double up) : m_east(east), m_north(north), m_up(up) {}

double ENU::East() const { return m_east; }

double ENU::North() const { return m_north; }

double ENU::Up() const { return m_up; }

void ENU::setEast(double east) { m_east = east; }

void ENU::setNorth(double north) { m_north = north; }

void ENU::setUp(double up) { m_up = up; }

ENU ENU::operator +(const ENU& enu) const { return {m_east + enu.m_east, m_north + enu.m_north, m_up + enu.m_up}; }

ENU ENU::operator -(const ENU& enu) const { return {m_east - enu.m_east, m_north - enu.m_north, m_up - enu.m_up}; }