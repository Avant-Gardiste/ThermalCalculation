#ifndef GLAZINGUVALUEVENTILATION_H
#define GLAZINGUVALUEVENTILATION_H

#include "glazinguvalueventilation_global.h"

#include <functional>

#include <boost/thread.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/thread/future.hpp>

#include "object.h"
#include "defineconstants.h"

using namespace VD6::Common;

namespace VD6 {
namespace Calculation {

/**
 * @brief
 *
 */
class GLAZINGUVALUEVENTILATIONSHARED_EXPORT GlazingUValueVentilation
{
public:
    boost::thread_specific_ptr<bool> flagBlind; /**< TODO: describe */
    boost::thread_specific_ptr<ClimateConditions::Climate> climateConditions; /**< TODO: describe */

    /**
     * @brief
     *
     */
    GlazingUValueVentilation();
    /**
     * @brief
     *
     */
    ~GlazingUValueVentilation();

    /**
     * @brief
     *
     * @return vector<double>
     */
    vector<double> execute();
    /**
     * @brief
     *
     * @param data
     */
    void setData(Object::ObjectUValue *data);
    /**
     * @brief
     *
     * @return map<string, double>
     */
    map<string, double> getResultGlazingUValueVentilation() const;

    /**
     * @brief
     *
     * @return vector<double>
     */
    vector<double> getResultUValueVentilation() const;

private:
    /**
     * @brief
     *
     * @param type
     */
    void initiation(Object::ProjectType type);
    /**
     * @brief
     *
     * @param energy
     */
    void calculateCoeffUValueVentilation(vector<double> energy);
    /**
     * @brief
     *
     * @param lateralVentilation
     * @param lowVentilation
     * @param highVentilation
     */
    void zeroingPeripheralSpaces(double &lateralVentilation, double &lowVentilation, double &highVentilation);
    /**
     * @brief
     *
     * @param EPSI
     * @param HR
     * @param hrv
     */
    void radialExchangeCoefficients(vector<double> &EPSI, vector<double> &HR, double &hrv);

    /**
     * @brief
     *
     * @return double
     */
    double calculationHXI();
    /**
     * @brief
     *
     * @param aaa
     * @param bbb
     * @param ccc
     * @return double
     */
    double calculationCALZX(double aaa, double bbb, double ccc);
    /**
     * @brief
     *
     * @param valEmn
     * @return double
     */
    double emc(double valEmn);
    /**
     * @brief
     *
     * @param aaa
     * @param bbb
     * @param ccc
     * @param neutralAxis
     * @return double
     */
    double ff(double aaa, double bbb, double ccc, double neutralAxis);
    /**
     * @brief
     *
     * @param gas
     * @return double
     */
    double calculationHXI(GasGap *gas);
    /**
     * @brief
     *
     * @param x
     * @param y
     * @return double
     */
    double getEmissivityByIndex(int x, int y);
    /**
     * @brief
     *
     * @param temperature
     * @param dTemperature
     * @param gasgap
     * @return double
     */
    double coefficientConvectiveExchange(double temperature, double dTemperature, GasGap* gasgap);

    /**
     * @brief
     *
     * @return vector<double>
     */
    vector<double> calculationEnergySysterm();
    /**
     * @brief
     *
     * @param matrixCX
     * @return vector<double>
     */
    vector<double> resolutionSystem(vector<vector<double> > matrixCX);
    /**
     * @brief
     *
     * @param varHC
     * @param varHR
     * @param hrv
     * @param varHXA
     * @param H0H
     * @param QQ
     * @param HXVA
     * @return vector<vector<double> >
     */
    vector<vector<double > > conditionMatrixTemperatures(vector<double> varHC, vector<double> varHR, double hrv, double varHXA, double H0H, double QQ, double HXVA);

    /**
     * @brief
     *
     * @param matrixV
     * @param varHR
     * @param varHXI
     * @param varHXA
     * @param varHC
     * @param varEPSI
     * @param dTam
     * @param tam
     * @param H0H
     * @param QQ
     * @param HXVA
     * @param HXVI
     * @return bool
     */
    bool resultIsAccepted(vector<double> &matrixV, vector<double> &varHR, double &varHXI,
                          double &varHXA, vector<double> &varHC, vector<double> &varEPSI,
                          double &dTam, double &tam , double &H0H, double &QQ, double &HXVA, double &HXVI);

    /**
     * @brief
     *
     * @param name
     * @return ObstacleVD
     */
    ObstacleVD *getObstacleByName(string name);

    /**
     * @brief
     *
     * @param index
     * @return GasGap
     */
    GasGap *getGasByIndex(int index);
    /**
     * @brief
     *
     * @return GasGap
     */
    GasGap *getVentilatedAirSpace();

    /**
     * @brief
     *
     * @return int
     */
    int getPositionVentilation();


private:
    Object::ObjectUValue *_data; /**< TODO: describe */
    vector<double>  _results; /**< TODO: describe */
};

}
}

#endif // GLAZINGUVALUEVENTILATION_H
