#ifndef BAYSOLARFACTORVENTILATIONXPP50_H
#define BAYSOLARFACTORVENTILATIONXPP50_H

#include "solarfactorxpp50_global.h"

#include "object.h"
#include "baysolarfactorventilation.h"

using namespace VD6::Common;
using namespace VD6::Calculation;

/**
 * @brief
 *
 */
class SOLARFACTORXPP50SHARED_EXPORT BaySolarFactorVentilationXPP50 : public BaySolarFactorVentilation
{
public:
    /**
     * @brief
     *
     * @param parent
     */
    explicit BaySolarFactorVentilationXPP50(BaySolarFactorVentilation *parent = 0);

    /**
     * @brief
     *
     * @param blind
     * @param beta
     * @param top
     * @param low
     * @param lateral
     * @return double
     */
    virtual double calculationHXI(int blind, double beta, double top, double low, double lateral);
    /**
     * @brief
     *
     * @param double
     * @return double
     */
    virtual double emc(double );

};

#endif // BAYSOLARFACTORVENTILATIONXPP50_H
