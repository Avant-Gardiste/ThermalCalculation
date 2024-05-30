#include "climatic.h"

Climatic::Climatic(QObject *parent) :
    QObject (parent)
{
    _flux = 99999;
    _he = 99999;
    _hi = 99999;

    _teMax = 99999;
    _ti = 99999;
    _teMin = 99999;

    _faFlux = 99999;
}

Climatic::Climatic(Climatic *clone)
{
    this->_flux = clone->flux();
    this->_he = clone->he();
    this->_hi = clone->hi();

    this->_teMax = clone->teMax();
    this->_ti = clone->ti();
    this->_teMin = clone->teMin();

    this->_faFlux = clone->faFlux();
}

ClimateConditions::Climate *Climatic::toCoreObject()
{
    ClimateConditions::Climate *clone = new ClimateConditions::Climate();

    clone->setFi(this->_flux);
    clone->setHe(this->_he);
    clone->setHi(this->_hi);

    clone->setTe(this->_teMax);
    clone->setTi(this->_ti);
    clone->setTeMin(this->_teMin);

    clone->setFaflu(this->_faFlux);

    return clone;
}

double Climatic::flux() const
{
    return _flux;
}

void Climatic::setFlux(double fi)
{
    if (fi != _flux) {
        _flux = fi;

        emit fluxChanged();
    }
}

double Climatic::he() const
{
    return _he;
}

void Climatic::setHe(double he)
{
    if (he != _he) {
        _he = he;

        emit heChanged();
    }
}

double Climatic::hi() const
{
    return _hi;
}

void Climatic::setHi(double hi)
{
    if (hi != _hi) {
        _hi = hi;

        emit hiChanged();
    }
}

double Climatic::teMax() const
{
    return _teMax;
}

void Climatic::setTeMax(double teMax)
{
    if (teMax != _teMax) {
        _teMax = teMax;

        emit teMaxChanged();
    }
}

double Climatic::ti() const
{
    return _ti;
}

void Climatic::setTi(double ti)
{
    if (ti != _ti) {
        _ti = ti;

        emit tiChanged();
    }
}

double Climatic::teMin() const
{
    return _teMin;
}

void Climatic::setTeMin(double teMin)
{
    if (teMin != _teMin) {
        _teMin = teMin;

        emit teMinChanged();
    }
}

double Climatic::faFlux() const
{
    return _faFlux;
}

void Climatic::setFaFlux(double faFlux)
{
    if (faFlux != _faFlux) {
        _faFlux = faFlux;

        emit faFluxChanged();
    }
}
