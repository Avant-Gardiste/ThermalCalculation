#include "obstaclevd.h"

#include "common.h"

using namespace VD6::Common;

ObstacleVD::ObstacleVD()
{
    _id = 0;

    _name = "";
    _height = 0;
    _width  = 0;
    _distance = 0;

    //Peripheral
    _high = 0;
    _low = 0;
    _lateral = 0;

    _thermalResistance = 0;
    _color = "";

    _te = 0;
    _re1 = 0;
    _emn1 = 0;
    _re2 = 0;
    _emn2 = 0;

    _temperature = 0;
}

ObstacleVD::~ObstacleVD()
{
}

unsigned int ObstacleVD::id() const
{
    return _id;
}

void ObstacleVD::setId(unsigned int value)
{
    _id = value;
}

string ObstacleVD::name() const
{
    return _name;
}

void ObstacleVD::setName(const string &value)
{
    _name = value;
}

double ObstacleVD::height() const
{
    return _height;
}

void ObstacleVD::setHeight(double height)
{
    _height = height;
}

double ObstacleVD::width() const
{
    return _width;
}

void ObstacleVD::setWidth(double width)
{
    _width = width;
}

double ObstacleVD::distance() const
{
    return _distance;
}

void ObstacleVD::setDistance(double distance)
{
    _distance = distance;
}

double ObstacleVD::high() const
{
    return _high;
}

void ObstacleVD::setHigh(double high)
{
    _high = high;
}

double ObstacleVD::low() const
{
    return _low;
}

void ObstacleVD::setLow(double low)
{
    _low = low;
}

double ObstacleVD::lateral() const
{
    return _lateral;
}

void ObstacleVD::setLateral(double lateral)
{
    _lateral = lateral;
}

double ObstacleVD::thermalResistance() const
{
    return _thermalResistance;
}

void ObstacleVD::setThermalResistance(double thermalResistance)
{
    _thermalResistance = thermalResistance;
}

string ObstacleVD::color() const
{
    return _color;
}

void ObstacleVD::setColor(const string &color)
{
    _color = color;
}

double ObstacleVD::temperature() const
{
    return _temperature;
}

void ObstacleVD::setTemperature(double temperature)
{
    _temperature = temperature;
}

double ObstacleVD::te() const
{
    return _te;
}

void ObstacleVD::setTe(double te)
{
    _te = te;
}

double ObstacleVD::re1() const
{
    return _re1;
}

void ObstacleVD::setRe1(double re1)
{
    _re1 = re1;
}

double ObstacleVD::emn1() const
{
    return _emn1;
}

void ObstacleVD::setEmn1(double emn1)
{
    _emn1 = emn1;
}

double ObstacleVD::re2() const
{
    return _re2;
}

void ObstacleVD::setRe2(double re2)
{
    _re2 = re2;
}

double ObstacleVD::emn2() const
{
    return _emn2;
}

void ObstacleVD::setEmn2(double emn2)
{
    _emn2 = emn2;
}

bool ObstacleVD::equal(ObstacleVD *another)
{
    if (!another) {
        return false;
    }

    if (_id != another->id()) {
        return false;
    }

    if (!equalDouble(_height, another->height())) {
        return false;
    }

    if (!equalDouble(_width, another->width())) {
        return false;
    }

    if (!equalDouble(_distance, another->distance())) {
        return false;
    }

    if (!equalDouble(_high, another->high())) {
        return false;
    }

    if (!equalDouble(_low, another->low())) {
        return false;
    }

    if (!equalDouble(_lateral, another->lateral())) {
        return false;
    }

    if (!equalDouble(_thermalResistance, another->thermalResistance())) {
        return false;
    }

    if (!equalDouble(_te, another->te())) {
        return false;
    }

    if (!equalDouble(_re1, another->re1())) {
        return false;
    }

    if (!equalDouble(_emn1, another->emn1())) {
        return false;
    }

    if (!equalDouble(_re2, another->re2())) {
        return false;
    }

    if (!equalDouble(_emn2, another->emn2())) {
        return false;
    }

    if (!equalDouble(_temperature, another->temperature())) {
        return false;
    }

    return true;
}
