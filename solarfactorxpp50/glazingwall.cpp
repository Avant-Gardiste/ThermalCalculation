#include "glazingwall.h"

GlazingWall::GlazingWall()
{
    _project = "";
    _nameGlazing = "";
    _description = "";
    _type = "";

    _enableMobileProtection = false;
    _withOpaquePart = false;
    _rollerExistence = false;

    _incline = 0;

    _height = 0;
    _width = 0;
    _surfaceGlazingAg = 0;
    _surfaceGlazingAf = 0;

    _surfaceOpaqueWallAp = 0;
    _surfaceRollingShutterAc = 0;
}

GlazingWall::~GlazingWall()
{
}

string GlazingWall::project() const
{
    return _project;
}

void GlazingWall::setProject(const string &project)
{
    _project = project;
}

string GlazingWall::nameGlazing() const
{
    return _nameGlazing;
}

void GlazingWall::setNameGlazing(const string &nameGlazing)
{
    _nameGlazing = nameGlazing;
}

string GlazingWall::description() const
{
    return _description;
}

void GlazingWall::setDescription(const string &description)
{
    _description = description;
}

string GlazingWall::type() const
{
    return _type;
}

void GlazingWall::setType(const string &type)
{
    _type = type;
}

bool GlazingWall::enableMobileProtection() const
{
    return _enableMobileProtection;
}

void GlazingWall::setEnableMobileProtection(bool enableMobileProtection)
{
    _enableMobileProtection = enableMobileProtection;
}

bool GlazingWall::withOpaquePart() const
{
    return _withOpaquePart;
}

void GlazingWall::setWithOpaquePart(bool withOpaquePart)
{
    _withOpaquePart = withOpaquePart;
}

bool GlazingWall::rollerExistence() const
{
    return _rollerExistence;
}

void GlazingWall::setRollerExistence(bool rollerExistence)
{
    _rollerExistence = rollerExistence;
}

double GlazingWall::incline() const
{
    return _incline;
}

void GlazingWall::setIncline(double incline)
{
    _incline = incline;
}

double GlazingWall::height() const
{
    return _height;
}

void GlazingWall::setHeight(double height)
{
    _height = height;
}

double GlazingWall::width() const
{
    return _width;
}

void GlazingWall::setWidth(double width)
{
    _width = width;
}

double GlazingWall::surfaceGlazingAg() const
{
    return _surfaceGlazingAg;
}

void GlazingWall::setSurfaceGlazingAg(double surfaceGlazingAg)
{
    _surfaceGlazingAg = surfaceGlazingAg;
}

double GlazingWall::surfaceGlazingAf() const
{
    return _surfaceGlazingAf;
}

void GlazingWall::setSurfaceGlazingAf(double surfaceGlazingAf)
{
    _surfaceGlazingAf = surfaceGlazingAf;
}

double GlazingWall::surfaceOpaqueWallAp() const
{
    return _surfaceOpaqueWallAp;
}

void GlazingWall::setSurfaceOpaqueWallAp(double surfaceOpaqueWallAp)
{
    _surfaceOpaqueWallAp = surfaceOpaqueWallAp;
}

double GlazingWall::surfaceRollingShutterAc() const
{
    return _surfaceRollingShutterAc;
}

void GlazingWall::setSurfaceRollingShutterAc(double surfaceRollingShutterAc)
{
    _surfaceRollingShutterAc = surfaceRollingShutterAc;
}
