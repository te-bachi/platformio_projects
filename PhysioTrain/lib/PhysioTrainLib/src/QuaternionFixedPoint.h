/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 03.05.2017
 *
 * https://github.com/te-bachi/PhysioTrainLib
 */

#ifndef __QUATERNION_FIXED_POINT_H__
#define __QUATERNION_FIXED_POINT_H__

#include "Quaternion.h"
#include "Wire.h"

class QuaternionFixedPoint {

    private:
        long                        _w;
        long                        _x;
        long                        _y;
        long                        _z;

    public:
                                    QuaternionFixedPoint();
                                    QuaternionFixedPoint(long  w, long x, long y, long z);
                                    QuaternionFixedPoint(const QuaternionFixedPoint& qfp);
        virtual                     ~QuaternionFixedPoint();

        static QuaternionFixedPoint fromByteArray(byte bytes[16]);
        static QuaternionFixedPoint fromI2C(TwoWire* wire);
        void                        toByteArray(byte bytes[16]);
        void                        toI2C(TwoWire* wire);
        Quaternion                  getQuaternion();

    private:
        float                       toFloat(long number);
};

#endif

