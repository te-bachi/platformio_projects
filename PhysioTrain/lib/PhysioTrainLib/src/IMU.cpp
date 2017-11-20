/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 07.04.2017
 *
 * https://github.com/te-bachi/PhysioTrainLib
 */

#include "config.h"
#include "IMU.h"
#include "I2CMux.h"

IMU::IMU(int select)
: _select(select)
{
    // Set up _mpu-9250 interrupt input (active-low)
    //pinMode(MPU9250_INT_PIN, INPUT_PULLUP);
}

IMU::~IMU()
{
    //
}

bool
IMU::begin()
{
    if (_select == IMU_SELECT_EXTERNAL) {
        I2CMux::selectRazorSlave();
    }

//    Serial.print("MPU::setWire(");
//    Serial.print(_select, DEC);
//    Serial.print(")\n");
    _mpu.setWire(_select);



    //Serial.print("MPU::begin()\n");
    // imu.begin() should return 0 on success. Will initialize
    // I2C bus, and reset __mpu-9250 to defaults.
    if (_mpu.begin() != INV_SUCCESS) {
        return false;
    }
    //Serial.print("MPU::setup()\n");
    
    // Set up _mpu-9250 interrupt:
//    _mpu.enableInterrupt(); // Enable interrupt output
//    _mpu.setIntLevel(1);    // Set interrupt to active-low
//    _mpu.setIntLatched(1);  // Latch interrupt output
    
    // Configure sensors:
    // Set gyro full-scale range: options are 250, 500, 1000, or 2000:
    _mpu.setGyroFSR(GYRO_FSR);
    
    // Set accel full-scale range: options are 2, 4, 8, or 16 g 
    _mpu.setAccelFSR(ACCEL_FSR);
    
    // Set gyro/accel LPF: options are5, 10, 20, 42, 98, 188 Hz
    _mpu.setLPF(AG_LPF); 
    
    // Set gyro/accel sample rate: must be between 4-1000Hz
    // (note: this value will be overridden by the DMP sample rate)
    _mpu.setSampleRate(AG_SAMPLE_RATE); 
    
    // Set compass sample rate: between 4-100Hz
    _mpu.setCompassSampleRate(COMPASS_SAMPLE_RATE); 
    
    // Configure digital motion processor.
    // Use the FIFO to get data from the DMP.
    unsigned short dmpFeatureMask = 0;

    dmpFeatureMask |= DMP_FEATURE_SEND_CAL_GYRO;
    dmpFeatureMask |= DMP_FEATURE_SEND_RAW_ACCEL;
    dmpFeatureMask |= DMP_FEATURE_GYRO_CAL;
    dmpFeatureMask |= DMP_FEATURE_6X_LP_QUAT;
    
    // Initialize the DMP, and set the FIFO's update rate
    _mpu.dmpBegin(dmpFeatureMask, DMP_SAMPLE_RATE);
    
    return true; // Return success
}

bool
IMU::update()
{
    if (_select == IMU_SELECT_EXTERNAL) {
        I2CMux::selectRazorSlave();
    }
    _mpu.setWire(_select);

    // New data available?
    if (!_mpu.fifoAvailable()) {
        return false;
    }
    
    // Read from the digital motion processor's FIFO
    if (_mpu.dmpUpdateFifo() != INV_SUCCESS) {
        return false;
    }

    // If enabled, read from the compass.
    if (_mpu.updateCompass() != INV_SUCCESS) {
        return false;
    }

    
    return true;
}

Acceleration
IMU::getAcceleration()
{
    float ax = _mpu.calcAccel(_mpu.ax);
    float ay = _mpu.calcAccel(_mpu.ay);
    float az = _mpu.calcAccel(_mpu.az);

    return Acceleration(ax, ay, az);
}

Quaternion
IMU::getQuaternion()
{
    float qw = _mpu.calcQuat(_mpu.qw);
    float qx = _mpu.calcQuat(_mpu.qx);
    float qy = _mpu.calcQuat(_mpu.qy);
    float qz = _mpu.calcQuat(_mpu.qz);

    return Quaternion(qw, qx, qy, qz);
}

QuaternionFixedPoint
IMU::getQuaternionFixedPoint()
{
    return QuaternionFixedPoint(_mpu.qw, _mpu.qx, _mpu.qy, _mpu.qz);
}

EulerAngle
IMU::getEulerAngle()
{
    _mpu.computeEulerAngles();
    return EulerAngle(_mpu.roll, _mpu.pitch, _mpu.yaw);
}

