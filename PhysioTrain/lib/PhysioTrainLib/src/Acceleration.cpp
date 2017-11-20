/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 07.04.2017
 *
 * https://github.com/te-bachi/PhysioTrainLib
 */

#include "config.h"
#include "Acceleration.h"

Acceleration::Acceleration()
: _x(0), _y(0), _z(0)
{
    //
}

Acceleration::Acceleration(float x, float y, float z)
: _x(x), _y(y), _z(z)
{
    //
}

Acceleration::~Acceleration()
{
    //
}

float
Acceleration::getX()
{
    return _x;
}

float
Acceleration::getY()
{
    return _y;
}

float
Acceleration::getZ()
{
    return _z;
}
