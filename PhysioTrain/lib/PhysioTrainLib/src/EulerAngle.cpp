/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 07.04.2017
 *
 * https://github.com/te-bachi/PhysioTrainLib
 */

#include "EulerAngle.h"

EulerAngle::EulerAngle()
: _roll(0), _pitch(0), _yaw(0)
{
    //
}

EulerAngle::EulerAngle(float roll, float pitch, float yaw)
: _roll(roll), _pitch(pitch), _yaw(yaw)
{
    //
}

EulerAngle::~EulerAngle()
{
    //
}

float
EulerAngle::getRoll()
{
    return _roll;
}

void
EulerAngle::setRoll(float roll)
{
    _roll = roll;
}
        
float
EulerAngle::getPitch()
{
    return _pitch;
}

void
EulerAngle::setPitch(float pitch)
{
    _pitch = pitch;
}
        
float
EulerAngle::getYaw()
{
    return _yaw;
}

void
EulerAngle::setYaw(float yaw)
{
    _yaw = yaw;
}

/*
void MPU9250_DMP::computeEulerAngles(bool degrees)
{
    float dqw = qToFloat(qw, 30);
    float dqx = qToFloat(qx, 30);
    float dqy = qToFloat(qy, 30);
    float dqz = qToFloat(qz, 30);
    
    float ysqr = dqy * dqy;
    float t0 = -2.0f * (ysqr + dqz * dqz) + 1.0f;
    float t1 = +2.0f * (dqx * dqy - dqw * dqz);
    float t2 = -2.0f * (dqx * dqz + dqw * dqy);
    float t3 = +2.0f * (dqy * dqz - dqw * dqx);
    float t4 = -2.0f * (dqx * dqx + ysqr) + 1.0f;
  
	// Keep t2 within range of asin (-1, 1)
    t2 = t2 > 1.0f ? 1.0f : t2;
    t2 = t2 < -1.0f ? -1.0f : t2;
  
    pitch = asin(t2) * 2;
    roll = atan2(t3, t4);
    yaw = atan2(t1, t0);
	
	if (degrees)
	{
		pitch *= (180.0 / PI);
		roll *= (180.0 / PI);
		yaw *= (180.0 / PI);
		if (pitch < 0) pitch = 360.0 + pitch;
		if (roll < 0) roll = 360.0 + roll;
		if (yaw < 0) yaw = 360.0 + yaw;	
	}
}
*/
