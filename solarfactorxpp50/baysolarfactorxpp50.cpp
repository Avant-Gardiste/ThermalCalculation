#include "baysolarfactorxpp50.h"

BaySolarFactorXPP50::BaySolarFactorXPP50(BaySolarFactor *parent) : BaySolarFactor(parent)
{
}

double BaySolarFactorXPP50::emc(double Emn)
{
    return  0.0010301 + 1.179 * Emn - 0.47529 * Emn * Emn + 0.23204 * Emn * Emn * Emn;
}

double BaySolarFactorXPP50::calculationHXI()
{
    double lateral = 0, top = 0, low = 0;
    double beta = 0, betaxx = 0;
    double bbb = 0, aaa = 0, ccc = 0;
    double neutralAxis = 0, neutrefabsAxis = 0;
    double varHXI = 0, varHXA = 0;

    double width = _data->_width;
    double height = _data->_height;

    if (_data->_blind != NULL) {
        lateral = _data->_blind->getLateralSpace();
        top = _data->_blind->getTopSpace();
        low = _data->_blind->getBottomSpace();

        beta = /*round*/(_data->_blind->getBlinds().at(0)->getOpennessFactor()); //??????? round
        betaxx = beta / 100.0;
        bbb = (2.0 / 3.0) * height * (2 * lateral + betaxx * width);

        aaa = low * _data->_width;
        ccc = top * _data->_width;
    }

    neutralAxis = calculationCALZX(aaa, bbb, ccc);
    neutrefabsAxis = neutralAxis * _data->_height / 100;
    bbb = bbb / _data->_height  * 100;

    varHXI = (1200.0f * 0.85f * 0.1975f * 0.96f * (aaa * pow(neutrefabsAxis, 0.5f) + bbb * pow(neutrefabsAxis , 1.5f)) / _data->_width / _data->_height); //check
    varHXI = varHXI / (double)sqrt(10);
    varHXA = varHXI;

    return varHXI;
}
