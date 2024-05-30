#include "result.h"

using namespace VD6::Common;

Result::Result()
{
    _thermalBreakageSpecific = new Object::ThermalBreakageSpecificResult();
}

vector<double> Result::getSolarGlass() const
{
    return _solarGlass;
}

void Result::setSolarGlass(const vector<double> &solarGlass)
{
    _solarGlass = solarGlass;
}

vector<vector<double> > Result::getSolarGlobal() const
{
    return _solarGlobal;
}

void Result::setSolarGlobal(const vector<vector<double> > &solarGlobal)
{
    _solarGlobal = solarGlobal;
}

vector<vector<double>> Result::getSolarAverage() const
{
    return _solarAverage;
}

void Result::setSolarAverage(const vector<vector<double> > &solarAverage)
{
    _solarAverage = solarAverage;
}

vector<double> Result::getLightGlass() const
{
    return _lightGlass;
}

void Result::setLightGlass(const vector<double> &lightGlass)
{
    _lightGlass = lightGlass;
}

vector<vector<double> > Result::getLightGlobal() const
{
    return _lightGlobal;
}

void Result::setLightGlobal(const vector<vector<double> > &lightGlobal)
{
    _lightGlobal = lightGlobal;
}

vector<vector<double> > Result::getLightAverage() const
{
    return _lightAverage;
}

void Result::setLightAverage(const vector<vector<double> > &lightAverage)
{
    _lightAverage = lightAverage;
}

std::map<string, Object::BaySolarFactorResult> Result::getBaySolarFactor() const
{
    return _baySolarFactor;
}

void Result::setBaySolarFactor(const std::map<string, Object::BaySolarFactorResult> &baySolarFactor)
{
    _baySolarFactor = baySolarFactor;
}

double Result::getHi673() const
{
    return _hi673;
}

void Result::setHi673(double hi673)
{
    _hi673 = hi673;
}

double Result::getTsi() const
{
    return _tsi;
}

void Result::setTsi(double tsi)
{
    _tsi = tsi;
}

double Result::getTse() const
{
    return _tse;
}

void Result::setTse(double tse)
{
    _tse = tse;
}

std::map<string, Object::SealingJointResult> Result::getResultSealingJoint() const
{
    return _sealingJoint;
}

void Result::setResultSealingJoint(const std::map<string, Object::SealingJointResult> &sealingJoint)
{
    _sealingJoint = sealingJoint;
}

map<string, Object::ThermalBreakageResult *> Result::getResultThermalBreakage() const
{
    return _thermalBreakage;
}

void Result::setResultThermalBreakage(const map<string, Object::ThermalBreakageResult *> &thermalBreakage)
{
    _thermalBreakage = thermalBreakage;
}

map<string, double> Result::getObstaclesUValue() const
{
    return _obstaclesUValue;
}

void Result::setObstaclesUValue(const map<string, double> &coefUValue)
{
    _obstaclesUValue = coefUValue;
}

std::map<string, Object::MaximalTemperaturesResult *> Result::getResultMaximalTemperatures() const
{
    return _maximalTemperatures;
}

void Result::setResultMaximalTemperatures(const std::map<string, Object::MaximalTemperaturesResult *> &maximalTemperatures)
{
    _maximalTemperatures = maximalTemperatures;
}

double Result::getSolarFactorGlass() const
{
    return _solarFactorGlass;
}

void Result::setSolarFactorGlass(double solarFactorGlass)
{
    _solarFactorGlass = solarFactorGlass;
}

double Result::getSolarFactorGlobal() const
{
    return _solarFactorGlobal;
}

void Result::setSolarFactorGlobal(double solarFactorGlobal)
{
    _solarFactorGlobal = solarFactorGlobal;
}

Object::SealingJointVECResult* Result::getSealingJointVEC() const
{
    return _sealingJointVEC;
}

void Result::setSealingJointVEC(Object::SealingJointVECResult* sealingJointVEC)
{
    _sealingJointVEC = sealingJointVEC;
}

std::map<string, Object::StressAndDeflectionResult *> Result::getStressAndDeflection() const
{
    return _stressAndDeflection;
}

void Result::setStressAndDeflection(const std::map<string, Object::StressAndDeflectionResult *> &stressAndDeflection)
{
    _stressAndDeflection = stressAndDeflection;
}

Object::ThermalBreakageSpecificResult *Result::getThermalBreakageSpecific() const
{
    return _thermalBreakageSpecific;
}

void Result::setThermalBreakageSpecific(Object::ThermalBreakageSpecificResult *thermalBreakageSpecific)
{
    _thermalBreakageSpecific = thermalBreakageSpecific;
}

Object::SlidingSashResult *Result::getSlidingSash() const
{
    return _slidingSash;
}

void Result::setSlidingSash(Object::SlidingSashResult *slidingSash)
{
    _slidingSash = slidingSash;
}

double Result::getCoefUGlass() const
{
    return _coefUGlass;
}

void Result::setCoefUGlass(double value)
{
    _coefUGlass = value;
}

double Result::getCoefUGlobal() const
{
    return _coefUGlobal;
}

void Result::setCoefUGlobal(double value)
{
    _coefUGlobal = value;
}
