#include "blindvd.h"

#include "common.h"

using namespace VD6::Common;

BlindVD::BlindVD()
{
    _type = "";
    _name = "";
    _range = "";

    _typeIndex = 1;

    _tl = 0;
    _rl1 = 0;
    _rl2 = 0;

    _te1 = 0;
    _re1 = 0;
    _emn1 =0;

    _te2 = 0;
    _re2 = 0;
    _emn2 =0;

    _thickness = 0;
    _density = 0;
    _opennessFactor = 0;

    _hexColor = "";
    _fireRating = "";

    _status = 0;//0: intergrated, 1: intergrated and spectral, 2 :spectral

    _material = "";
    _manufacturer = "";
}

BlindVD::BlindVD(BlindVD *clone)
{
    this->_id = clone->getId();

    this->_type = clone->getType();
    this->_name = clone->getName();
    this->_range = clone->getRange();

    this->_typeIndex = clone->typeIndex();

    this->_tl = clone->getTl();
    this->_rl1 = clone->getRl1();
    this->_rl2 = clone->getRl2();

    this->_te1 = clone->getTe1();
    this->_re1 = clone->getRe1();
    this->_emn1 = clone->getEmn1();

    this->_te2 = clone->getTe2();
    this->_re2 = clone->getRe2();
    this->_emn2 = clone->getEmn2();

    this->_thickness = clone->getThickness();
    this->_density = clone->getDensity();

    this->_opennessFactor = clone->getOpennessFactor();
    this->_hexColor = clone->getHexColor();
    this->_fireRating = clone->getFireRating();

    this->_status = clone->getStatus();

    this->_material = clone->getMaterial();
    this->_manufacturer = clone->getManufacturer();

    int size = clone->spectralCount();
    this->_spectral.clear();

    for (int i = 0; i < size; i++) {
        this->_spectral.push_back(new Spectral(clone->spectral(i)));
    }
}

BlindVD::~BlindVD()
{
    for(std::vector<Spectral *>::iterator it = _spectral.begin(); it != _spectral.end(); it++) {
        delete (*it);
    }
}
unsigned int BlindVD::getId() const
{
    return _id;
}

void BlindVD::setId(unsigned int id)
{
    _id = id;
}

string BlindVD::getName() const
{
    return _name;
}

void BlindVD::setName(const string &name)
{
    _name = name;
}

string BlindVD::getRange() const
{
    return _range;
}

void BlindVD::setRange(const string &range)
{
    _range = range;
}

double BlindVD::getRe1() const
{
    return _re1;
}

void BlindVD::setRe1(double re1)
{
    _re1 = re1;
}

double BlindVD::getEmn1() const
{
    return _emn1;
}

void BlindVD::setEmn1(double emn1)
{
    _emn1 = emn1;
}

double BlindVD::getRe2() const
{
    return _re2;
}

void BlindVD::setRe2(double re2)
{
    _re2 = re2;
}

double BlindVD::getEmn2() const
{
    return _emn2;
}

void BlindVD::setEmn2(double emn2)
{
    _emn2 = emn2;
}

double BlindVD::getThickness() const
{
    return _thickness;
}

void BlindVD::setThickness(double thickness)
{
    _thickness = thickness;
}

double BlindVD::getDensity() const
{
    return _density;
}

void BlindVD::setDensity(double density)
{
    _density = density;
}

double BlindVD::getOpennessFactor() const
{
    return _opennessFactor;
}

void BlindVD::setOpennessFactor(double opennessFactor)
{
    _opennessFactor = opennessFactor;
}

string BlindVD::getHexColor() const
{
    return _hexColor;
}

void BlindVD::setHexColor(const string &hexColor)
{
    _hexColor = hexColor;
}

string BlindVD::getFireRating() const
{
    return _fireRating;
}

void BlindVD::setFireRating(const string &fireRating)
{
    _fireRating = fireRating;
}

int BlindVD::getStatus() const
{
    return _status;
}

void BlindVD::setStatus(int status)
{
    _status = status;
}

string BlindVD::getMaterial() const
{
    return _material;
}

void BlindVD::setMaterial(const string &material)
{
    _material = material;
}

string BlindVD::getManufacturer() const
{
    return _manufacturer;
}

void BlindVD::setManufacturer(const string &manufacturer)
{
    _manufacturer = manufacturer;
}

std::vector<Spectral*> BlindVD::getSpectral() const
{
    return _spectral;
}

void BlindVD::setSpectral(const std::vector<Spectral *> &spectral)
{
    _spectral = spectral;
}

int BlindVD::spectralCount()
{
    return _spectral.size();
}

Spectral *BlindVD::spectral(int index)
{
    if (index < _spectral.size()) {
        return _spectral[index];
    }

    return NULL;
}

string BlindVD::getType() const
{
    return _type;
}

void BlindVD::setType(const string &type)
{
    _type = type;
}

int BlindVD::typeIndex() const
{
    return _typeIndex;
}

void BlindVD::setTypeIndex(int typeIndex)
{
    _typeIndex = typeIndex;
}

bool BlindVD::equal(BlindVD *another)
{
    if (!another) {
        return false;
    }

    if (this->_id != another->getId()) {
        return false;
    }

    if (this->_typeIndex != another->typeIndex()) {
        return false;
    }

    if (!equalDouble(this->_thickness, another->getThickness())) {
        return false;
    }

    if (!equalDouble(this->_tl, another->getTl())) {
        return false;
    }

    if (!equalDouble(this->_rl1, another->getRl1())) {
        return false;
    }

    if (!equalDouble(this->_rl2, another->getRl2())) {
        return false;
    }

    if (!equalDouble(this->_te1, another->getTe1())) {
        return false;
    }

    if (!equalDouble(this->_re1, another->getRe1())) {
        return false;
    }

    if (!equalDouble(this->_emn1, another->getEmn1())) {
        return false;
    }

    if (!equalDouble(this->_te2, another->getTe2())) {
        return false;
    }

    if (!equalDouble(this->_re2, another->getRe2())) {
        return false;
    }

    if (!equalDouble(this->_emn2, another->getEmn2())) {
        return false;
    }

    if (!equalDouble(this->_density, another->getDensity())) {
        return false;
    }

    if (!equalDouble(this->_opennessFactor, another->getOpennessFactor())) {
        return false;
    }

    if (this->_status != another->getStatus()) {
        return false;
    }

    if (this->_material != another->getMaterial()) {
        return false;
    }

    if (this->spectralCount() != another->spectralCount()) {
        return false;
    } else {
        int size = another->spectralCount();

        for (int i = 0; i < size; i++) {
            if (!this->spectral(i)->equal(another->spectral(i))) {
                return false;
            }
        }
    }

    return true;
}

double BlindVD::getTl() const
{
    return _tl;
}

void BlindVD::setTl(double tl)
{
    _tl = tl;
}

double BlindVD::getRl1() const
{
    return _rl1;
}

void BlindVD::setRl1(double rl1)
{
    _rl1 = rl1;
}

double BlindVD::getRl2() const
{
    return _rl2;
}

void BlindVD::setRl2(double rl2)
{
    _rl2 = rl2;
}

double BlindVD::getTe1() const
{
    return _te1;
}

void BlindVD::setTe1(double te)
{
    _te1 = te;
}

double BlindVD::getTe2() const
{
    return _te2;
}

void BlindVD::setTe2(double te)
{
    _te2 = te;
}
