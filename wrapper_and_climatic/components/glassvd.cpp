#include "glassvd.h"

#include "common.h"

using namespace VD6::Common;

GlassVD::GlassVD()
{
    _id = 0;

    _name = "";
    _range = "";

    _thicknessTotal = 0;
    _thickness1 = 0;
    _thickness2 = 0;
    _thickness3 = 0;
    _thickness4 = 0;
    _thickness5 = 0;

    _tl = 0;
    _rl1 = 0;
    _rl2 = 0;

    _te = 0;
    _re1 = 0;
    _emn1 = 0;
    _re2 = 0;
    _emn2 = 0;

    _positionSolarControlLayer = 0;
    _positionSelfCleaningLayer = 0;

    _status = 0;
    _material = "";
    _manufacturer = "";
    _research = "";
}

GlassVD::GlassVD(GlassVD *clone)
{
    this->_id = clone->getId();

    this->_name = clone->getName();
    this->_range = clone->getRange();

    this->_thicknessTotal = clone->getThicknessTotal();
    this->_thickness1 = clone->getThickness1();
    this->_thickness2 = clone->getThickness2();
    this->_thickness3 = clone->getThickness3();
    this->_thickness4 = clone->getThickness4();
    this->_thickness5 = clone->getThickness5();

    this->_tl = clone->getTl();
    this->_rl1 = clone->getRl1();
    this->_rl2 = clone->getRl2();

    this->_te = clone->getTe();
    this->_re1 = clone->getRe1();
    this->_emn1 = clone->getEmn1();
    this->_re2 = clone->getRe2();
    this->_emn2 = clone->getEmn2();

    this->_positionSolarControlLayer = clone->getPositionSolarControlLayer();
    this->_positionSelfCleaningLayer = clone->getPositionSelfCleaningLayer();

    this->_status = clone->getStatus();
    this->_material = clone->getMaterial();
    this->_manufacturer = clone->getManufacturer();
    this->_research = clone->getResearch();

    int size = clone->spectralCount();
    this->_spectral.clear();

    for (int i = 0; i < size; i++) {
        this->_spectral.push_back(new Spectral(clone->spectral(i)));
    }
}

GlassVD::~GlassVD()
{
    if (this->_spectral.size() != 0) {
        for(std::vector<Spectral*>::iterator it = _spectral.begin();it != _spectral.end(); it++) {
            delete (*it);
        }
    }
}

unsigned int GlassVD::getId() const
{
    return _id;
}

void GlassVD::setId(unsigned int value)
{
    _id = value;
}

double GlassVD::getTe() const
{
    return _te;
}

void GlassVD::setTe(double value)
{
    _te = value;
}

double GlassVD::getRe1() const
{
    return _re1;
}

void GlassVD::setRe1(double value)
{
    _re1 = value;
}

double GlassVD::getRe2() const
{
    return _re2;
}

void GlassVD::setRe2(double value)
{
    _re2 = value;
}

double GlassVD::getEmn1() const
{
    return _emn1;
}

void GlassVD::setEmn1(double value)
{
    _emn1 = value;
}

double GlassVD::getEmn2() const
{
    return _emn2;
}

void GlassVD::setEmn2(double value)
{
    _emn2 = value;
}

string GlassVD::getName() const
{
    return _name;
}

void GlassVD::setName(const string &value)
{
    _name = value;
}

string GlassVD::getRange() const
{
    return _range;
}

void GlassVD::setRange(const string &value)
{
    _range = value;
}

double GlassVD::getThicknessTotal() const
{
    return _thicknessTotal;
}

void GlassVD::setThicknessTotal(double value)
{
    _thicknessTotal = value;
}

double GlassVD::getThickness1() const
{
    return _thickness1;
}

void GlassVD::setThickness1(double value)
{
    _thickness1 = value;
}

double GlassVD::getThickness2() const
{
    return _thickness2;
}

void GlassVD::setThickness2(double value)
{
    _thickness2 = value;
}

double GlassVD::getThickness3() const
{
    return _thickness3;
}

void GlassVD::setThickness3(double value)
{
    _thickness3 = value;
}

double GlassVD::getThickness4() const
{
    return _thickness4;
}

void GlassVD::setThickness4(double value)
{
    _thickness4 = value;
}

double GlassVD::getThickness5() const
{
    return _thickness5;
}

void GlassVD::setThickness5(double value)
{
    _thickness5 = value;
}

double GlassVD::getTl() const
{
    return _tl;
}

void GlassVD::setTl(double value)
{
    _tl = value;
}

double GlassVD::getRl1() const
{
    return _rl1;
}

void GlassVD::setRl1(double value)
{
    _rl1 = value;
}

double GlassVD::getRl2() const
{
    return _rl2;
}

void GlassVD::setRl2(double value)
{
    _rl2 = value;
}

int GlassVD::getPositionSolarControlLayer() const
{
    return _positionSolarControlLayer;
}

void GlassVD::setPositionSolarControlLayer(int value)
{
    _positionSolarControlLayer = value;
}

int GlassVD::getPositionSelfCleaningLayer() const
{
    return _positionSelfCleaningLayer;
}

void GlassVD::setPositionSelfCleaningLayer(int value)
{
    _positionSelfCleaningLayer = value;
}

int GlassVD::getStatus() const
{
    return _status;
}

void GlassVD::setStatus(int value)
{
    _status = value;
}

std::vector<Spectral *> GlassVD::getSpectral() const
{
    return _spectral;
}

void GlassVD::setSpectral(const std::vector<Spectral *> &spectral)
{
    _spectral = spectral;
}

int GlassVD::spectralCount()
{
    return _spectral.size();
}

Spectral *GlassVD::spectral(int index)
{
    if (index < _spectral.size()) {
        return _spectral[index];
    }

    return NULL;
}

string GlassVD::getManufacturer() const
{
    return _manufacturer;
}

void GlassVD::setManufacturer(const string &manufacturer)
{
    _manufacturer = manufacturer;
}

string GlassVD::getMaterial() const
{
    return _material;
}

void GlassVD::setMaterial(const string &material)
{
    _material = material;
}

string GlassVD::getResearch() const
{
    return _research;
}

void GlassVD::setResearch(const string &research)
{
    _research = research;
}

bool GlassVD::equal(GlassVD *another)
{
    if (!another) {
        return false;
    }

    if (this->_id != another->getId()) {
        return false;
    }

    if (!equalDouble(this->_thicknessTotal, another->getThicknessTotal())) {
        return false;
    }

    if (!equalDouble(this->_thickness1, another->getThickness1())) {
        return false;
    }

    if (!equalDouble(this->_thickness2, another->getThickness2())) {
        return false;
    }

    if (!equalDouble(this->_thickness3, another->getThickness3())) {
        return false;
    }

    if (!equalDouble(this->_thickness4, another->getThickness4())) {
        return false;
    }

    if (!equalDouble(this->_thickness5, another->getThickness5())) {
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

    if (!equalDouble(this->_te, another->getTe())) {
        return false;
    }

    if (!equalDouble(this->_re1, another->getRe1())) {
        return false;
    }

    if (!equalDouble(this->_emn1, another->getEmn1())) {
        return false;
    }

    if (!equalDouble(this->_re2, another->getRe2())) {
        return false;
    }

    if (!equalDouble(this->_emn2, another->getEmn2())) {
        return false;
    }

    if (this->_positionSolarControlLayer != another->getPositionSolarControlLayer()) {
        return false;
    }

    if (this->_positionSelfCleaningLayer != another->getPositionSelfCleaningLayer()) {
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
