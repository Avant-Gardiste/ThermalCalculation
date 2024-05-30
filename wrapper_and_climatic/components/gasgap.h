#ifndef GASGAP_H
#define GASGAP_H

#include "components_global.h"

#include <string>

using namespace std;

namespace VD6 {
namespace Common {

/**
 * @brief
 *
 */
class COMPONENTSSHARED_EXPORT GasGap
{
public:
    /**
     * @brief
     *
     */
    explicit GasGap();
    /**
     * @brief
     *
     * @param clone
     */
    GasGap(GasGap *clone);
    /**
     * @brief
     *
     */
    virtual ~GasGap();

    /**
     * @brief
     *
     * @return string
     */
    string getName() const;
    /**
     * @brief
     *
     * @param value
     */
    void setName(const string &value);

    /**
     * @brief
     *
     * @return int
     */
    int getType() const;
    /**
     * @brief
     *
     * @param value
     */
    void setType(int value);

    /**
     * @brief
     *
     * @return double
     */
    double getThickness() const;
    /**
     * @brief
     *
     * @param value
     */
    void setThickness(double value);

    /**
     * @brief
     *
     * @return double
     */
    double getArgon() const;
    /**
     * @brief
     *
     * @param value
     */
    void setArgon(double value);

    /**
     * @brief
     *
     * @return double
     */
    double getKrypton() const;
    /**
     * @brief
     *
     * @param value
     */
    void setKrypton(double value);

    /**
     * @brief
     *
     * @return double
     */
    double getXenon() const;
    /**
     * @brief
     *
     * @param value
     */
    void setXenon(double value);

    /**
     * @brief
     *
     * @return int
     */
    int getTypeVentilation() const;
    /**
     * @brief
     *
     * @param value
     */
    void setTypeVentilation(int value);

    /**
     * @brief
     *
     * @return double
     */
    double getAirFlow() const;
    /**
     * @brief
     *
     * @param value
     */
    void setAirFlow(double value);

    /**
     * @brief
     *
     * @return double
     */
    double getAirTemperature() const;
    /**
     * @brief
     *
     * @param value
     */
    void setAirTemperature(double value);

    /**
     * @brief
     *
     * @return double
     */
    double getHigh() const;
    /**
     * @brief
     *
     * @param value
     */
    void setHigh(double value);

    /**
     * @brief
     *
     * @return double
     */
    double getLow() const;
    /**
     * @brief
     *
     * @param value
     */
    void setLow(double value);

    /**
     * @brief
     *
     * @return double
     */
    double getLateral() const;
    /**
     * @brief
     *
     * @param value
     */
    void setLateral(double value);

    /**
     * @brief
     *
     * @return bool
     */
    bool getAirflowOutlet() const;
    /**
     * @brief
     *
     * @param airflowOutlet
     */
    void setAirflowOutlet(bool airflowOutlet);

    /**
     * @brief
     *
     * @return bool
     */
    bool getVentilationFrom() const;
    /**
     * @brief
     *
     * @param ventilationFrom
     */
    void setVentilationFrom(bool ventilationFrom);

    /**
     * @brief
     *
     * @param another
     * @return bool
     */
    bool equal(GasGap *another);

private:
    string _name; /**< TODO: describe */

    int _type; //0: Air, 1: Mixte, 2: Ventile /**< TODO: describe */
    double _thickness; /**< TODO: describe */

    double _argon; /**< TODO: describe */
    double _krypton; /**< TODO: describe */
    double _xenon; /**< TODO: describe */

    int _typeVentilation; //Forced = 0, Natural= 1, Respiration =2 /**< TODO: describe */

    double _airFlow; /**< TODO: describe */
    double _airTemperature; /**< TODO: describe */

    bool _airflowOutlet; // Interior = 0, Exterior = 1 /**< TODO: describe */
    bool _ventilationFrom; // Interior = 0, Exterior = 1 /**< TODO: describe */

    double _high; /**< TODO: describe */
    double _low; /**< TODO: describe */
    double _lateral; /**< TODO: describe */

};

}
}

#endif // GASGAP_H
