/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 07.04.2017
 *
 * https://github.com/te-bachi/PhysioTrainLib
 */

#ifndef __QUATERNION_H__
#define __QUATERNION_H__

#include "RotationMatrix.h"

class Quaternion;

class Quaternion {
    
    private:
        float                   _w;
        float                   _x;
        float                   _y;
        float                   _z;
        
    public:
                                Quaternion();
                                Quaternion(float  w, float x, float y, float z);
                                Quaternion(const Quaternion& q);
        virtual                 ~Quaternion();

        String                  toString();

        static Quaternion       diff(const Quaternion &a, const Quaternion &b);
        static float            dot(const Quaternion &q1, const Quaternion &q2);
        
        void                    inverse();
        void                    conjugate();

        float                   getW();
        float                   getX();
        float                   getY();
        float                   getZ();
        void                    setW(float w);
        void                    setX(float x);
        void                    setY(float y);
        void                    setZ(float z);

        RotationMatrix          getRotationMatrix();

        Quaternion operator* (const Quaternion &q);
        Quaternion operator/ (const float s);
        
};

#endif

