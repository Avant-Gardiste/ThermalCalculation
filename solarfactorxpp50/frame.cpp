#include "frame.h"

Frame::Frame()
{
}

Frame::~Frame()
{
}

double Frame::afSurface() const
{
    return _afSurface;
}

void Frame::setAfSurface(double afSurface)
{
    _afSurface = afSurface;
}

double Frame::ufAverage() const
{
    return _ufAverage;
}

void Frame::setUfAverage(double ufAverage)
{
    _ufAverage = ufAverage;
}

string Frame::materialType() const
{
    return _materialType;
}

void Frame::setMaterialType(string materialType)
{
    _materialType = materialType;
}

int Frame::glazingBinding() const
{
    return _glazingBinding;
}

void Frame::setGlazingBinding(int glazingBinding)
{
    _glazingBinding = glazingBinding;
}

double Frame::coefBinding() const
{
    return _coefBinding;
}

void Frame::setCoefBinding(double coefBinding)
{
    _coefBinding = coefBinding;
}

double Frame::coefEnergyAbsorption() const
{
    return _coefEnergyAbsorption;
}

void Frame::setCoefEnergyAbsorption(double coefEnergyAbsorption)
{
    _coefEnergyAbsorption = coefEnergyAbsorption;
}
