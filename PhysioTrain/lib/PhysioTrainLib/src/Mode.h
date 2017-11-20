/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 14.05.2017
 *
 * https://github.com/te-bachi/PhysioTrainLib
 */

#ifndef __MODE_H__
#define __MODE_H__

#include "WString.h"

class Mode {
    public:
        enum ModeEnum {
            NONE,
            TEACH,
            EXERCISE,
            EVALUATE
        };

    private:
        ModeEnum        _mode;

    public:
                        Mode();
                        Mode(ModeEnum mode);
                        Mode(const Mode& mode);
        virtual         ~Mode();

        String          toString();
        ModeEnum        getMode();

        Mode& operator=(Mode::ModeEnum mode);
        Mode& operator=(const Mode &mode);

        bool operator==(Mode::ModeEnum mode) const;
        bool operator==(const Mode &mode) const;

        bool operator!=(Mode::ModeEnum mode) const;
        bool operator!=(const Mode &mode) const;
};

#endif

