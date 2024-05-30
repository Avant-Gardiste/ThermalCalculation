#include "glazingdtu39.h"

GlazingDTU39::GlazingDTU39()
{
    _type = 0;
    _numberLayer = 1;
    _natureType = 0;

    _gasThickness = 15;
}

GlazingDTU39::~GlazingDTU39()
{
}
int GlazingDTU39::type() const
{
    return _type;
}

void GlazingDTU39::setType(const int &type)
{
    _type = type;
}

int GlazingDTU39::numberLayer() const
{
    return _numberLayer;
}

void GlazingDTU39::setNumberLayer(int numberLayer)
{
    _numberLayer = numberLayer;
}

double GlazingDTU39::gasThickness() const
{
    return _gasThickness;
}

void GlazingDTU39::setGasThickness(double gasThickness)
{
    _gasThickness = gasThickness;
}

int GlazingDTU39::natureType() const
{
    return _natureType;
}

void GlazingDTU39::setNatureType(int natureType)
{
    _natureType = natureType;
}
