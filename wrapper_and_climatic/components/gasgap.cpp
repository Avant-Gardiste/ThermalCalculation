#include "gasgap.h"

#include "common.h"

using namespace VD6::Common;

GasGap::GasGap()
{
    _name = "";
    _type = 0; //0: Air, 1: Mixte, 2: Ventile
    _thickness = 0;

    _argon = 0;
    _krypton = 0;
    _xenon = 0;

    //air  = 0;
    _typeVentilation = -1; //Forced = 0, Natural= 1,Respiration =2

    _airFlow = 0;
    _airTemperature = 0;
    _airflowOutlet = false;

    _ventilationFrom = false;

    _high = 0;
    _low = 0;
    _lateral = 0;
}

GasGap::GasGap(GasGap *clone)
{
     this->_name = clone->getName();
     this->_type = clone->getType();

     this->_thickness = clone->getThickness();

     this->_argon = clone->getArgon();
     this->_krypton = clone->getKrypton();
     this->_xenon = clone->getXenon();

     this->_typeVentilation = clone->getTypeVentilation();

     this->_airFlow = clone->getAirFlow();
     this->_airTemperature = clone->getAirTemperature();

     this->_airflowOutlet = clone-> getAirflowOutlet();
     this->_ventilationFrom = clone->getVentilationFrom();

     this->_high = clone->getHigh();
     this->_low = clone->getLow();
     this->_lateral = clone->getLateral();
}

GasGap::~GasGap()
{
}

string GasGap::getName() const
{
    return _name;
}

void GasGap::setName(const string &value)
{
    _name = value;
}

int GasGap::getType() const
{
    return _type;
}

void GasGap::setType(int value)
{
    _type = value;
}

double GasGap::getThickness() const
{
    return _thickness;
}

void GasGap::setThickness(double value)
{
    _thickness = value;
}

double GasGap::getArgon() const
{
    return _argon;
}

void GasGap::setArgon(double value)
{
    _argon = value;
}

double GasGap::getKrypton() const
{
    return _krypton;
}

void GasGap::setKrypton(double value)
{
    _krypton = value;
}

double GasGap::getXenon() const
{
    return _xenon;
}

void GasGap::setXenon(double value)
{
    _xenon = value;
}

int GasGap::getTypeVentilation() const
{
    return _typeVentilation;
}

void GasGap::setTypeVentilation(int value)
{
    _typeVentilation = value;
}

double GasGap::getAirFlow() const
{
    return _airFlow;
}

void GasGap::setAirFlow(double value)
{
    _airFlow = value;
}

double GasGap::getAirTemperature() const
{
    return _airTemperature;
}

void GasGap::setAirTemperature(double value)
{
    _airTemperature = value;
}

double GasGap::getHigh() const
{
    return _high;
}

void GasGap::setHigh(double value)
{
    _high = value;
}

double GasGap::getLow() const
{
    return _low;
}

void GasGap::setLow(double value)
{
    _low = value;
}

double GasGap::getLateral() const
{
    return _lateral;
}

void GasGap::setLateral(double value)
{
    _lateral = value;
}
bool GasGap::getAirflowOutlet() const
{
    return _airflowOutlet;
}

void GasGap::setAirflowOutlet(bool airflowOutlet)
{
    _airflowOutlet = airflowOutlet;
}
bool GasGap::getVentilationFrom() const
{
    return _ventilationFrom;
}

void GasGap::setVentilationFrom(bool ventilationFrom)
{
    _ventilationFrom = ventilationFrom;
}

bool GasGap::equal(GasGap *another)
{
    if (!another) {
        return false;
    }

    if (this->_name != another->getName()) {
        return false;
    }

    if (this->_type != another->getType()) {
        return false;
    }

    if (!equalDouble(this->_thickness, another->getThickness())) {
        return false;
    }

    if (!equalDouble(this->_argon, another->getArgon())) {
        return false;
    }

    if (!equalDouble(this->_krypton, another->getKrypton())) {
        return false;
    }

    if (!equalDouble(this->_xenon, another->getXenon())) {
        return false;
    }

    if (this->_typeVentilation != another->getTypeVentilation()) {
        return false;
    }

    if (!equalDouble(this->_airFlow, another->getAirFlow())) {
        return false;
    }

    if (!equalDouble(this->_airTemperature, another->getAirTemperature())) {
        return false;
    }

    if (this->_airflowOutlet != another-> getAirflowOutlet()) {
        return false;
    }

    if (this->_ventilationFrom != another->getVentilationFrom()) {
        return false;
    }

    if (!equalDouble(this->_high, another->getHigh())) {
        return false;
    }

    if (!equalDouble(this->_low, another->getLow())) {
        return false;
    }

    if (!equalDouble(this->_lateral, another->getLateral())) {
        return false;
    }

    return true;
}
