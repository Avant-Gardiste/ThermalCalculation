#ifndef FRAME_H
#define FRAME_H

#include "solarfactorxpp50_global.h"

#include <iostream>

using namespace std;

/**
 * @brief
 *
 */
class SOLARFACTORXPP50SHARED_EXPORT Frame
{
public:
    /**
     * @brief
     *
     */
    Frame();
    /**
     * @brief
     *
     */
    ~Frame();

    /**
     * @brief
     *
     * @return double
     */
    double afSurface() const;
    /**
     * @brief
     *
     * @param afSurface
     */
    void setAfSurface(double afSurface);

    /**
     * @brief
     *
     * @return double
     */
    double ufAverage() const;
    /**
     * @brief
     *
     * @param ufAverage
     */
    void setUfAverage(double ufAverage);

    /**
     * @brief
     *
     * @return string
     */
    string materialType() const;
    /**
     * @brief
     *
     * @param materialType
     */
    void setMaterialType(string materialType);

    /**
     * @brief
     *
     * @return int
     */
    int glazingBinding() const;
    /**
     * @brief
     *
     * @param glazingBinding
     */
    void setGlazingBinding(int glazingBinding);

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

    double _afSurface; /**< TODO: describe */
    double _ufAverage; /**< TODO: describe */

    string _materialType; /**< TODO: describe */
    int _glazingBinding; /**< TODO: describe */

    double _coefBinding; /**< TODO: describe */
    double _coefEnergyAbsorption; /**< TODO: describe */
};

#endif // FRAME_H
