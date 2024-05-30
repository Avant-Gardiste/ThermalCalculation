#include "information.h"

using namespace VD6::Common;

Information::Information()
{
}

Information::~Information()
{
}

string Information::getName() const
{
    return name;
}

void Information::setName(const string &value)
{
    name = value;
}

string Information::getDescription() const
{
    return description;
}

void Information::setDescription(const string &value)
{
    description = value;
}

string Information::getGlazing() const
{
    return glazing;
}

void Information::setGlazing(const string &value)
{
    glazing = value;
}
