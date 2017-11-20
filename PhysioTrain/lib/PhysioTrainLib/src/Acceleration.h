/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 07.04.2017
 *
 * https://github.com/te-bachi/PhysioTrainLib
 */

#ifndef __ACCELERATION_H__
#define __ACCELERATION_H__

class Acceleration {

    private:
        float         _x;
        float         _y;
        float         _z;


    public:
                    Acceleration();
                    Acceleration(float x, float y, float z);
        virtual     ~Acceleration();

        float       getX();
        float       getY();
        float       getZ();
};

#endif

