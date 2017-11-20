/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 14.05.2017
 *
 * https://github.com/te-bachi/PhysioTrainLib
 */

#include "config.h"
#include "StateMachine.h"
#include "SdCard.h"
#include "PhysioTrain.h"

StateMachine::StateMachine()
: _currentState(START), /*_nextState(START), */ _mode(Mode::NONE)
{

}

StateMachine::~StateMachine()
{

}

StateMachine::State
StateMachine::getState()
{
    return _currentState;
}

String
StateMachine::toString()
{
    String str;
    switch (_currentState) {
        case State::NONE:               str = "NONE";               break;
        case State::TEACH:              str = "TEACH";              break;
        case State::TEACH_WAIT:         str = "TEACH_WAIT";         break;
        case State::TEACH_BEGIN:        str = "TEACH_BEGIN";        break;
        case State::TEACH_RUN:          str = "TEACH_RUN";          break;
        case State::TEACH_END:          str = "TEACH_END";          break;
        case State::EXERCISE:           str = "EXERCISE";           break;
        case State::EXERCISE_WAIT:      str = "EXERCISE_WAIT";      break;
        case State::EXERCISE_BEGIN:     str = "EXERCISE_BEGIN";     break;
        case State::EXERCISE_RUN:       str = "EXERCISE_RUN";       break;
        case State::EXERCISE_END:       str = "EXERCISE_END";       break;
        case State::EVALUATE:           str = "EVALUATE";           break;
        case State::EVALUATE_WAIT:      str = "EVALUATE_WAIT";      break;
        case State::EVALUATE_SERIAL:    str = "EVALUATE_SERIAL";    break;
        case State::ERROR:              str = "ERROR";              break;
        case State::START:              str = "START";              break;
        default:                        str = "<EMPTY>";            break;
    }
    return str;
}

void
StateMachine::run(Mode &mode, bool start)
{
    DateTime    now;

    switch (_currentState) {
        case State::NONE:
            checkState(mode);
            break;

        case State::TEACH:
            if (start) {
                _currentState = State::ERROR;
            } else {
                _mode         = mode;
                _currentState = State::TEACH_WAIT;
            }
            break;

        case State::TEACH_WAIT:
            if (!checkState(mode)) {
                /* Start */
                if (start) {
                    _currentState = State::TEACH_BEGIN;
                }
            }
            break;

        case State::TEACH_BEGIN:

            I2CMux::selectRtc();
            now             = rtc.now();

            teachFile       = sdCard.replaceTeachFile(now);
//            teachFile.println("hallo");
//            teachFile.println("welt");
//            teachFile.println("bla");

            /* Reset switch increment and local variable */
            recordSwitch.resetIncrementValue();
            _teachRunInc   = 0;

            _currentState = State::TEACH_RUN;
            break;

        case State::TEACH_RUN:
            if (!checkStateOnRun(mode, State::TEACH_END)) {

                /* Stop */
                if (!start) {
                    _currentState = State::TEACH_END;

                /* Run */
                } else {
                    teachRun();
                }
            }
            break;

        case State::TEACH_END:
        {
            I2CMux::selectRtc();
            now = rtc.now();

            sdCard.closeTeachFile(teachFile, now);

            /* Good */
            if (!start) {
                _currentState = State::TEACH;

            /* Bad */
            } else {
                _currentState = State::ERROR;
            }
            break;
        }

        case State::EXERCISE:
            if (start) {
                _currentState = State::ERROR;
            } else {
                _mode         = mode;
                _currentState = State::EXERCISE_WAIT;
            }
            break;

        case State::EXERCISE_WAIT:
            if (!checkState(mode)) {
                /* Start */
                if (start) {
                    _currentState = State::EXERCISE_BEGIN;
                }
            }
            break;

        case State::EXERCISE_BEGIN:
        {
            String line;

            _start = millis();

            I2CMux::selectRtc();
            now = rtc.now();

            sdCard.openRoot();
            sdCard.rewindRoot();
            teachFile = sdCard.openNextTeachFile();
            sdCard.closeRoot();

            /* teach file not found */
            if (!teachFile) {
                _currentState = State::ERROR;

            /* teach file found: open exercise and result file */
            } else {

                line = teachFile.readStringUntil('\n');
                SerialUSB.println(line);

                exerciseFile    = sdCard.openExerciseFile(now);
                resultFile      = sdCard.openResultFile(now);

                if (resultFile) {
                    resultFile.println("80:0");
                    resultFile.println("100:1");
                    resultFile.println("60:0");
                    resultFile.println("75:0");
                    resultFile.println("80:0");
                    resultFile.println("90:0");
                    resultFile.println("0:0");
                    resultFile.println("20:2");
                }

                _currentState = State::EXERCISE_RUN;
            }
            break;
        }

        case State::EXERCISE_RUN:
            if (!checkStateOnRun(mode, State::EXERCISE_END)) {

                /* Stop */
                if (!start) {
                    _currentState = State::EXERCISE_END;

                /* Run */
                } else {
                    exerciseRun();
                }
            }
            break;

        case State::EXERCISE_END:
        {
            I2CMux::selectRtc();
            now = rtc.now();

            teachFile.close();
            sdCard.closeExerciseFile(exerciseFile, now);
            sdCard.closeResultFile(resultFile, now);

            /* Good */
            if (!start) {
                _currentState = State::EXERCISE;

            /* Bad */
            } else {
                _currentState = State::ERROR;
            }
            break;
        }

        case State::EVALUATE:
            if (start) {
                _currentState = State::ERROR;
            } else {

                /*
                sdCard.openRoot();
                sdCard.rewindRoot();
                File file = sdCard.openNextExerciseFile();
                while (file) {
                    SerialUSB.print("==> ");
                    SerialUSB.println(file.name());
                    file.close();
                    file = sdCard.openNextExerciseFile();
                }
                sdCard.closeRoot();
                */

                _mode         = mode;
                _currentState = State::EVALUATE_WAIT;
            }
            break;

        case State::EVALUATE_WAIT:
        {
            if (!checkState(mode)) {

                /* Start Serial*/
                if (start) {
                    _currentState = State::EVALUATE_SERIAL;

                /* Checks for new serial input */
                } else if (SerialUSB.available()) {
                    char action;

                    SerialUSB.println("Serial available");

                    action = SerialUSB.read();
                    switch (action) {
                        /* Download teach files*/
                        case 't':
                            SerialUSB.println("Download teach files");
                            sdCard.downloadTeachFiles();
                            break;

                        /* Download exercise files*/
                        case 'e':
                            SerialUSB.println("Download exercise files");
                            sdCard.downloadExerciseFiles();
                            break;

                        /* Download result files*/
                        case 'r':
                            SerialUSB.println("Download result files");
                            sdCard.downloadResultFiles();
                            break;

                       /* Delete exercise and result files */
                        case 'd':
                            SerialUSB.println("Delete exercise and result files");
                            sdCard.deleteExerciseFiles();
                            sdCard.deleteResultFiles();
                            break;

                    }

                }
            }
            break;
        }

        case State::EVALUATE_SERIAL:
            if (!checkState(mode)) {

                /* Start => Error */
                if (!start) {
                    _currentState = State::EVALUATE;
                } else {
                    evaluateSerial();
                }
            }
            break;

        case State::ERROR:
            if (!start) {
                _currentState = nextState(mode);
            }
            break;

        case State::START:
        default:
            vibra.start(800);
            _currentState = nextState(mode);
            break;
    }
}


/**
 * Change mode/state NOW!
 **/
bool
StateMachine::checkState(Mode &mode)
{
    if (mode != _mode) {
        _mode         = mode;
        _currentState = nextState(mode);
        //_nextState    = nextState(mode);

        return true;
    }

    return false;
}

/**
 * Changed Mode during RUN
 **/
bool
StateMachine::checkStateOnRun(Mode &mode, StateMachine::State state)
{
    if (mode != _mode) {
        _mode           = mode;
        _currentState   = state;
        //_nextState      = nextState(mode);

        return true;
    }

    return false;
}

StateMachine::State
StateMachine::nextState(Mode &mode)
{
    if (mode == Mode::TEACH) {
        return State::TEACH;

    } else if (mode == Mode::EXERCISE) {
        return State::EXERCISE;

    } else if (mode == Mode::EVALUATE) {
        return State::EVALUATE;
    }

    return State::NONE;
}

void
StateMachine::teachRun()
{
    static int k = 0;
    String line;

    if (k % 20 == 0) {
        int inc = recordSwitch.getIncrementValue();
        if (inc > _teachRunInc) {
            _teachRunInc = inc;
            //SerialUSB.print("inc");
            //SerialUSB.println(inc);
            line = getPositionString();
            teachFile.println(line);
            vibra.start(600);
        }
    }
}

void
StateMachine::exerciseRun()
{
    static int k = 0;
    String line;

    if (k % 20 == 0) {
        line = getPositionQuaternionString();
        exerciseFile.println(line);
    }
    k++;
}

void
StateMachine::evaluateSerial()
{
    static int u = 0;
    String line;

    if (u % 20 == 0) {
        line = getSerialString();
        SerialUSB.println(line);

    }
    u++;
}


String
StateMachine::getPositionString()
{
    String line;

    Position pLower = model.getLowerArmPosition();

    line   = String(pLower.getX(), 4) + " ";
    line  += String(pLower.getY(), 4) + " ";
    line  += String(pLower.getZ(), 4);

    return line;
}

String
StateMachine::getPositionQuaternionString()
{
    String line;
    int    diff = millis() - _start;

    Position pUpper = model.getUpperArmPosition();
    Position pLower = model.getLowerArmPosition();

    line   = String("[ ");
    line  += String(diff);
    line  += String(" ] ");

    line  += String("[ ");
    line  += String(q1.getW(), 4) + ", ";
    line  += String(q1.getX(), 4) + ", ";
    line  += String(q1.getY(), 4) + ", ";
    line  += String(q1.getZ(), 4);
    line  += String(" ] ");

    line  += String("[ ");
    line  += String(pUpper.getX(), 4) + ", ";
    line  += String(pUpper.getY(), 4) + ", ";
    line  += String(pUpper.getZ(), 4);
    line  += String(" ] ");

    line  += String("[ ");
    line  += String(q2.getW(), 4) + ", ";
    line  += String(q2.getX(), 4) + ", ";
    line  += String(q2.getY(), 4) + ", ";
    line  += String(q2.getZ(), 4);
    line  += String(" ] ");

    line  += String("[ ");
    line  += String(pLower.getX(), 4) + ", ";
    line  += String(pLower.getY(), 4) + ", ";
    line  += String(pLower.getZ(), 4);
    line  += String(" ] ");

    return line;
}

String
StateMachine::getSerialString()
{
    String line;

    Position pUpper = model.getUpperArmPosition();
    Position pLower = model.getLowerArmPosition();

    line   = String("[ ");
    line  += String(millis());
    line  += String(" ] ");

    line  += String("[ ");
    line  += String(q1.getW(), 4) + ", ";
    line  += String(q1.getX(), 4) + ", ";
    line  += String(q1.getY(), 4) + ", ";
    line  += String(q1.getZ(), 4);
    line  += String(" ] ");

    line  += String("[ ");
    line  += String(pUpper.getX(), 4) + ", ";
    line  += String(pUpper.getY(), 4) + ", ";
    line  += String(pUpper.getZ(), 4);
    line  += String(" ] ");

    line  += String("[ ");
    line  += String(q2.getW(), 4) + ", ";
    line  += String(q2.getX(), 4) + ", ";
    line  += String(q2.getY(), 4) + ", ";
    line  += String(q2.getZ(), 4);
    line  += String(" ] ");

    line  += String("[ ");
    line  += String(pLower.getX(), 4) + ", ";
    line  += String(pLower.getY(), 4) + ", ";
    line  += String(pLower.getZ(), 4);
    line  += String(" ] ");

    /*
    line  += String(" mode=");
    line  += String(mode.toString());
    */

    line  += String(" record=");
    line  += String(recordValue);
    line  += String(" start=");
    line  += String(startStopValue);

    return line;
}
