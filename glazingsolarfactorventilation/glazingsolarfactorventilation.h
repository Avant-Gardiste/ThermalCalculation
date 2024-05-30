#ifndef GLAZINGSOLARFACTORVENTILATION_H
#define GLAZINGSOLARFACTORVENTILATION_H

#include "glazingsolarfactorventilation_global.h"

#include <map>
#include <functional>

#include <boost/thread.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/thread/future.hpp>

#include "object.h"
#include "defineconstants.h"

namespace VD6 {
namespace Calculation {

/**
 * @brief
 *
 */
class GLAZINGSOLARFACTORVENTILATIONSHARED_EXPORT GlazingSolarFactorVentilation
{
public:
    boost::thread_specific_ptr<ClimateConditions::Climate> climateConditions; /**< TODO: describe */
    boost::thread_specific_ptr<bool> flagBlind; /**< TODO: describe */

    /**
     * @brief
     *
     */
    GlazingSolarFactorVentilation();
    /**
     * @brief
     *
     */
    ~GlazingSolarFactorVentilation();

    /**
     * @brief
     *
     * @return vector<double>
     */
    vector<double> calculationGlazingSolarFactorVentilation();
    /**
     * @brief
     *
     * @param type
     */
    void execute(Object::ProjectType type);

    /**
     * @brief
     *
     * @param project
     * @param condition
     */
    void initModuleCalculation(Object::ProjectType project, ClimateConditions::Climate *condition);
    /**
     * @brief
     *
     * @param resultFluxNonNull
     * @param resultFluxNull
     * @return double
     */
    double solarFactor(vector<double> resultFluxNonNull, vector<double> resultFluxNull);
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
     * @return vector<double>
     */
    vector<double> calculationEnergy();

    /**
     * @brief
     *
     * @param varHC
     * @param varHR
     * @param hrv
     * @param varHXA
     * @param hoh
     * @param temperature
     * @param varQQ
     * @param varHXVA
     * @return vector<vector<double> >
     */
    vector<vector<double > > conditionMatrixTemperatures(vector<double> varHC, vector<double> varHR, double hrv, double varHXA, double hoh, double temperature, double varQQ, double varHXVA);

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
     * @param temperature
     * @param dTemperature
     * @param gasgap
     * @return double
     */
    double coefficientConvectiveExchange(double temperature, double dTemperature, GasGap *gasgap);
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
     * @param matrixV
     * @param coefHR
     * @param coefHXI
     * @param coefHXA
     * @param coefHC
     * @param coefEPSI
     * @param dTam
     * @param tam
     * @param hoh
     * @param coefHXVA
     * @param coefQQ
     * @param coefHXVI
     * @return bool
     */
    bool resultIsAccepted(vector<double> matrixV, vector<double> &coefHR, double coefHXI, double &coefHXA, vector<double> &coefHC, vector<double> &coefEPSI, double &dTam, double &tam , double &hoh, double &coefHXVA, double coefQQ, double coefHXVI);
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
     * @param x
     * @param y
     * @return double
     */
    double getEmissivityByIndex(int x, int y);
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
     * @param index
     * @return GasGap
     */
    GasGap *getGasByIndex(int index);

    /**
     * @brief
     *
     * @return Object::ObjectGlazingSolarFactor
     */
    Object::ObjectGlazingSolarFactor *getData() const;
    /**
     * @brief
     *
     * @param data
     */
    void setData(Object::ObjectGlazingSolarFactor *data);

    /**
     * @brief
     *
     * @return double
     */
    double getSolarFactor() const;
    /**
     * @brief
     *
     * @param solarFactor
     */
    void setSolarFactor(double solarFactor);
    /**
     * @brief
     *
     * @return double
     */
    double getFactorRadiation() const;
    /**
     * @brief
     *
     * @param radiationFactor
     */
    void setFactorRadiation(double radiationFactor);
    /**
     * @brief
     *
     * @return double
     */
    double getFactorConvection() const;
    /**
     * @brief
     *
     * @param convectionFactor
     */
    void setFactorConvection(double convectionFactor);
    /**
     * @brief
     *
     * @return double
     */
    double getFactorVentilation() const;
    /**
     * @brief
     *
     * @param ventilationFactor
     */
    void setFactorVentilation(double ventilationFactor);

    /**
     * @brief
     *
     * @return GasGap
     */
    GasGap *getVentilation();
    /**
     * @brief
     *
     * @return int
     */
    int getPositionVentilation();
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
     * @param tth[]
     * @param tmpEM1[]
     * @param tmpEM2[]
     * @param numGlass
     * @param qth0
     * @param qqthn
     * @param glassTemperator
     * @return vector<vector<double> >
     */
    vector<vector<double >> conditionMatrixFluxNetThermique(double tth[], double tmpEM1[], double tmpEM2[],
                                 double numGlass, double qth0, double qqthn, vector<double> glassTemperator);
    void bilan(vector<double> &matrixV, int numGlassBlind);
    double equation(double a, double b, double c, double x);
    double resolTemperature(double a, double b, double c);
    double calVelHtp(double hg, double T1, double T2, double tth, int gas);
//    double calVisHtp(double hg, double T1, double T2, double tth, GasGap *gasgap);
    double calVel(double T1, double T2, double tth, int gasID);
    double coefficientHg(double temperature, double dTemperature, GasGap *gasgap);
private:
    Object::ObjectGlazingSolarFactor* _data; /**< TODO: describe */
    double _solarFactor; /**< TODO: describe */
    vector<double> _hr; /**< TODO: describe */
    vector<double> _hc; /**< TODO: describe */
    double _gth; /**< TODO: describe */
    double _gc; /**< TODO: describe */
    double _gv; /**< TODO: describe */
    double _hcn;

};

}
}
#endif // GLAZINGSOLARFACTORVENTILATION_H
