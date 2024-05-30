#include "opaquewall.h"

OpaqueWall::OpaqueWall()
{

}

OpaqueWall::~OpaqueWall()
{

}

double OpaqueWall::surfaceAp() const
{
    return _surfaceAp;
}

void OpaqueWall::setSurfaceAp(double surfaceAp)
{
    _surfaceAp = surfaceAp;
}

double OpaqueWall::lpPerimeter() const
{
    return _lpPerimeter;
}

void OpaqueWall::setLpPerimeter(double lpPerimeter)
{
    _lpPerimeter = lpPerimeter;
}

double OpaqueWall::coefUp() const
{
    return _coefUp;
}

void OpaqueWall::setCoefUp(double coefUp)
{
    _coefUp = coefUp;
}

double OpaqueWall::coefBinding() const
{
    return _coefBinding;
}

void OpaqueWall::setCoefBinding(double coefBinding)
{
    _coefBinding = coefBinding;
}

double OpaqueWall::coefEnergyAbsorption() const
{
    return _coefEnergyAbsorption;
}

void OpaqueWall::setCoefEnergyAbsorption(double coefEnergyAbsorption)
{
    _coefEnergyAbsorption = coefEnergyAbsorption;
}
