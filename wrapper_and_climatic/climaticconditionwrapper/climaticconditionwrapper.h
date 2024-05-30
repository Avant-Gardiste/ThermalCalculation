#ifndef CLIMATICCONDITIONWRAPPER_H
#define CLIMATICCONDITIONWRAPPER_H

#include "climaticconditionwrapper_global.h"

#include <QObject>
#include <QVariantMap>

#include "baseclimaticcondition.h"

#include "projectcase.h"

#include "baysolarfactorclimaticconditions.h"
#include "glazingsolarfactorclimaticcondition.h"
#include "glazinguvalueclimaticcondition.h"
#include "tmaxsealingjointclimaticcondition.h"
#include "thermalbreakageclimaticcondition.h"

/**
 * @brief
 *
 */
class CLIMATICCONDITIONWRAPPERSHARED_EXPORT ClimaticConditionWrapper : public QObject
{
    Q_OBJECT

    Q_PROPERTY(BaseClimaticCondition *basedataClimatic READ baseData WRITE setBaseData NOTIFY baseDataChanged)
    Q_PROPERTY(ProjectCase *environments READ environments WRITE setEnvironments NOTIFY environmentsChanged)

    Q_PROPERTY(QVariantMap tmaxClimatics READ tmaxClimatics NOTIFY tmaxClimaticsChanged)

public:
    /**
     * @brief
     *
     */
    void updateBaseData();

    /**
     * @brief
     *
     * @return BaySolarFactorClimaticConditions
     */
    BaySolarFactorClimaticConditions *climateBaySolarFactor() const;
    /**
     * @brief
     *
     * @param climateBaySolarFactor
     */
    void setClimateBaySolarFactor(BaySolarFactorClimaticConditions *climateBaySolarFactor);

    /**
     * @brief
     *
     * @return GlazingSolarFactorClimaticCondition
     */
    GlazingSolarFactorClimaticCondition *climateGlazingSolarFactor() const;
    /**
     * @brief
     *
     * @param climateGlazingSolarFactor
     */
    void setClimateGlazingSolarFactor(GlazingSolarFactorClimaticCondition *climateGlazingSolarFactor);

    /**
     * @brief
     *
     * @return GlazingUValueClimaticCondition
     */
    GlazingUValueClimaticCondition *climateGlazingUValue() const;
    /**
     * @brief
     *
     * @param climateGlazingUValue
     */
    void setClimateGlazingUValue(GlazingUValueClimaticCondition *climateGlazingUValue);

    /**
     * @brief
     *
     * @return TmaxSealingJointClimaticCondition
     */
    TmaxSealingJointClimaticCondition *climateTmaxSealingJoint() const;
    /**
     * @brief
     *
     * @param climateTmaxSealingJoint
     */
    void setClimateTmaxSealingJoint(TmaxSealingJointClimaticCondition *climateTmaxSealingJoint);

    /**
     * @brief
     *
     * @return vector<Object::Orientation>
     */
    vector<Object::Orientation> orientations() const;
    /**
     * @brief
     *
     * @param orientations
     */
    void setOrientations(const vector<Object::Orientation> &orientations);

    /**
     * @brief
     *
     * @return vector<Object::Season>
     */
    vector<Object::Season> seasons() const;
    /**
     * @brief
     *
     * @param seasons
     */
    void setSeasons(const vector<Object::Season> &seasons);

    /**
     * @brief
     *
     * @return ThermalBreakageClimaticCondition
     */
    ThermalBreakageClimaticCondition *climateThermalBreakage() const;
    /**
     * @brief
     *
     * @param climateThermalBreakage
     */
    void setClimateThermalBreakage(ThermalBreakageClimaticCondition *climateThermalBreakage);

    /**
     * @brief
     *
     * @return BaseClimaticCondition
     */
    BaseClimaticCondition *baseData() const;
    /**
     * @brief
     *
     * @param baseData
     */
    void setBaseData(BaseClimaticCondition *baseData);

    /**
     * @brief
     *
     * @return ProjectCase
     */
    ProjectCase *environments() const;
    /**
     * @brief
     *
     * @param environments
     */
    void setEnvironments(ProjectCase *environments);

    /**
     * @brief
     *
     * @param mode
     */
    void setModeThermalBreakage(int mode);

    /**
     * @brief
     *
     * @return ClimaticConditionWrapper
     */
    static ClimaticConditionWrapper *currentClimatic();

    /**
     * @brief
     *
     * @return QVariantMap
     */
    QVariantMap tmaxClimatics() const;

private:
    static ClimaticConditionWrapper* _currentClimatic; /**< TODO: describe */

    static bool _initialized; /**< TODO: describe */

    /**
     * @brief
     *
     * @param parent
     */
    explicit ClimaticConditionWrapper(QObject *parent = 0);

    /**
     * @brief
     *
     * @param QMap<QString
     * @param >
     * @return bool
     */
    bool compareClimatic(QMap<QString, Climatic *>);
    /**
     * @brief
     *
     * @param a
     * @param b
     * @param threshold
     * @return bool
     */
    bool equalDouble(double a, double b, double threshold = 0.00001);

    /**
     * @brief
     *
     * @param data
     * @return QList<double>
     */
    QList<double> fromVariantList(QVariantList data);

signals:
    /**
     * @brief
     *
     */
    void baseDataChanged();
    /**
     * @brief
     *
     */
    void environmentsChanged();

    /**
     * @brief
     *
     */
    void orientationChanged();

    /**
     * @brief
     *
     */
    void climaticConditionChanged();
    /**
     * @brief
     *
     */
    void climaticConditionThermalChanged();

    /**
     * @brief
     *
     */
    void tmaxClimaticsChanged();

public slots:
    /**
     * @brief
     *
     */
    void onOrientationChanged();
    /**
     * @brief
     *
     */
    void calculationClimaticThermal();

    /**
     * @brief
     *
     */
    void calculateClimateCondition();

private:
    vector<Object::Orientation> _orientations; /**< TODO: describe */
    vector<Object::Season> _seasons; /**< TODO: describe */

    BaseClimaticCondition *_baseData; /**< TODO: describe */

    BaySolarFactorClimaticConditions *_climateBaySolarFactor; /**< TODO: describe */
    GlazingSolarFactorClimaticCondition *_climateGlazingSolarFactor; /**< TODO: describe */
    GlazingUValueClimaticCondition *_climateGlazingUValue; /**< TODO: describe */
    TmaxSealingJointClimaticCondition *_climateTmaxSealingJoint; /**< TODO: describe */
    ThermalBreakageClimaticCondition *_climateThermalBreakage; /**< TODO: describe */

    ProjectCase *_environments; /**< TODO: describe */

    QVariantMap _tmaxClimatics; /**< TODO: describe */

};

#endif // CLIMATICCONDITIONWRAPPER_H
