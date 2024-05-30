#ifndef GLAZINGXP50_H
#define GLAZINGXP50_H

#include "solarfactorxpp50_global.h"

#include <iostream>

#include "defineglass.h"

using namespace VD6::Common;

/**
 * @brief
 *
 */
class SOLARFACTORXPP50SHARED_EXPORT GlazingXP50 : public DefineGlass
{
public:
    /**
     * @brief
     *
     * @param parent
     */
    explicit GlazingXP50(DefineGlass *parent = 0);
    /**
     * @brief
     *
     */
    virtual ~GlazingXP50();

    /**
     * @brief
     *
     * @return bool
     */
    bool gasGapsVentilationExistence();

    /**
     * @brief
     *
     * @return double
     */
    double glazingSurface() const;
    /**
     * @brief
     *
     * @param glazingSurface
     */
    void setGlazingSurface(double glazingSurface);

    /**
     * @brief
     *
     * @return double
     */
    double totalPerimetersLg() const;
    /**
     * @brief
     *
     * @param totalPerimetersLg
     */
    void setTotalPerimetersLg(double totalPerimetersLg);

    /**
     * @brief
     *
     * @return double
     */
    double coefUgAverage() const;
    /**
     * @brief
     *
     * @param coefUgAverage
     */
    void setCoefUgAverage(double coefUgAverage);

private:
    double _glazingSurface; /**< TODO: describe */
    double _totalPerimetersLg; /**< TODO: describe */
    double _coefUgAverage; /**< TODO: describe */
};

#endif // GLAZINGXP50_H
