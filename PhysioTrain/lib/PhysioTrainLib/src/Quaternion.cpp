/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 07.04.2017
 *
 * https://github.com/te-bachi/PhysioTrainLib
 */

#include "config.h"
#include "Quaternion.h"

#include "avr/dtostrf.h"

Quaternion::Quaternion()
: _w(0), _x(0), _y(0), _z(0)
{
    //
}

Quaternion::Quaternion(float w, float x, float y, float z)
: _w(w), _x(x), _y(y), _z(z)
{
    //
}

Quaternion::Quaternion(const Quaternion& q)
:  _w(q._w), _x(q._x), _y(q._y), _z(q._z)
{
    //
}

Quaternion::~Quaternion()
{
    //
}

String
Quaternion::toString()
{
    String res = "";
    char str[33];

    dtostrf(_w, 6, 4, str);
    res += str;
    res += " ";

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

Quaternion
Quaternion::diff(const Quaternion &a, const Quaternion &b)
{
    Quaternion inv = a;
    inv.inverse();
    return inv * b;
}

void
Quaternion::inverse()
{
    Quaternion qu = (*this);
    qu.conjugate();
    (*this) = qu / Quaternion::dot((*this), (*this));
}


void
Quaternion::conjugate()
{
    Quaternion qu;

    qu._w = this->_w;
    qu._x = -this->_x;
    qu._y = -this->_y;
    qu._z = -this->_z;

    (*this) = qu;
}

float
Quaternion::dot(const Quaternion &q1, const Quaternion &q2)
{
    return q1._w*q2._w + q1._x*q2._x + q1._y*q2._y + q1._z*q2._z;
}


float
Quaternion::getW()
{
    return _w;
}

float
Quaternion::getX()
{
    return _x;
}

float
Quaternion::getY()
{
    return _y;
}

float
Quaternion::getZ()
{
    return _z;
}

void
Quaternion::setW(float w)
{
    _w = w;
}

void
Quaternion::setX(float x)
{
    _x = x;
}

void
Quaternion::setY(float y)
{
    _y = y;
}

void
Quaternion::setZ(float z)
{
    _z = z;
}

RotationMatrix
Quaternion::getRotationMatrix()
{
    RotationMatrix rot;

    rot.a[0][0] = 1 - 2 * (_y * _y + _z * _z);
    rot.a[0][1] =     2 * (_x * _y - _w * _z);
    rot.a[0][2] =     2 * (_x * _z + _w * _y);

    rot.a[1][0] =     2 * (_x * _y + _w * _z);
    rot.a[1][1] = 1 - 2 * (_x * _x + _z * _z);
    rot.a[1][2] =     2 * (_y * _z - _w * _x);

    rot.a[2][0] =     2 * (_x * _z - _w * _y);
    rot.a[2][1] =     2 * (_y * _z + _w * _x);
    rot.a[2][2] = 1 - 2 * (_x * _x + _y * _y);

    return rot;
}

Quaternion
Quaternion::operator*(const Quaternion &q)
{
    Quaternion qu;
    qu._w = this->_w*q._w - this->_x*q._x - this->_y*q._y - this->_z*q._z;
    qu._x = this->_w*q._x + this->_x*q._w + this->_y*q._z - this->_z*q._y;
    qu._y = this->_w*q._y + this->_y*q._w + this->_z*q._x - this->_x*q._z;
    qu._z = this->_w*q._z + this->_z*q._w + this->_x*q._y - this->_y*q._x;
    return qu;
}

Quaternion
Quaternion::operator/ (const float s)
{
    Quaternion qu = (*this);
    return Quaternion(qu._w / s, qu._x / s, qu._y / s, qu._z / s);
}
