#include "baysolarfactorventilationxpp50.h"

BaySolarFactorVentilationXPP50::BaySolarFactorVentilationXPP50(BaySolarFactorVentilation *parent)
    : BaySolarFactorVentilation(parent)
{
}

double BaySolarFactorVentilationXPP50::calculationHXI(int blind, double beta, double top, double low, double lateral)
{
    double betaxx = 0;
    double bbb = 0;
    double aaa = 0;
    double ccc = 0;

    double neutralAxis = 0;
    double neutrefabsAxis = 0;

    double varHXI = 0;
    double varHXA =0;
    double width = _data->_width;
    double height = _data->_height;

    if (blind > 0){
        betaxx = round(beta) / 100.0; //VD5: beta is declared "byte" in func
        bbb = (2.0/3.0) * height * (2 * lateral + betaxx * width);
        aaa = low * _data->_width;
        ccc = top * _data->_width;
    }

    neutralAxis = calculationCALZX(aaa, bbb, ccc);
    neutrefabsAxis = neutralAxis * _data->_height / 100;
    bbb = bbb / _data->_height  * 100;

    varHXI =(1200.0f * 0.85f * 0.1975f * 0.96f * (aaa * pow(neutrefabsAxis, 0.5f) + bbb * pow(neutrefabsAxis , 1.5f)) / _data->_width / _data->_height); //check
    varHXI = varHXI / (double)sqrt(10);
    varHXA = varHXI;

    return varHXI;
}

double BaySolarFactorVentilationXPP50::emc(double Emn)
{
    return  0.0010301 + 1.179 * Emn - 0.47529 * Emn * Emn + 0.23204 * Emn * Emn * Emn;
}
