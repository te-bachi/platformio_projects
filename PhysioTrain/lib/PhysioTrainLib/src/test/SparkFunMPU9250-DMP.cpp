
#ifndef ARDUINO

#include "SparkFunMPU9250-DMP.h"

MPU9250_DMP::MPU9250_DMP()
{
}

inv_error_t MPU9250_DMP::begin()
{
    return INV_SUCCESS;
}

void MPU9250_DMP::setWire(int select)
{

}

inv_error_t MPU9250_DMP::enableInterrupt(unsigned char enable)
{
    return INV_SUCCESS;
}

inv_error_t MPU9250_DMP::setIntLevel(unsigned char active_low)
{
    return INV_SUCCESS;
}

inv_error_t MPU9250_DMP::setIntLatched(unsigned char enable)
{
    return INV_SUCCESS;
}

short MPU9250_DMP::getIntStatus(void)
{
    return 0;
}

inv_error_t MPU9250_DMP::lowPowerAccel(unsigned short rate)
{
    return INV_SUCCESS;
}

inv_error_t MPU9250_DMP::setGyroFSR(unsigned short fsr)
{
    return INV_SUCCESS;
}

inv_error_t MPU9250_DMP::setAccelFSR(unsigned char fsr)
{
    return INV_SUCCESS;
}

unsigned short MPU9250_DMP::getGyroFSR(void)
{
    return 0;
}

unsigned char MPU9250_DMP::getAccelFSR(void)
{
    return 0;
}

unsigned short MPU9250_DMP::getMagFSR(void)
{
    return 0;
}

inv_error_t MPU9250_DMP::setLPF(unsigned short lpf)
{
    return INV_SUCCESS;
}

unsigned short MPU9250_DMP::getLPF(void)
{
    return 0;
}

inv_error_t MPU9250_DMP::setSampleRate(unsigned short rate)
{
    return INV_SUCCESS;
}

unsigned short MPU9250_DMP::getSampleRate(void)
{
    return 0;
}

inv_error_t MPU9250_DMP::setCompassSampleRate(unsigned short rate)
{
    return INV_SUCCESS;
}

unsigned short MPU9250_DMP::getCompassSampleRate(void)
{
    return 0;
}

float MPU9250_DMP::getGyroSens(void)
{
    return 0.0f;
}
	
unsigned short MPU9250_DMP::getAccelSens(void)
{
    return 0;
}

float MPU9250_DMP::getMagSens(void)
{
    return 0.0f;
}

unsigned char MPU9250_DMP::getFifoConfig(void)
{
    return INV_SUCCESS;
}

inv_error_t MPU9250_DMP::configureFifo(unsigned char sensors)
{
    return INV_SUCCESS;
}

inv_error_t MPU9250_DMP::resetFifo(void)
{
    return INV_SUCCESS;
}

unsigned short MPU9250_DMP::fifoAvailable(void)
{
    return 0;
}

inv_error_t MPU9250_DMP::updateFifo(void)
{
    return INV_SUCCESS;
}

inv_error_t MPU9250_DMP::setSensors(unsigned char sensors)
{
    return INV_SUCCESS;
}

bool MPU9250_DMP::dataReady()
{
    return false;
}

inv_error_t MPU9250_DMP::update(unsigned char sensors)
{
    return INV_SUCCESS;
}

int MPU9250_DMP::updateAccel(void)
{
    return 0;
}

int MPU9250_DMP::updateGyro(void)
{
    return 0;
}

int MPU9250_DMP::updateCompass(void)
{
    return 0;
}

inv_error_t MPU9250_DMP::updateTemperature(void)
{
    return INV_SUCCESS;
}

int MPU9250_DMP::selfTest(unsigned char debug)
{
    return 0;
}

inv_error_t MPU9250_DMP::dmpBegin(unsigned short features, unsigned short fifoRate)
{
    return INV_SUCCESS;
}

inv_error_t MPU9250_DMP::dmpLoad(void)
{
    return INV_SUCCESS;
}

unsigned short MPU9250_DMP::dmpGetFifoRate(void)
{
    return 0;
}

inv_error_t MPU9250_DMP::dmpSetFifoRate(unsigned short rate)
{
    return INV_SUCCESS;
}

inv_error_t MPU9250_DMP::dmpUpdateFifo(void)
{
	return INV_SUCCESS;
}

inv_error_t MPU9250_DMP::dmpEnableFeatures(unsigned short mask)
{
    return INV_SUCCESS;
}

unsigned short MPU9250_DMP::dmpGetEnabledFeatures(void)
{
    return 0;
}

inv_error_t MPU9250_DMP::dmpSetTap(
        unsigned short xThresh, unsigned short yThresh, unsigned short zThresh,
        unsigned char taps, unsigned short tapTime, unsigned short tapMulti)
{
    return INV_SUCCESS;
}

unsigned char MPU9250_DMP::getTapDir(void)
{
    return 0;
}

unsigned char MPU9250_DMP::getTapCount(void)
{
    return 0;
}

bool MPU9250_DMP::tapAvailable(void)
{
    return false;
}

inv_error_t MPU9250_DMP::dmpSetOrientation(const signed char * orientationMatrix)
{
    return INV_SUCCESS;
}

unsigned char MPU9250_DMP::dmpGetOrientation(void)
{
    return 0;
}

inv_error_t MPU9250_DMP::dmpEnable3Quat(void)
{
    return INV_SUCCESS;
}
	
unsigned long MPU9250_DMP::dmpGetPedometerSteps(void)
{
    return 0;
}

inv_error_t MPU9250_DMP::dmpSetPedometerSteps(unsigned long steps)
{
    return INV_SUCCESS;
}

unsigned long MPU9250_DMP::dmpGetPedometerTime(void)
{
    return 0;
}

inv_error_t MPU9250_DMP::dmpSetPedometerTime(unsigned long time)
{
    return INV_SUCCESS;
}

float MPU9250_DMP::calcAccel(int axis)
{
    return 0.0f;
}

float MPU9250_DMP::calcGyro(int axis)
{
    return 0.0f;
}

float MPU9250_DMP::calcMag(int axis)
{
    return 0.0f;
}

float MPU9250_DMP::calcQuat(long axis)
{
    return 0.0f;
}

void MPU9250_DMP::computeEulerAngles(bool degrees)
{
    //
}

float MPU9250_DMP::computeCompassHeading(void)
{
    return 0.0f;
}

#endif
