#include "pvbvd.h"

using namespace VD6::Common;

PVBVD::PVBVD()
{
}

PVBVD::~PVBVD()
{
}

unsigned int PVBVD::getId() const
{
    return id;
}

void PVBVD::setId(unsigned int value)
{
    id = value;
}

string PVBVD::getName() const
{
    return name;
}

void PVBVD::setName(const string &value)
{
    name = value;
}

string PVBVD::getRange() const
{
    return range;
}

void PVBVD::setRange(const string &value)
{
    range = value;
}

double PVBVD::getThicknessTotal() const
{
    return thicknessTotal;
}

void PVBVD::setThicknessTotal(double value)
{
    thicknessTotal = value;
}

double PVBVD::getThickness1() const
{
    return thickness1;
}

void PVBVD::setThickness1(double value)
{
    thickness1 = value;
}

double PVBVD::getThickness2() const
{
    return thickness2;
}

void PVBVD::setThickness2(double value)
{
    thickness2 = value;
}

double PVBVD::getThickness3() const
{
    return thickness3;
}

void PVBVD::setThickness3(double value)
{
    thickness3 = value;
}

double PVBVD::getThickness4() const
{
    return thickness4;
}

void PVBVD::setThickness4(double value)
{
    thickness4 = value;
}

double PVBVD::getThickness5() const
{
    return thickness5;
}

void PVBVD::setThickness5(double value)
{
    thickness5 = value;
}

double PVBVD::getTl() const
{
    return tl;
}

void PVBVD::setTl(double value)
{
    tl = value;
}

double PVBVD::getRl1() const
{
    return rl1;
}

void PVBVD::setRl1(double value)
{
    rl1 = value;
}

double PVBVD::getRl2() const
{
    return rl2;
}

void PVBVD::setRl2(double value)
{
    rl2 = value;
}

double PVBVD::getTe() const
{
    return te;
}

void PVBVD::setTe(double value)
{
    te = value;
}

double PVBVD::getRe1() const
{
    return re1;
}

void PVBVD::setRe1(double value)
{
    re1 = value;
}

double PVBVD::getEmn1() const
{
    return emn1;
}

void PVBVD::setEmn1(double value)
{
    emn1 = value;
}

double PVBVD::getRe2() const
{
    return re2;
}

void PVBVD::setRe2(double value)
{
    re2 = value;
}

double PVBVD::getEmn2() const
{
    return emn2;
}

void PVBVD::setEmn2(double value)
{
    emn2 = value;
}

int PVBVD::getStatus() const
{
    return status;
}

void PVBVD::setStatus(int value)
{
    status = value;
}

string PVBVD::getMaterial() const
{
    return material;
}

void PVBVD::setMaterial(const string &value)
{
    material = value;
}

string PVBVD::getManufacturer() const
{
    return manufacturer;
}

void PVBVD::setManufacturer(const string &value)
{
    manufacturer = value;
}

std::vector<Spectral *> PVBVD::getSpectral() const
{
    return spectral;
}

void PVBVD::setSpectral(const std::vector<Spectral *> &value)
{
    spectral = value;
}
