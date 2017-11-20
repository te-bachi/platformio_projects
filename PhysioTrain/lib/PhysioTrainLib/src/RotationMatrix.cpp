/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 23.04.2017
 *
 * https://github.com/te-bachi/PhysioTrainLib
 */

#include "config.h"
#include "RotationMatrix.h"

#include "avr/dtostrf.h"

RotationMatrix::RotationMatrix()
{
    int m;
    int n;

    for (m = 0; m < SIZE; m++) {
        for (n = 0; n < SIZE; n++) {
            a[m][n] = 0;
        }
    }
}

RotationMatrix::RotationMatrix(const RotationMatrix& rot)
{
    int m;
    int n;

    for (m = 0; m < SIZE; m++) {
        for (n = 0; n < SIZE; n++) {
            a[m][n] = rot.a[m][n];
        }
    }
}

RotationMatrix::~RotationMatrix()
{
    //
}

float
RotationMatrix::getElement(int m, int n)
{
    if (m >= 0 && m < SIZE && n >= 0 && n < SIZE) {
        return a[m][n];
    }
    return 0.0f;
}

String
RotationMatrix::toString()
{
    String res = "";
    char str[16];
    int  m;
    int  n;

    for (m = 0; m < SIZE; m++) {
        for (n = 0; n < SIZE; n++) {
            dtostrf(a[m][n], 8, 4, str);
            res += str;
            res += " ";
        }
    }

    return res;
}

String
RotationMatrix::toStringMatrix()
{
    String res = "";
    char str[16];
    int  m;
    int  n;

    for (m = 0; m < SIZE; m++) {
        res += "  ";
        for (n = 0; n < SIZE; n++) {
            dtostrf(a[m][n], 8, 4, str);
            res += str;
            res += " ";
        }
        res += "\n";
    }

    return res;
}
