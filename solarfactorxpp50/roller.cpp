#include "roller.h"

Roller::Roller()
{
}

Roller::~Roller()
{
}

double Roller::surfaceAc() const
{
    return _surfaceAc;
}

void Roller::setSurfaceAc(double surfaceAc)
{
    _surfaceAc = surfaceAc;
}

double Roller::coefUc() const
{
    return _coefUc;
}

void Roller::setCoefUc(double coefUc)
{
    _coefUc = coefUc;
}

double Roller::coefEnergyAbsorption() const
{
    return _coefEnergyAbsorption;
}

void Roller::setCoefEnergyAbsorption(double coefEnergyAbsorption)
{
    _coefEnergyAbsorption = coefEnergyAbsorption;
}
