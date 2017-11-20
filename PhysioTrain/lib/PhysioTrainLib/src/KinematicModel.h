/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 25.04.2017
 *
 * https://github.com/te-bachi/PhysioTrainLib
 */

#ifndef __KINEMATIC_MODEL_H__
#define __KINEMATIC_MODEL_H__

#include "IMU.h"
#include "Quaternion.h"
#include "Position.h"

class KinematicModel {
    public:

    private:
        IMU                     *_upperImu;
        IMU                     *_lowerImu;
        float                   _upperArmLength;
        float                   _lowerArmLength;
        Quaternion              _initUpperArmQuaternion;
        Quaternion              _initLowerArmQuaternion;
        Position                _upperArmPosition;
        Position                _lowerArmPosition;

    public:
                                KinematicModel();
                                KinematicModel(const KinematicModel& model);
        virtual                 ~KinematicModel();

        void                    begin(IMU *upperImu, IMU *lowerImu);
        void                    reinitialize();
        void                    update();

        void                    setArmLength(float upperArmLength, float lowerArmLength);
        void                    setUpperArmLength(float upperArmLength);
        void                    setLowerArmLength(float lowerArmLength);

        Position                getUpperArmPosition();
        Position                getLowerArmPosition();

};

#endif

