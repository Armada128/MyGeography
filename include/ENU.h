//
// Created by jds on 3/18/24.
//

#ifndef MYGEOGRAPHY_ENU_H
#define MYGEOGRAPHY_ENU_H


class ENU {
public:
    ENU(double east, double north, double up);
    double East() const;
    double North() const;
    double Up() const;
    void setEast(double east);
    void setNorth(double north);
    void setUp(double up);
    ENU operator +(const ENU& enu) const;
    ENU operator -(const ENU& enu) const;

private:
    double m_east, m_north, m_up;
};


#endif //MYGEOGRAPHY_ENU_H
