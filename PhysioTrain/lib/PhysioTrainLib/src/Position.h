/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 23.04.2017
 *
 * https://github.com/te-bachi/PhysioTrainLib
 */

#ifndef __POSITION_H__
#define __POSITION_H__

#include "WString.h"

class Position {

    private:
        float                   _x;
        float                   _y;
        float                   _z;

    public:
                                Position();
                                Position(float x, float y, float z);
                                Position(const Position& q);
        virtual                 ~Position();

        float                   getX() const;
        float                   getY() const;
        float                   getZ() const;

        String                  toString();

        Position operator+ (const Position &other);
};

#endif

