#include "glazingxp50.h"

GlazingXP50::GlazingXP50(DefineGlass *parent) :
    DefineGlass(parent)
{
}

GlazingXP50::~GlazingXP50()
{
}

bool GlazingXP50::gasGapsVentilationExistence()
{
    vector<GasGap *> gasses = this->getGasGaps();

    for(auto it = gasses.begin();it != gasses.end(); it++) {
        if ((*it)->getType() == 2) {
            return true;
        }
    }

    return false;
}

double GlazingXP50::glazingSurface() const
{
    return _glazingSurface;
}

void GlazingXP50::setGlazingSurface(double glazingSurface)
{
    _glazingSurface = glazingSurface;
}

double GlazingXP50::totalPerimetersLg() const
{
    return _totalPerimetersLg;
}

void GlazingXP50::setTotalPerimetersLg(double totalPerimetersLg)
{
    _totalPerimetersLg = totalPerimetersLg;
}

double GlazingXP50::coefUgAverage() const
{
    return _coefUgAverage;
}

void GlazingXP50::setCoefUgAverage(double coefUgAverage)
{
    _coefUgAverage = coefUgAverage;
}
