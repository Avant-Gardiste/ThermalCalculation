#include "glazingsolarfactorclimaticcondition.h"

#include "thermal.h"
#include "projectcase.h"

GlazingSolarFactorClimaticCondition::GlazingSolarFactorClimaticCondition(BaseClimaticCondition *parent) :
    BaseClimaticCondition(parent)
{
}

void GlazingSolarFactorClimaticCondition::specificClimaticCondition()
{
    ThermalObject *object = ProjectCase::currentProject()->thermal()->glazingSolarThermalData();

    if (object) {
        Climatic *tmpClimate = new Climatic();
        tmpClimate->setFlux(object->flux().toDouble());
        tmpClimate->setHe(object->he().toDouble());
        tmpClimate->setHi(object->hi().toDouble());
        tmpClimate->setTeMax(object->teMax().toDouble());
        tmpClimate->setTi(object->ti().toDouble());

        _climatic["normal"] = tmpClimate;
        _climatic["summer"] = tmpClimate;
        _climatic["reference"] = tmpClimate;
    }
}

void GlazingSolarFactorClimaticCondition::normalClimaticCondition()
{
    Climatic *climatic = new Climatic();
    climatic->setFlux(750);
    climatic->setHe(23);
    climatic->setHi(7.7);
    climatic->setTeMax(35);
    climatic->setTi(25);

    Climatic *summer = new Climatic();
    summer->setFlux(500);
    summer->setHe(8);
    summer->setHi(2.5);
    summer->setTeMax(25);
    summer->setTi(25);

    Climatic *reference = new Climatic();
    reference->setFlux(300);
    reference->setHe(18);
    reference->setHi(3.6);
    reference->setTeMax(5);
    reference->setTi(20);

    _climatic["normal"] = climatic;
    _climatic["summer"] = summer;
    _climatic["reference"] = reference;
}

std::map<string, ClimateConditions::Climate *> GlazingSolarFactorClimaticCondition::getClimaticConditionCore()
{
    map<string, ClimateConditions::Climate*> clone;

    for (auto it = this->_climatic.begin(); it != this->_climatic.end(); it++) {
        string key = it.key().toStdString();
        ClimateConditions::Climate *value = (*it)->toCoreObject();
        clone[key] = value;
    }

    return clone;
}

QMap<QString, Climatic *> GlazingSolarFactorClimaticCondition::climatic() const
{
    return _climatic;
}

void GlazingSolarFactorClimaticCondition::setClimatic(const QMap<QString, Climatic *> &climatic)
{
    _climatic = climatic;
}
