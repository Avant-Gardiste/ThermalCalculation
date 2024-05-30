#include "glazinguvalueclimaticcondition.h"

#include "thermal.h"
#include "projectcase.h"

GlazingUValueClimaticCondition::GlazingUValueClimaticCondition(BaseClimaticCondition *parent) :
    BaseClimaticCondition(parent)
{
    _hi673 = 0;
}

void GlazingUValueClimaticCondition::specificClimaticCondition()
{
    ThermalObject *object = ProjectCase::currentProject()->thermal()->glazingUValueThermalData();

    if (object) {
        Climatic *tmpClimate = new Climatic();
        tmpClimate->setFlux(object->flux().toDouble());
        tmpClimate->setHe(object->he().toDouble());
        tmpClimate->setHi(object->hi().toDouble());
        tmpClimate->setTeMax(object->teMax().toDouble());
        tmpClimate->setTi(object->ti().toDouble());

        _climatic["GlazingUValue"] = tmpClimate;
    }
}

void GlazingUValueClimaticCondition::normalClimaticCondition()
{
    Climatic *tmpClimate = new Climatic();

    tmpClimate->setFlux(0);
    tmpClimate->setHe(25);
    tmpClimate->setTeMax(0);
    tmpClimate->setTi(20);

    if (ProjectCase::currentProject()->glassParameters()->inclination() >= 60) {
        tmpClimate->setHi(7.7);
    } else {
        tmpClimate->setHi(10);
    }

    _climatic["GlazingUValue"] = tmpClimate;
}

std::map<string, ClimateConditions::Climate *> GlazingUValueClimaticCondition::getClimaticConditionCore()
{
    map<string, ClimateConditions::Climate*> clone;

    for (auto it = this->_climatic.begin(); it != this->_climatic.end(); it++) {
        string key = it.key().toStdString();
        ClimateConditions::Climate *value = (*it)->toCoreObject();
        clone[key] = value;
    }
    return clone;
}

QMap<QString, Climatic *> GlazingUValueClimaticCondition::climatic() const
{
    return _climatic;
}

void GlazingUValueClimaticCondition::setClimatic(const QMap<QString, Climatic *> &climatic)
{
    _climatic = climatic;
}

double GlazingUValueClimaticCondition::hi673() const
{
    return _hi673;
}

void GlazingUValueClimaticCondition::setHi673(double hi673)
{
    _hi673 = hi673;
}
