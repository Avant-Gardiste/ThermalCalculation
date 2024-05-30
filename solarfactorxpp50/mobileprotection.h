#ifndef MOBILEPROTECTION_H
#define MOBILEPROTECTION_H
#include "solarfactorxpp50_global.h"

#include <iostream>
#include "blindvd.h"
#include "defineblind.h"

using namespace std;
using namespace VD6::Common;

/**
 * @brief
 *
 */
class SOLARFACTORXPP50SHARED_EXPORT MobileProtection : public DefineBlind
{
public:
    /**
     * @brief
     *
     * @param parent
     */
    explicit MobileProtection(DefineBlind *parent = 0);
    /**
     * @brief
     *
     */
    virtual ~MobileProtection();

    /**
     * @brief
     *
     * @return MobileProtection
     */
    MobileProtection *clone();

    /**
     * @brief
     *
     * @return double
     */
    double deltalR() const;
    /**
     * @brief
     *
     * @param deltalR
     */
    void setDeltalR(double deltalR);

    /**
     * @brief
     *
     * @return bool
     */
    bool getEnableSolarTracking() const;
    /**
     * @brief
     *
     * @param value
     */
    void setEnableSolarTracking(bool value);

    /**
     * @brief
     *
     * @return double
     */
    double getDistacneAxises() const;
    /**
     * @brief
     *
     * @param distacneAxises
     */
    void setDistacneAxises(double distacneAxises);

    /**
     * @brief
     *
     * @return double
     */
    double getWidthBlade() const;
    /**
     * @brief
     *
     * @param widthBlade
     */
    void setWidthBlade(double widthBlade);

    /**
     * @brief
     *
     * @return double
     */
    double getOrientationBlade() const;
    /**
     * @brief
     *
     * @param orientationBlade
     */
    void setOrientationBlade(double orientationBlade);

    /**
     * @brief
     *
     * @return double
     */
    double getActualAngle() const;
    /**
     * @brief
     *
     * @param actualAngle
     */
    void setActualAngle(double actualAngle);

private:
    double _deltalR; /**< TODO: describe */

    //Lame
    bool enableSolarTracking; // 1: equivalent characteristics for a given angle 0: Solar tracking mode /**< TODO: describe */
    double _distacneAxises; /**< TODO: describe */
    double _widthBlade; /**< TODO: describe */
    double _orientationBlade; /**< TODO: describe */
    double _actualAngle; /**< TODO: describe */


};

#endif // MOBILEPROTECTION_H
