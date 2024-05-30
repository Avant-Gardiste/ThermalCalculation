#include "baysolarfactorclimaticconditions.h"

#include "thermal.h"
#include "projectcase.h"

BaySolarFactorClimaticConditions::BaySolarFactorClimaticConditions(BaseClimaticCondition *parent) :
    BaseClimaticCondition(parent)
{
}

void BaySolarFactorClimaticConditions::specificClimaticCondition()
{
    ThermalObject *objectSummer = ProjectCase::currentProject()->thermal()->baySolarData(0);

    if (objectSummer) {
        Climatic *summer = new Climatic();
        summer->setFlux(objectSummer->flux().toDouble());
        summer->setHe(objectSummer->he().toDouble());
        summer->setHi(objectSummer->hi().toDouble());
        summer->setTeMax(objectSummer->teMax().toDouble());
        summer->setTi(objectSummer->ti().toDouble());

        _climatic["summer"] = summer;
    }

    ThermalObject *objectWinter = ProjectCase::currentProject()->thermal()->baySolarData(1);

    if (objectWinter) {
        Climatic *winter = new Climatic();
        winter->setFlux(objectWinter->flux().toDouble());
        winter->setHe(objectWinter->he().toDouble());
        winter->setHi(objectWinter->hi().toDouble());
        winter->setTeMax(objectWinter->teMax().toDouble());
        winter->setTi(objectWinter->ti().toDouble());

        _climatic["winter"] = winter;
    }
}

void BaySolarFactorClimaticConditions::normalClimaticCondition()
{
    Climatic *summer = new Climatic();
    summer->setFlux(500);
    summer->setHe(13.5);
    summer->setHi(8);
    summer->setTeMax(25);
    summer->setTi(25);

    Climatic *winter = new Climatic();
    winter->setFlux(300);
    winter->setHe(25);
    winter->setHi(7.7);
    winter->setTeMax(5);
    winter->setTi(20);

    _climatic["summer"] = summer;
    _climatic["winter"] = winter;
}

std::map<string, ClimateConditions::Climate *> BaySolarFactorClimaticConditions::getClimaticConditionCore()
{
    map<string, ClimateConditions::Climate*> clone;

    for (auto it = this->_climatic.begin(); it != this->_climatic.end(); it++) {
        string key = it.key().toStdString();
        ClimateConditions::Climate *value = (*it)->toCoreObject();
        clone[key] = value;
    }
    return clone;
}

QMap<QString, Climatic *> BaySolarFactorClimaticConditions::getClimatic() const
{
    return _climatic;
}

void BaySolarFactorClimaticConditions::setClimatic(const QMap<QString, Climatic *> &climatic)
{
    _climatic = climatic;
}
