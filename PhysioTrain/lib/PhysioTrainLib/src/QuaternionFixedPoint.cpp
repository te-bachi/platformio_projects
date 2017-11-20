
/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 03.05.2017
 *
 * https://github.com/te-bachi/PhysioTrainLib
 */

#include "config.h"
#include "QuaternionFixedPoint.h"

QuaternionFixedPoint::QuaternionFixedPoint()
: _w(0), _x(0), _y(0), _z(0)
{
    //
}

QuaternionFixedPoint::QuaternionFixedPoint(long w, long x, long y, long z)
: _w(w), _x(x), _y(y), _z(z)
{
    //
}

QuaternionFixedPoint::QuaternionFixedPoint(const QuaternionFixedPoint& qfp)
:  _w(qfp._w), _x(qfp._x), _y(qfp._y), _z(qfp._z)
{
    //
}

QuaternionFixedPoint::~QuaternionFixedPoint()
{
    //
}

QuaternionFixedPoint
QuaternionFixedPoint::fromByteArray(byte buffer[16])
{
    QuaternionFixedPoint qfp;

    qfp._w = ( (buffer[ 0] << 24)
             + (buffer[ 1] << 16)
             + (buffer[ 2] <<  8)
             + (buffer[ 3] <<  0));

    qfp._x = ( (buffer[ 4] << 24)
             + (buffer[ 5] << 16)
             + (buffer[ 6] <<  8)
             + (buffer[ 7] <<  0));

    qfp._y = ( (buffer[ 8] << 24)
             + (buffer[ 9] << 16)
             + (buffer[10] <<  8)
             + (buffer[11] <<  0));

    qfp._z = ( (buffer[12] << 24)
             + (buffer[13] << 16)
             + (buffer[14] <<  8)
             + (buffer[15] <<  0));

    return qfp;
}

QuaternionFixedPoint
QuaternionFixedPoint::fromI2C(TwoWire* wire)
{
    byte    buffer[16];
    uint8_t i;

    /* Send request to receive quaternion*/
    wire->requestFrom(I2C_ADDRESS_RAZOR_SLAVE, sizeof(buffer));

    /* Slave may send less than requested... */
    for (i = 0; wire->available() && i < sizeof(buffer); i++) {
        /* Receive a byte */
        buffer[i] = wire->read();
    }

    return fromByteArray(buffer);
}

void
QuaternionFixedPoint::toByteArray(byte buffer[16])
{
    buffer[ 0] = (byte) ((_w >> 24) & 0xFF);
    buffer[ 1] = (byte) ((_w >> 16) & 0xFF);
    buffer[ 2] = (byte) ((_w >>  8) & 0XFF);
    buffer[ 3] = (byte) ((_w >>  0) & 0XFF);

    buffer[ 4] = (byte) ((_x >> 24) & 0xFF);
    buffer[ 5] = (byte) ((_x >> 16) & 0xFF);
    buffer[ 6] = (byte) ((_x >>  8) & 0XFF);
    buffer[ 7] = (byte) ((_x >>  0) & 0XFF);

    buffer[ 8] = (byte) ((_y >> 24) & 0xFF);
    buffer[ 9] = (byte) ((_y >> 16) & 0xFF);
    buffer[10] = (byte) ((_y >>  8) & 0XFF);
    buffer[11] = (byte) ((_y >>  0) & 0XFF);

    buffer[12] = (byte) ((_z >> 24) & 0xFF);
    buffer[13] = (byte) ((_z >> 16) & 0xFF);
    buffer[14] = (byte) ((_z >>  8) & 0XFF);
    buffer[15] = (byte) ((_z >>  0) & 0XFF);
}

void
QuaternionFixedPoint::toI2C(TwoWire* wire)
{
    byte buffer[16];

    toByteArray(buffer);

    wire->write((uint8_t *) buffer, sizeof(buffer));
}

Quaternion
QuaternionFixedPoint::getQuaternion()
{
    return Quaternion(toFloat(_w), toFloat(_x), toFloat(_y), toFloat(_z));
}

float
QuaternionFixedPoint::toFloat(long number)
{
    unsigned long   mask = 0;
    int             i;
    unsigned char   q = 30;

    for (i = 0; i < q; i++) {
        mask |= (1 << i);
    }
    return (number >> q) + ((number & mask) / (float) (2<<(q-1)));
}
