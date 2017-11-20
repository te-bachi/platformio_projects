/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 23.04.2017
 *
 * https://github.com/te-bachi/PhysioTrainLib
 */

#ifndef __TRANSFORMATION_H__
#define __TRANSFORMATION_H__

#include "WString.h"
#include "Position.h"
#include "RotationMatrix.h"

class Transformation {
    public:
        typedef enum {
            TYPE_NULL,
            TYPE_EYE
        } Type;
        static const int        SIZE = 4;
        float                   a[SIZE][SIZE];

    private:

    public:
                                Transformation();
                                Transformation(Type type);
                                Transformation(Position &pos, RotationMatrix &rot);
                                Transformation(const Transformation& q);
        virtual                 ~Transformation();

        float                   getElement(int m, int n);
        String                  toString();
        String                  toStringMatrix();

        Transformation operator* (const Transformation &other);
        Position       operator* (const Position &other);

};

#endif

