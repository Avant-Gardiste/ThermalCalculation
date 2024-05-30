#ifndef GLAZINGSOLARFACTOR_H
#define GLAZINGSOLARFACTOR_H

#include "glazingsolarfactor_global.h"

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
class GLAZINGSOLARFACTORSHARED_EXPORT GlazingSolarFactor
{
public:
    boost::thread_specific_ptr<Object::Climate> climateConditions; /**< TODO: describe */
    boost::thread_specific_ptr<bool> flagBlind; /**< TODO: describe */

    /**
     * @brief
     *
     */
    GlazingSolarFactor();

    /**
     * @brief
     *
     * @return vector<double>
     */
    vector<double> calculationGlazingSolarFactor();

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
     * @return vector<vector<double> >
     */
    vector<vector<double > > conditionMatrixTemperatures(vector<double> varHC, vector<double> varHR, double hrv, double varHXA);
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
    double coefficientHg(double temperature, double dTemperature, GasGap *gasgap);
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
     * @param varHR
     * @param varHXI
     * @param varHXA
     * @param varHC
     * @param varEPSI
     * @param dTam
     * @param tam
     * @param stop
     */
    void itIsTheEnd(vector<double> &matrixV, vector<double> &varHR, double &varHXI, double &varHXA, vector<double> &varHC,vector<double> &varEPSI, double &dTam,double &tam ,bool &stop);
    /**
     * @brief
     *
     * @param matrixCX
     * @return vector<double>
     */
    void bilan(vector<double> &matrixV, int numGlassBlind);
    vector<double> resolutionSystem(vector<vector<double> > matrixCX);
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
     * @param tth[]
     * @param tmpEM1[]
     * @param tmpEM2[]
     * @param numGlass
     * @param qth0
     * @param qqthn
     * @param glassTemperator
     * @return vector<vector<double> >
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
    vector<vector<double >> conditionMatrixFluxNetThermique(double tth[], double tmpEM1[], double tmpEM2[],
                                                                    double numGlass, double qth0, double qqthn, vector<double> glassTemperator);
    double equation(double a, double b, double c, double x);
    double resolTemperature(double a, double b, double c);
    GasGap *getGasByIndex(int index);
    double calVelHtp(double hg, double T1, double T2, double tth);
    double calVel(double T1, double T2, double tth);
private:
    Object::ObjectGlazingSolarFactor* _data; /**< TODO: describe */
    double _solarFactor; /**< TODO: describe */

    vector<double> _solarFactorElements; /**< TODO: describe */
    vector<double> _hr; /**< TODO: describe */
    vector<double> _hc; /**< TODO: describe */
    double _gth; /**< TODO: describe */
    double _gc; /**< TODO: describe */
    double _gv; /**< TODO: describe */
    double _hcn;
};


}
}
#endif // GLAZINGSOLARFACTOR_H
