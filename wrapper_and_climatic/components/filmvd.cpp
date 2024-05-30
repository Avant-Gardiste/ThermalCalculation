#include "filmvd.h"

using namespace VD6::Common;

FilmVD::FilmVD()
{
}

FilmVD::~FilmVD()
{
}

unsigned int FilmVD::getId() const
{
    return id;
}

void FilmVD::setId(unsigned int value)
{

    id = value;
}

string FilmVD::getName() const
{
    return name;
}

void FilmVD::setName(const string &value)
{
    name = value;
}

string FilmVD::getRange() const
{
    return range;
}

void FilmVD::setRange(const string &value)
{
    range = value;
}

double FilmVD::getThicknessTotal() const
{
    return thicknessTotal;
}

void FilmVD::setThicknessTotal(double value)
{
    thicknessTotal = value;
}

double FilmVD::getThickness1() const
{
    return thickness1;
}

void FilmVD::setThickness1(double value)
{
    thickness1 = value;
}

double FilmVD::getThickness2() const
{
    return thickness2;
}

void FilmVD::setThickness2(double value)
{
    thickness2 = value;
}

double FilmVD::getThickness3() const
{
    return thickness3;
}

void FilmVD::setThickness3(double value)
{
    thickness3 = value;
}

double FilmVD::getThickness4() const
{
    return thickness4;
}

void FilmVD::setThickness4(double value)
{
    thickness4 = value;
}

double FilmVD::getThickness5() const
{
    return thickness5;
}

void FilmVD::setThickness5(double value)
{
    thickness5 = value;
}

double FilmVD::getTl() const
{
    return tl;
}

void FilmVD::setTl(double value)
{
    tl = value;
}

double FilmVD::getRe1() const
{
    return re1;
}

void FilmVD::setRe1(double value)
{
    re1 = value;
}

double FilmVD::getRe2() const
{
    return re2;
}

void FilmVD::setRe2(double value)
{
    re2 = value;
}

double FilmVD::getTe() const
{
    return te;
}

void FilmVD::setTe(double value)
{
    te = value;
}

double FilmVD::getRl1() const
{
    return rl1;
}

void FilmVD::setRl1(double value)
{
    rl1 = value;
}

double FilmVD::getEmn1() const
{
    return emn1;
}

void FilmVD::setEmn1(double value)
{
    emn1 = value;
}

double FilmVD::getRl2() const
{
    return rl2;
}

void FilmVD::setRl2(double value)
{
    rl2 = value;
}

double FilmVD::getEmn2() const
{
    return emn2;
}

void FilmVD::setEmn2(double value)
{
    emn2 = value;
}

int FilmVD::getStatus() const
{
    return status;
}

void FilmVD::setStatus(int value)
{
    status = value;
}

string FilmVD::getMaterial() const
{
    return material;
}

void FilmVD::setMaterial(const string &value)
{
    material = value;
}

string FilmVD::getManufacturer() const
{
    return manufacturer;
}

std::vector<Spectral *> FilmVD::getSpectral() const
{
    return spectral;
}

void FilmVD::setSpectral(const std::vector<Spectral *> &value)
{
    spectral = value;
}

void FilmVD::setManufacturer(const string &value)
{
    manufacturer = value;
}
