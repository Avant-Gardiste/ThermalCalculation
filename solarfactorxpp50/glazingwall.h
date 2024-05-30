#ifndef GLAZINGWALL_H
#define GLAZINGWALL_H

#include "solarfactorxpp50_global.h"
#include <iostream>

using namespace std;

/**
 * @brief
 *
 */
class SOLARFACTORXPP50SHARED_EXPORT GlazingWall
{
public:
    /**
     * @brief
     *
     */
    GlazingWall();
    /**
     * @brief
     *
     */
    ~GlazingWall();

    /**
     * @brief
     *
     * @return string
     */
    string project() const;
    /**
     * @brief
     *
     * @param project
     */
    void setProject(const string &project);

    /**
     * @brief
     *
     * @return string
     */
    string nameGlazing() const;
    /**
     * @brief
     *
     * @param nameGlazing
     */
    void setNameGlazing(const string &nameGlazing);

    /**
     * @brief
     *
     * @return string
     */
    string description() const;
    /**
     * @brief
     *
     * @param description
     */
    void setDescription(const string &description);

    /**
     * @brief
     *
     * @return string
     */
    string type() const;
    /**
     * @brief
     *
     * @param type
     */
    void setType(const string &type);

    /**
     * @brief
     *
     * @return bool
     */
    bool enableMobileProtection() const;
    /**
     * @brief
     *
     * @param enableMobileProtection
     */
    void setEnableMobileProtection(bool enableMobileProtection);

    /**
     * @brief
     *
     * @return bool
     */
    bool withOpaquePart() const;
    /**
     * @brief
     *
     * @param withOpaquePart
     */
    void setWithOpaquePart(bool withOpaquePart);

    /**
     * @brief
     *
     * @return bool
     */
    bool rollerExistence() const;
    /**
     * @brief
     *
     * @param rollerExistence
     */
    void setRollerExistence(bool rollerExistence);

    /**
     * @brief
     *
     * @return double
     */
    double incline() const;
    /**
     * @brief
     *
     * @param incline
     */
    void setIncline(double incline);

    /**
     * @brief
     *
     * @return double
     */
    double height() const;
    /**
     * @brief
     *
     * @param height
     */
    void setHeight(double height);

    /**
     * @brief
     *
     * @return double
     */
    double width() const;
    /**
     * @brief
     *
     * @param width
     */
    void setWidth(double width);

    /**
     * @brief
     *
     * @return double
     */
    double surfaceGlazingAg() const;
    /**
     * @brief
     *
     * @param surfaceGlazingAg
     */
    void setSurfaceGlazingAg(double surfaceGlazingAg);

    /**
     * @brief
     *
     * @return double
     */
    double surfaceGlazingAf() const;
    /**
     * @brief
     *
     * @param surfaceGlazingAf
     */
    void setSurfaceGlazingAf(double surfaceGlazingAf);

    /**
     * @brief
     *
     * @return double
     */
    double surfaceOpaqueWallAp() const;
    /**
     * @brief
     *
     * @param surfaceOpaqueWallAp
     */
    void setSurfaceOpaqueWallAp(double surfaceOpaqueWallAp);

    /**
     * @brief
     *
     * @return double
     */
    double surfaceRollingShutterAc() const;
    /**
     * @brief
     *
     * @param surfaceRollingShutterAc
     */
    void setSurfaceRollingShutterAc(double surfaceRollingShutterAc);

private:
    string _project; /**< TODO: describe */
    string _nameGlazing; /**< TODO: describe */
    string _description; /**< TODO: describe */
    string _type; /**< TODO: describe */

    bool _enableMobileProtection; /**< TODO: describe */
    bool _withOpaquePart; /**< TODO: describe */
    bool _rollerExistence; /**< TODO: describe */

    double _incline; /**< TODO: describe */

    double _height; /**< TODO: describe */
    double _width; /**< TODO: describe */
    double _surfaceGlazingAg; /**< TODO: describe */
    double _surfaceGlazingAf; /**< TODO: describe */

    double _surfaceOpaqueWallAp; /**< TODO: describe */
    double _surfaceRollingShutterAc; /**< TODO: describe */
};

#endif // GLAZINGWALL_H
