/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 07.04.2017
 *
 * https://github.com/te-bachi/PhysioTrainLib
 */

#ifndef __EULER_ANGLE_H__
#define __EULER_ANGLE_H__

class EulerAngle {
    
    private:
        float         _roll;
        float         _pitch;
        float         _yaw;

        
    public:
                    EulerAngle();
                    EulerAngle(float roll, float pitch, float yaw);
        virtual     ~EulerAngle();

        float       getRoll();
        void        setRoll(float roll);
        
        float       getPitch();
        void        setPitch(float pitch);
        
        float       getYaw();
        void        setYaw(float yaw);
};

#endif

