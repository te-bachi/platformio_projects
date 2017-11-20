/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 07.04.2017
 *
 * https://github.com/te-bachi/PhysioTrainLib
 */

#ifndef __IMU_H__
#define __IMU_H__

// MPU-9250 Digital Motion Processing (DMP) Library
#include <SparkFunMPU9250-DMP.h>

#include "Acceleration.h"
#include "Quaternion.h"
#include "QuaternionFixedPoint.h"
#include "EulerAngle.h"


class IMU {
    
    private:
        int                     _select;
        MPU9250_DMP             _mpu;

        
    public:
        
        const static int                MPU9250_INT_PIN         = 4;
        const static int                MPU9250_INT_ACTIVE      = LOW;
        const static unsigned short     DMP_SAMPLE_RATE         = 100;
        const static int                COMPASS_SAMPLE_RATE     = 100;
        const static int                AG_SAMPLE_RATE          = 100;
        const static unsigned short     GYRO_FSR                = 2000;
        const static unsigned short     ACCEL_FSR               = 2;
        const static int                AG_LPF                  = 5;
        const static bool               ENABLE_GYRO_CALIBRATION = true;


                                IMU(int select);
        virtual                 ~IMU();
        bool                    begin();
        bool                    update();
        Acceleration            getAcceleration();
        Quaternion              getQuaternion();
        QuaternionFixedPoint    getQuaternionFixedPoint();
        EulerAngle              getEulerAngle();
};

#endif

