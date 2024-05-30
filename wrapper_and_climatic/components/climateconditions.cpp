#include "climateconditions.h"

#include "common.h"

using namespace VD6::Common;

ClimateConditions::ClimateConditions()
{
    _solarFactor = new SolarFactor();
    _uValue = new UValue();

    _baySolarFactor = new BaySolarFactor();
    _maximalTemperaturesSealingJoint = new MaximalTemperaturesSealingJoint();
    _thermalBreakage = new ThermalBreakage();
    _glazingSolarFactor = new GlazingSolarFactor();
}

ClimateConditions::SolarFactor *ClimateConditions::solarFactor() const
{
    return _solarFactor;
}

void ClimateConditions::setSolarFactor(SolarFactor *solarFactor)
{
    _solarFactor = solarFactor;
}

ClimateConditions::UValue *ClimateConditions::uValue() const
{
    return _uValue;
}

void ClimateConditions::setUValue(UValue *uValue)
{
    _uValue = uValue;
}

ClimateConditions::BaySolarFactor *ClimateConditions::getBaySolarFactor() const
{
    return _baySolarFactor;
}

void ClimateConditions::setBaySolarFactor(BaySolarFactor *baySolarFactor)
{
    _baySolarFactor = baySolarFactor;
}

ClimateConditions::MaximalTemperaturesSealingJoint *ClimateConditions::getMaximalTemperaturesSealingJoint() const
{
    return _maximalTemperaturesSealingJoint;
}

void ClimateConditions::setMaximalTemperaturesSealingJoint(MaximalTemperaturesSealingJoint *maximalTemperaturesSealingJoint)
{
    _maximalTemperaturesSealingJoint = maximalTemperaturesSealingJoint;
}

ClimateConditions::ThermalBreakage *ClimateConditions::getThermalBreakage() const
{
    return _thermalBreakage;
}

void ClimateConditions::setThermalBreakage(ThermalBreakage *thermalBreakage)
{
    _thermalBreakage = thermalBreakage;
}

ClimateConditions::GlazingSolarFactor *ClimateConditions::getGlazingSolarFactor() const
{
    return _glazingSolarFactor;
}

void ClimateConditions::setGlazingSolarFactor(GlazingSolarFactor *climateSolarFactor)
{
    _glazingSolarFactor = climateSolarFactor;
}

double ClimateConditions::BaySolarFactor::Summer::getFi() const
{
    return _fi;
}

void ClimateConditions::BaySolarFactor::Summer::setFi(double fi)
{
    _fi = fi;
}

double ClimateConditions::BaySolarFactor::Summer::getHe() const
{
    return _he;
}

void ClimateConditions::BaySolarFactor::Summer::setHe(double he)
{
    _he = he;
}

double ClimateConditions::BaySolarFactor::Summer::getHi() const
{
    return _hi;
}

void ClimateConditions::BaySolarFactor::Summer::setHi(double hi)
{
    _hi = hi;
}

double ClimateConditions::BaySolarFactor::Summer::getTe() const
{
    return _te;
}

void ClimateConditions::BaySolarFactor::Summer::setTe(double te)
{
    _te = te;
}

double ClimateConditions::BaySolarFactor::Summer::getTi() const
{
    return _ti;
}

void ClimateConditions::BaySolarFactor::Summer::setTi(double ti)
{
    _ti = ti;
}

double ClimateConditions::BaySolarFactor::Winter::getFi() const
{
    return _fi;
}

void ClimateConditions::BaySolarFactor::Winter::setFi(double fi)
{
    _fi = fi;
}

double ClimateConditions::BaySolarFactor::Winter::getHe() const
{
    return _he;
}

void ClimateConditions::BaySolarFactor::Winter::setHe(double he)
{
    _he = he;
}

double ClimateConditions::BaySolarFactor::Winter::getHi() const
{
    return _hi;
}

void ClimateConditions::BaySolarFactor::Winter::setHi(double hi)
{
    _hi = hi;
}

double ClimateConditions::BaySolarFactor::Winter::getTe() const
{
    return _te;
}

void ClimateConditions::BaySolarFactor::Winter::setTe(double te)
{
    _te = te;
}

double ClimateConditions::BaySolarFactor::Winter::getTi() const
{
    return _ti;
}

void ClimateConditions::BaySolarFactor::Winter::setTi(double ti)
{
    _ti = ti;
}

bool ClimateConditions::BaySolarFactor::getGlazingBareInterior() const
{
    return _glazingBareInterior;
}

void ClimateConditions::BaySolarFactor::setGlazingBareInterior(bool glazingBareInterior)
{
    _glazingBareInterior = glazingBareInterior;
}

ClimateConditions::BaySolarFactor::Winter *ClimateConditions::BaySolarFactor::getWinter() const
{
    return _winter;
}

void ClimateConditions::BaySolarFactor::setWinter(Winter *winter)
{
    _winter = winter;
}

double ClimateConditions::BaySolarFactor::getBayUfFrame() const
{
    return _bayUfFrame;
}

void ClimateConditions::BaySolarFactor::setBayUfFrame(double bayUfFrame)
{
    _bayUfFrame = bayUfFrame;
}

double ClimateConditions::BaySolarFactor::getBayAbsFrame() const
{
    return _bayAbsFrame;
}

void ClimateConditions::BaySolarFactor::setBayAbsFrame(double bayAbsFrame)
{
    _bayAbsFrame = bayAbsFrame;
}

double ClimateConditions::BaySolarFactor::getSigma() const
{
    return _sigma;
}

void ClimateConditions::BaySolarFactor::setSigma(double sigma)
{
    _sigma = sigma;
}

ClimateConditions::BaySolarFactor::Summer *ClimateConditions::BaySolarFactor::getSummer() const
{
    return _summer;
}

void ClimateConditions::BaySolarFactor::setSummer(Summer *summer)
{
    _summer = summer;
}

double ClimateConditions::UValue::fi() const
{
    return _fi;
}

void ClimateConditions::UValue::setFi(double fi)
{
    _fi = fi;
}

double ClimateConditions::UValue::he() const
{
    return _he;
}

void ClimateConditions::UValue::setHe(double he)
{
    _he = he;
}

double ClimateConditions::UValue::hi() const
{
    return _hi;
}

void ClimateConditions::UValue::setHi(double hi)
{
    _hi = hi;
}

double ClimateConditions::UValue::te() const
{
    return _te;
}

void ClimateConditions::UValue::setTe(double te)
{
    _te = te;
}

double ClimateConditions::UValue::ti() const
{
    return _ti;
}

void ClimateConditions::UValue::setTi(double ti)
{
    _ti = ti;
}

ClimateConditions::Climate::Climate()
{
    _fi = 9999;
    _he = 9999;
    _hi = 9999;
    _te = 9999;
    _ti = 9999;

    _teMin = 9999;
    _faflu = 9999;
}

ClimateConditions::Climate::Climate(ClimateConditions::Climate *clone)
{
    this->_fi = clone->getFi();
    this->_he = clone->getHe();
    this->_hi = clone->getHi();
    this->_te = clone->getTe();
    this->_ti = clone->getTi();
    this->_teMin = clone->getTeMin();
    this->_faflu = clone->getFaflu();
}

ClimateConditions::Climate::Climate(double fi, double he, double hi, double te, double ti)
{
    this->_fi = fi;
    this->_he = he;
    this->_hi = hi;
    this->_te = te;
    this->_ti = ti;
}

double ClimateConditions::Climate::getFi() const
{
    return _fi;
}

void ClimateConditions::Climate::setFi(double fi)
{
    _fi = fi;
}

double ClimateConditions::Climate::getHe() const
{
    return _he;
}

void ClimateConditions::Climate::setHe(double he)
{
    _he = he;
}

double ClimateConditions::Climate::getHi() const
{
    return _hi;
}

void ClimateConditions::Climate::setHi(double hi)
{
    _hi = hi;
}

double ClimateConditions::Climate::getTe() const
{
    return _te;
}

void ClimateConditions::Climate::setTe(double te)
{
    _te = te;
}

double ClimateConditions::Climate::getTi() const
{
    return _ti;
}

void ClimateConditions::Climate::setTi(double ti)
{
    _ti = ti;
}

double ClimateConditions::Climate::getTeMin() const
{
    return _teMin;
}

void ClimateConditions::Climate::setTeMin(double teMin)
{
    _teMin = teMin;
}

double ClimateConditions::Climate::getFaflu() const
{
    return _faflu;
}

void ClimateConditions::Climate::setFaflu(double faflu)
{
    _faflu = faflu;
}

bool ClimateConditions::Climate::equal(ClimateConditions::Climate *another)
{
    if (!another) {
        return false;
    }

    if (!this) {
        return false;
    }

    if (!equalDouble(this->_fi, another->getFi())) {
        return false;
    }

    if (!equalDouble(this->_he, another->getHe())) {
        return false;
    }

    if (!equalDouble(this->_hi, another->getHi())) {
        return false;
    }

    if (!equalDouble(this->_te, another->getTe())) {
        return false;
    }

    if (!equalDouble(this->_ti, another->getTi())) {
        return false;
    }

    if (!equalDouble(this->_teMin, another->getTeMin())) {
        return false;
    }

    if (!equalDouble(this->_faflu, another->getFaflu())) {
        return false;
    }

    return true;
}

ClimateConditions::MaximalTemperaturesSealingJoint::MaximalTemperaturesSealingJoint()
{
}

map<string, ClimateConditions::Climate *> ClimateConditions::MaximalTemperaturesSealingJoint::getMaximalTemperaturesSealingJoint() const
{
    return _maximalTemperaturesSealingJoint;
}

void ClimateConditions::MaximalTemperaturesSealingJoint::setMaximalTemperaturesSealingJoint(map<string, Climate *> value)
{
    _maximalTemperaturesSealingJoint = value;
}

map<string, ClimateConditions::Climate *> ClimateConditions::ThermalBreakage::getClimateConditions() const
{
    return climateConditions;
}

void ClimateConditions::ThermalBreakage::setClimateConditions(const map<string, Climate *> &value)
{
    climateConditions = value;
}

ClimateConditions::Climate ClimateConditions::GlazingSolarFactor::getGlazingSolarFactor() const
{
    return _climateConditions;
}

void ClimateConditions::GlazingSolarFactor::setGlazingSolarFactor(const Climate &glazingSolarFactor)
{
    _climateConditions = glazingSolarFactor;
}
