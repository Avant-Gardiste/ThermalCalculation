#ifndef OBSTACLEVD_H
#define OBSTACLEVD_H

#include "components_global.h"

#include <string>

using namespace std;

namespace VD6 {
namespace Common {

/**
 * @brief
 *
 */
class COMPONENTSSHARED_EXPORT ObstacleVD
{
public:
    /**
     * @brief
     *
     */
    ObstacleVD();
    /**
     * @brief
     *
     */
    ~ObstacleVD();

    /**
     * @brief
     *
     * @return unsigned int
     */
    unsigned int id() const;
    /**
     * @brief
     *
     * @param value
     */
    void setId(unsigned int value);

    /**
     * @brief
     *
     * @return string
     */
    string name() const;
    /**
     * @brief
     *
     * @param value
     */
    void setName(const string &value);

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
    double distance() const;
    /**
     * @brief
     *
     * @param distance
     */
    void setDistance(double distance);

    /**
     * @brief
     *
     * @return double
     */
    double high() const;
    /**
     * @brief
     *
     * @param high
     */
    void setHigh(double high);

    /**
     * @brief
     *
     * @return double
     */
    double low() const;
    /**
     * @brief
     *
     * @param low
     */
    void setLow(double low);

    /**
     * @brief
     *
     * @return double
     */
    double lateral() const;
    /**
     * @brief
     *
     * @param lateral
     */
    void setLateral(double lateral);

    /**
     * @brief
     *
     * @return double
     */
    double thermalResistance() const;
    /**
     * @brief
     *
     * @param thermalResistance
     */
    void setThermalResistance(double thermalResistance);

    /**
     * @brief
     *
     * @return string
     */
    string color() const;
    /**
     * @brief
     *
     * @param color
     */
    void setColor(const string &color);

    /**
     * @brief
     *
     * @return double
     */
    double temperature() const;
    /**
     * @brief
     *
     * @param temperature
     */
    void setTemperature(double temperature);

    /**
     * @brief
     *
     * @return double
     */
    double te() const;
    /**
     * @brief
     *
     * @param te
     */
    void setTe(double te);

    /**
     * @brief
     *
     * @return double
     */
    double re1() const;
    /**
     * @brief
     *
     * @param re1
     */
    void setRe1(double re1);

    /**
     * @brief
     *
     * @return double
     */
    double emn1() const;
    /**
     * @brief
     *
     * @param emn1
     */
    void setEmn1(double emn1);

    /**
     * @brief
     *
     * @return double
     */
    double re2() const;
    /**
     * @brief
     *
     * @param re2
     */
    void setRe2(double re2);

    /**
     * @brief
     *
     * @return double
     */
    double emn2() const;
    /**
     * @brief
     *
     * @param emn2
     */
    void setEmn2(double emn2);

    /**
     * @brief
     *
     * @param another
     * @return bool
     */
    bool equal(ObstacleVD *another);

private:
    //dimensions
    unsigned int _id; /**< TODO: describe */

    string _name; /**< TODO: describe */

    double _height; /**< TODO: describe */
    double _width; /**< TODO: describe */
    double _distance; /**< TODO: describe */

    //Peripheral
    double _high; /**< TODO: describe */
    double _low; /**< TODO: describe */
    double _lateral; /**< TODO: describe */
    double _thermalResistance; /**< TODO: describe */

    string _color; /**< TODO: describe */

    double _te; /**< TODO: describe */
    double _re1; /**< TODO: describe */
    double _emn1; /**< TODO: describe */
    double _re2; /**< TODO: describe */
    double _emn2; /**< TODO: describe */

    double _temperature; /**< TODO: describe */

};

}
}

#endif // OBSTACLEVD_H
