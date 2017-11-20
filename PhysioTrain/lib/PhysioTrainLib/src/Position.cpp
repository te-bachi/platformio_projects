/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 23.04.2017
 *
 * https://github.com/te-bachi/PhysioTrainLib
 */

#include "config.h"
#include "Position.h"

#include "avr/dtostrf.h"

Position::Position()
: _x(0), _y(0), _z(0)
{
    //
}

Position::Position(float x, float y, float z)
: _x(x), _y(y), _z(z)
{
    //
}

Position::Position(const Position& q)
: _x(q._x), _y(q._y), _z(q._z)
{
    //
}

Position::~Position()
{
    //
}

float
Position::getX() const
{
    return _x;
}

float
Position::getY() const
{
    return _y;
}

float
Position::getZ() const
{
    return _z;
}

String
Position::toString()
{
    String res = "";
    char str[33];

    dtostrf(_x, 6, 4, str);
    res += str;
    res += " ";

    dtostrf(_y, 6, 4, str);
    res += str;
    res += " ";

    dtostrf(_z, 6, 4, str);
    res += str;

    return res;
}


Position
Position::operator+ (const Position &other)
{
    Position p;

    p._x = this->_x + other._x;
    p._y = this->_y + other._y;
    p._z = this->_z + other._z;

    return p;
}
