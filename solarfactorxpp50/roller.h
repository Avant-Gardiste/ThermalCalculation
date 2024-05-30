#ifndef ROLLER_H
#define ROLLER_H
#include "solarfactorxpp50_global.h"
#include <iostream>

using namespace std;

/**
 * @brief
 *
 */
class SOLARFACTORXPP50SHARED_EXPORT Roller
{
public:
    /**
     * @brief
     *
     */
    Roller();
    /**
     * @brief
     *
     */
    ~Roller();

    /**
     * @brief
     *
     * @return double
     */
    double surfaceAc() const;
    /**
     * @brief
     *
     * @param surfaceAc
     */
    void setSurfaceAc(double surfaceAc);

    /**
     * @brief
     *
     * @return double
     */
    double coefUc() const;
    /**
     * @brief
     *
     * @param coefUc
     */
    void setCoefUc(double coefUc);

    /**
     * @brief
     *
     * @return double
     */
    double coefEnergyAbsorption() const;
    /**
     * @brief
     *
     * @param coefEnergyAbsorption
     */
    void setCoefEnergyAbsorption(double coefEnergyAbsorption);

private:
    double _surfaceAc; /**< TODO: describe */
    double _coefUc; /**< TODO: describe */
    double _coefEnergyAbsorption; /**< TODO: describe */
};

#endif // ROLLER_H
