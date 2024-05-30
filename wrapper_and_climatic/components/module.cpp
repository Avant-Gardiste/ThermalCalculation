#include "module.h"

using namespace VD6::Common;

Module::Module()
{
}

Module::~Module()
{
}

string Module::getName() const
{
    return _name;
}

void Module::setName(const string &value)
{
    _name = value;
}
