/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 02.05.2017
 *
 * https://github.com/te-bachi/PhysioTrainLib
 */

#include "PhysioTrain.h"
#include "Mode.h"
#include "config.h"

// pinPeripheral() function
#include "wiring_private.h"

CLI                     cli;
IMU                     imuLower(IMU_SELECT_INTERNAL);
IMU                     imuUpper(IMU_SELECT_EXTERNAL);
KinematicModel          model;

TwoWire                 muxWire(&sercom1, 11, 13);
SX1509                  ioExpander;
RTC_DS3231              rtc;
Vibra                   vibra;
                        
StateMachine            stateMachine;
Switch                  recordSwitch;
PushButton              startStopButton;
RotarySwitch            modeSwitch;

Led                     ledLeft;
Led                     ledRight;
Accumulator             accu;

SdCard                  sdCard;
File                    teachFile;
File                    exerciseFile;
File                    resultFile;


StateMachine::State     state;
Quaternion              q1;
Quaternion              q2;

Mode                    mode;
bool                    recordValue;
bool                    startStopValue;
bool                    startStopSaved = false;

PhysioTrain::PhysioTrain()
{
    //
}

PhysioTrain::~PhysioTrain()
{
    //
}

static void countdown()
{
    for (int i = PHYSIOTRAIN_COUNTDOWN; i > 0; i--) {
        SerialUSB.println(i);
        delay(1000);
    }
}

void PhysioTrain::begin()
{
    SerialUSB.begin(SERIAL_BAUD_RATE);

    countdown();

    /* Initialize SERCOM3 + SERCOM 1 as I2C masters */
    Wire3.begin();                  // SERCOM3 => internal IMU
    Wire1.begin();                  // SERCOM1 => external I2C Multiplexer
    pinPeripheral(11, PIO_SERCOM);  // Assign D11 to SERCOM
    pinPeripheral(13, PIO_SERCOM);  // Assign D13 to SERCOM

    /* GPIO Expander */
    I2CMux::selectGpioExpander();
    ioExpander.begin(&Wire1);
    recordSwitch.begin(&ioExpander, IO_IN_SWITCH_RECORD);
    startStopButton.begin(&ioExpander, IO_IN_PUSHBUTTON_START_STOP);
    ledLeft.begin(&ioExpander, IO_OUT_ACCU_INDICATION_LOW);
    ledRight.begin(&ioExpander, IO_OUT_ACCU_INDICATION_HIGH);
    modeSwitch.begin(&ioExpander, IO_IN_ROTARYSWITCH_TEACH, IO_IN_ROTARYSWITCH_EXERCISE, IO_IN_ROTARYSWITCH_EVALUATE);

    /* RTC */
    I2CMux::selectRtc();
    rtc.begin();

    /* Vibra */
    vibra.begin(&ioExpander, IO_OUT_VIBRA_PWM, IO_OUT_VIBRA_ENABLE);

    /* Accumulator */
    accu.begin(IO_IN_ACCU_MEASURE, &ledLeft, &ledRight);

    cli.begin();
    imuLower.begin();
    imuUpper.begin();
    sdCard.begin();

    model.begin(&imuUpper, &imuLower);
    model.setArmLength(KINEMATIK_UPPER_ARM_LENGTH, KINEMATIK_LOWER_ARM_LENGTH);
}
