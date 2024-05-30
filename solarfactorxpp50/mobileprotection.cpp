#include "mobileprotection.h"

MobileProtection::MobileProtection(DefineBlind *parent):
    DefineBlind (parent)
{
}

MobileProtection::~MobileProtection()
{
}

MobileProtection *MobileProtection::clone()
{
    DefineBlind *parent = this;
    MobileProtection *target = new MobileProtection(parent);

    target->setDeltalR(this->deltalR());
    target->setEnableSolarTracking(this->getEnableSolarTracking()); // 1: equivalent characteristics for a given angle 0: Solar tracking mode
    target->setDistacneAxises(this->getDistacneAxises());
    target->setWidthBlade(this->getWidthBlade());
    target->setOrientationBlade(this->getOrientationBlade());
    target->setActualAngle(this->getActualAngle());

    return target;
}

double MobileProtection::deltalR() const
{
    return _deltalR;
}

void MobileProtection::setDeltalR(double deltalR)
{
    _deltalR = deltalR;
}

bool MobileProtection::getEnableSolarTracking() const
{
    return enableSolarTracking;
}

void MobileProtection::setEnableSolarTracking(bool value)
{
    enableSolarTracking = value;
}

double MobileProtection::getDistacneAxises() const
{
    return _distacneAxises;
}

void MobileProtection::setDistacneAxises(double distacneAxises)
{
    _distacneAxises = distacneAxises;
}

double MobileProtection::getWidthBlade() const
{
    return _widthBlade;
}

void MobileProtection::setWidthBlade(double widthBlade)
{
    _widthBlade = widthBlade;
}

double MobileProtection::getOrientationBlade() const
{
    return _orientationBlade;
}

void MobileProtection::setOrientationBlade(double orientationBlade)
{
    _orientationBlade = orientationBlade;
}

double MobileProtection::getActualAngle() const
{
    return _actualAngle;
}

void MobileProtection::setActualAngle(double actualAngle)
{
    _actualAngle = actualAngle;
}
