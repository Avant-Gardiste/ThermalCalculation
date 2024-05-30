#include "spectral.h"

#include "common.h"

using namespace VD6::Common;

Spectral::Spectral()
{
     _id = 0;
     _lamda = 0;
     _te = 0;
     _re1 = 0;
     _re2 = 0;
}

Spectral::Spectral(Spectral *clone)
{
    this->_id = clone->getId();
    this->_lamda = clone->getLamda();
    this->_te = clone->getTe();
    this->_re1 = clone->getRe1();
    this->_re2 = clone->getRe2();
}

Spectral::~Spectral()
{
}

Spectral *Spectral::operator=(Spectral *clone)
{
    return new Spectral(clone);
}

int Spectral::getId() const
{
    return _id;
}

void Spectral::setId(int value)
{
    _id = value;
}

int Spectral::getLamda() const
{
    return _lamda;
}

void Spectral::setLamda(int value)
{
    _lamda = value;
}

double Spectral::getTe() const
{
    return _te;
}

void Spectral::setTe(double value)
{
    _te = value;
}

double Spectral::getRe1() const
{
    return _re1;
}

void Spectral::setRe1(double value)
{
    _re1 = value;
}

double Spectral::getRe2() const
{
    return _re2;
}

void Spectral::setRe2(double value)
{
    _re2 = value;
}

bool Spectral::equal(Spectral *another)
{
    if (!another) {
        return false;
    }

    if(this->_id != another->getId()) {
        return false;
    }

    if(this->_lamda != another->getLamda()) {
        return false;
    }

    if(!equalDouble(this->_te, another->getTe())) {
        return false;
    }

    if(!equalDouble(this->_re1, another->getRe1())) {
        return false;
    }

    if(!equalDouble(this->_re2, another->getRe2())) {
        return false;
    }

    return true;
}
