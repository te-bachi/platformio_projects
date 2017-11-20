/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 14.05.2017
 *
 * https://github.com/te-bachi/PhysioTrainLib
 */

#include "config.h"
#include "Mode.h"

Mode::Mode()
: _mode(Mode::NONE)
{

}

Mode::Mode(ModeEnum mode)
: _mode(mode)
{

}

Mode::Mode(const Mode& mode)
: _mode(mode._mode)
{

}

Mode::~Mode()
{

}

String
Mode::toString()
{
    String str;
    switch (_mode) {
        case Mode::TEACH:       str = "TEACH";      break;
        case Mode::EXERCISE:    str = "EXERCISE";   break;
        case Mode::EVALUATE:    str = "EVALUATE";   break;
        case Mode::NONE:
        default:                str = "NONE";       break;
    }
    return str;
}

Mode::ModeEnum
Mode::getMode()
{
    return _mode;
}

Mode&
Mode::operator=(Mode::ModeEnum mode)
{
    this->_mode = mode;
    return *this;
};


Mode&
Mode::operator=(const Mode &mode)
{
    this->_mode = mode._mode;
    return *this;
}

bool
Mode::operator==(Mode::ModeEnum mode) const
{
    if (_mode == mode) {
        return true;
    }
    return false;
}

bool
Mode::operator==(const Mode &mode) const
{
    if (_mode == mode._mode) {
        return true;
    }
    return false;
}



bool
Mode::operator!=(Mode::ModeEnum mode) const
{
    if (_mode != mode) {
        return true;
    }
    return false;
}

bool
Mode::operator!=(const Mode &mode) const
{
    if (_mode != mode._mode) {
        return true;
    }
    return false;
}
