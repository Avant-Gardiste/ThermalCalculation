#ifndef OQAPUEWALL_H
#define OQAPUEWALL_H

#include "solarfactorxpp50_global.h"

#include <iostream>

using namespace std;

/**
 * @brief
 *
 */
class SOLARFACTORXPP50SHARED_EXPORT OpaqueWall
{
public:
    /**
     * @brief
     *
     */
    OpaqueWall();
    /**
     * @brief
     *
     */
    ~OpaqueWall();

    /**
     * @brief
     *
     * @return double
     */
    double surfaceAp() const;
    /**
     * @brief
     *
     * @param surfaceAp
     */
    void setSurfaceAp(double surfaceAp);

    /**
     * @brief
     *
     * @return double
     */
    double lpPerimeter() const;
    /**
     * @brief
     *
     * @param lpPerimeter
     */
    void setLpPerimeter(double lpPerimeter);

    /**
     * @brief
     *
     * @return double
     */
    double coefUp() const;
    /**
     * @brief
     *
     * @param coefUp
     */
    void setCoefUp(double coefUp);

    /**
     * @brief
     *
     * @return double
     */
    double coefBinding() const;
    /**
     * @brief
     *
     * @param coefBinding
     */
    void setCoefBinding(double coefBinding);

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
    double _surfaceAp; /**< TODO: describe */
    double _lpPerimeter; /**< TODO: describe */
    double _coefUp; /**< TODO: describe */

    double _coefBinding; /**< TODO: describe */
    double _coefEnergyAbsorption; /**< TODO: describe */
};

#endif // OQAPUEWALL_H
