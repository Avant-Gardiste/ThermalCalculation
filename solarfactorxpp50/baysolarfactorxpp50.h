#ifndef BAYSOLARFACTORXPP50_H
#define BAYSOLARFACTORXPP50_H


#include "solarfactorxpp50_global.h"

#include "baysolarfactor.h"

using namespace VD6::Calculation;

/**
 * @brief
 *
 */
class SOLARFACTORXPP50SHARED_EXPORT BaySolarFactorXPP50 : public BaySolarFactor
{
public:
    /**
     * @brief
     *
     * @param parent
     */
    explicit BaySolarFactorXPP50(BaySolarFactor *parent = 0);

    /**
     * @brief
     *
     * @return double
     */
    virtual double calculationHXI();
    /**
     * @brief
     *
     * @param double
     * @return double
     */
    virtual double emc(double );
private:

};

#endif // BAYSOLARFACTORXPP50_H
