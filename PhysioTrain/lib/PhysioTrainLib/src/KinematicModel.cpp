/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 25.04.2017
 *
 * https://github.com/te-bachi/PhysioTrainLib
 */

#include "config.h"
#include "KinematicModel.h"
#include "Transformation.h"

KinematicModel::KinematicModel()
: _upperImu(NULL), _lowerImu(NULL)
{

}

KinematicModel::KinematicModel(const KinematicModel& model)
: _upperImu(model._upperImu), _lowerImu(model._lowerImu)
{

}

KinematicModel::~KinematicModel()
{
    //
}

void
KinematicModel::begin(IMU *upperImu, IMU *lowerImu)
{
    this->_upperImu = upperImu;
    this->_lowerImu = lowerImu;
}

void
KinematicModel::reinitialize()
{
    //SerialUSB.println("reinitialize() ============");
    /* Get quaternion from IMU */
    _initUpperArmQuaternion = _upperImu->getQuaternion();
    _initLowerArmQuaternion = _lowerImu->getQuaternion();

    /* Invert both */
    _initUpperArmQuaternion.inverse();
    _initLowerArmQuaternion.inverse();


}

void
KinematicModel::update()
{
    Quaternion      upperQAbs = _upperImu->getQuaternion();
    Quaternion      lowerQAbs = _lowerImu->getQuaternion();

    /* Rel_t = Abs_0^-1 * Abs_t */
    //Quaternion      upperQRel = _initUpperArmQuaternion * upperQAbs;
    //Quaternion      lowerQRel = _initLowerArmQuaternion * lowerQAbs;

    /* Rel_t = Abs_t * Abs_0^-1 */
    Quaternion      upperQRel = upperQAbs * _initUpperArmQuaternion;
    Quaternion      lowerQRel = lowerQAbs * _initLowerArmQuaternion;

    Position        p10(0.0f, 0.0f,  0.0f);
    Position        p11(0.0f, 0.0f, -_upperArmLength);
    Position        p12(0.0f, 0.0f, -_lowerArmLength);
    RotationMatrix  rot1 = upperQRel.getRotationMatrix();
    RotationMatrix  rot2 = lowerQRel.getRotationMatrix();
    Transformation  t01(p10, rot1);
    Transformation  t02(p10, rot2);
    Transformation  t03(p10, rot2);

    /*
    SerialUSB.print("upperQAbs: ");
    SerialUSB.println(upperQAbs.toString());
    SerialUSB.print("lowerQAbs: ");
    SerialUSB.println(lowerQAbs.toString());
    SerialUSB.print("upperQRel: ");
    SerialUSB.println(upperQRel.toString());
    SerialUSB.print("lowerQRel: ");
    SerialUSB.println(lowerQRel.toString());
    */

    _upperArmPosition =                     (t01 * p11);
    _lowerArmPosition = _upperArmPosition + (t02 * p12);
}

void
KinematicModel::setArmLength(float upperArmLength, float lowerArmLength)
{
    this->_upperArmLength = upperArmLength;
    this->_lowerArmLength = lowerArmLength;
}

void
KinematicModel::setUpperArmLength(float upperArmLength)
{
    this->_upperArmLength = upperArmLength;
}

void
KinematicModel::setLowerArmLength(float lowerArmLength)
{
    this->_lowerArmLength = lowerArmLength;
}

Position
KinematicModel::getUpperArmPosition()
{
    return _upperArmPosition;
}

Position
KinematicModel::getLowerArmPosition()
{
    return _lowerArmPosition;
}
