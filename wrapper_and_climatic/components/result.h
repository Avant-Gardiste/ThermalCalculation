#ifndef RESULT_H
#define RESULT_H

#include "components_global.h"

#include <map>
#include <string>
#include <vector>

#include "object.h"

using namespace std;

namespace VD6 {
namespace Common {

/**
 * @brief
 *
 */
class COMPONENTSSHARED_EXPORT Result
{
public:
    /**
     * @brief
     *
     */
    Result();

    /**
     * @brief
     *
     * @return vector<double>
     */
    vector<double> getSolarGlass() const;
    /**
     * @brief
     *
     * @param solarGlass
     */
    void setSolarGlass(const vector<double> &solarGlass);

    /**
     * @brief
     *
     * @return vector<vector<double> >
     */
    vector<vector<double> > getSolarGlobal() const;
    /**
     * @brief
     *
     * @param solarGlobal
     */
    void setSolarGlobal(const vector<vector<double> > &solarGlobal);

    /**
     * @brief
     *
     * @return vector<vector<double> >
     */
    vector<vector<double> > getSolarAverage() const;
    /**
     * @brief
     *
     * @param solarAverage
     */
    void setSolarAverage(const vector<vector<double> > &solarAverage);

    /**
     * @brief
     *
     * @return vector<double>
     */
    vector<double> getLightGlass() const;
    /**
     * @brief
     *
     * @param lightGlass
     */
    void setLightGlass(const vector<double> &lightGlass);

    /**
     * @brief
     *
     * @return vector<vector<double> >
     */
    vector<vector<double> > getLightGlobal() const;
    /**
     * @brief
     *
     * @param lightGlobal
     */
    void setLightGlobal(const vector<vector<double> > &lightGlobal);

    /**
     * @brief
     *
     * @return vector<vector<double> >
     */
    vector<vector<double> > getLightAverage() const;
    /**
     * @brief
     *
     * @param lightAverage
     */
    void setLightAverage(const vector<vector<double> > &lightAverage);

    /**
     * @brief
     *
     * @return double
     */
    double getCoefUGlass() const;
    /**
     * @brief
     *
     * @param value
     */
    void setCoefUGlass(double value);

    /**
     * @brief
     *
     * @return double
     */
    double getCoefUGlobal() const;
    /**
     * @brief
     *
     * @param value
     */
    void setCoefUGlobal(double value);

    /**
     * @brief
     *
     * @return std::map<string, Object::BaySolarFactorResult>
     */
    std::map<string, Object::BaySolarFactorResult> getBaySolarFactor() const;
    /**
     * @brief
     *
     * @param std::map<string
     * @param BaySolarFactor
     */
    void setBaySolarFactor(const std::map<string, Object::BaySolarFactorResult> &BaySolarFactor);

    /**
     * @brief
     *
     * @return double
     */
    double getHi673() const;
    /**
     * @brief
     *
     * @param hi673
     */
    void setHi673(double hi673);

    /**
     * @brief
     *
     * @return double
     */
    double getTsi() const;
    /**
     * @brief
     *
     * @param tsi
     */
    void setTsi(double tsi);

    /**
     * @brief
     *
     * @return double
     */
    double getTse() const;
    /**
     * @brief
     *
     * @param tse
     */
    void setTse(double tse);

    /**
     * @brief
     *
     * @return std::map<string, Object::SealingJointResult>
     */
    std::map<string, Object::SealingJointResult> getResultSealingJoint() const;
    /**
     * @brief
     *
     * @param std::map<string
     * @param sealingJoint
     */
    void setResultSealingJoint(const std::map<string, Object::SealingJointResult> &sealingJoint);

    /**
     * @brief
     *
     * @return map<string, Object::ThermalBreakageResult *>
     */
    map<string, Object::ThermalBreakageResult *> getResultThermalBreakage() const;
    /**
     * @brief
     *
     * @param map<string
     * @param thermalBreakage
     */
    void setResultThermalBreakage(const map<string, Object::ThermalBreakageResult *> &thermalBreakage);

    /**
     * @brief
     *
     * @return map<string, double>
     */
    map<string, double> getObstaclesUValue() const;
    /**
     * @brief
     *
     * @param map<string
     * @param coefUValue
     */
    void setObstaclesUValue(const map<string, double> &coefUValue);

    /**
     * @brief
     *
     * @return std::map<string, Object::MaximalTemperaturesResult *>
     */
    std::map<string, Object::MaximalTemperaturesResult *> getResultMaximalTemperatures() const;
    /**
     * @brief
     *
     * @param std::map<string
     * @param maximalTemperatures
     */
    void setResultMaximalTemperatures(const std::map<string, Object::MaximalTemperaturesResult *> &maximalTemperatures);

    /**
     * @brief
     *
     * @return double
     */
    double getSolarFactorGlass() const;
    /**
     * @brief
     *
     * @param solarFactorGlass
     */
    void setSolarFactorGlass(double solarFactorGlass);

    /**
     * @brief
     *
     * @return double
     */
    double getSolarFactorGlobal() const;
    /**
     * @brief
     *
     * @param solarFactorGlobal
     */
    void setSolarFactorGlobal(double solarFactorGlobal);

    /**
     * @brief
     *
     * @return Object::SealingJointVECResult
     */
    Object::SealingJointVECResult *getSealingJointVEC() const;
    /**
     * @brief
     *
     * @param sealingJointVEC
     */
    void setSealingJointVEC(Object::SealingJointVECResult *sealingJointVEC);

    /**
     * @brief
     *
     * @return std::map<string, Object::StressAndDeflectionResult *>
     */
    std::map<string, Object::StressAndDeflectionResult *> getStressAndDeflection() const;
    /**
     * @brief
     *
     * @param std::map<string
     * @param stressAndDeflection
     */
    void setStressAndDeflection(const std::map<string, Object::StressAndDeflectionResult *> &stressAndDeflection);

    /**
     * @brief
     *
     * @return Object::ThermalBreakageSpecificResult
     */
    Object::ThermalBreakageSpecificResult *getThermalBreakageSpecific() const;
    /**
     * @brief
     *
     * @param thermalBreakageSpecific
     */
    void setThermalBreakageSpecific(Object::ThermalBreakageSpecificResult *thermalBreakageSpecific);

    /**
     * @brief
     *
     * @return Object::SlidingSashResult
     */
    Object::SlidingSashResult *getSlidingSash() const;
    /**
     * @brief
     *
     * @param slidingSash
     */
    void setSlidingSash(Object::SlidingSashResult *slidingSash);

private:
    vector<double> _solarGlass; /**< TODO: describe */
    vector<vector<double> > _solarGlobal; /**< TODO: describe */
    vector<vector<double> > _solarAverage; /**< TODO: describe */

    vector<double> _lightGlass; /**< TODO: describe */
    vector<vector<double> > _lightGlobal; /**< TODO: describe */
    vector<vector<double> > _lightAverage; /**< TODO: describe */

    std::map<string, Object::BaySolarFactorResult> _baySolarFactor; /**< TODO: describe */
    std::map<string, Object::SealingJointResult> _sealingJoint; /**< TODO: describe */

    Object::SealingJointVECResult *_sealingJointVEC; /**< TODO: describe */

    std::map<string, Object::MaximalTemperaturesResult*> _maximalTemperatures ; /**< TODO: describe */
    std::map<string, Object::ThermalBreakageResult*> _thermalBreakage; /**< TODO: describe */
    std::map<string, Object::StressAndDeflectionResult*> _stressAndDeflection; /**< TODO: describe */

    map<string, double> _obstaclesUValue; /**< TODO: describe */
    Object::ThermalBreakageSpecificResult *_thermalBreakageSpecific; /**< TODO: describe */
    Object::SlidingSashResult *_slidingSash; /**< TODO: describe */

    double _coefUGlass; /**< TODO: describe */
    double _coefUGlobal; /**< TODO: describe */

    double _hi673; /**< TODO: describe */
    double _tsi; /**< TODO: describe */
    double _tse; /**< TODO: describe */

    double _solarFactorGlass; /**< TODO: describe */
    double _solarFactorGlobal; /**< TODO: describe */

};

}
}
#endif // RESULT_H
