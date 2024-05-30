#ifndef TMAXSEALINGJOINTCLIMATICCONDITION_H
#define TMAXSEALINGJOINTCLIMATICCONDITION_H

#include "climaticconditionwrapper_global.h"

#include <QMap>
#include <QObject>

#include "climatic.h"
#include "thermalobject.h"

#include "baseclimaticcondition.h"

/**
 * @brief
 *
 */
class CLIMATICCONDITIONWRAPPERSHARED_EXPORT TmaxSealingJointClimaticCondition : public BaseClimaticCondition
{
    Q_OBJECT
public:
    /**
     * @brief
     *
     * @param parent
     */
    explicit TmaxSealingJointClimaticCondition(BaseClimaticCondition *parent = 0);

    /**
     * @brief
     *
     */
    virtual void specificClimaticCondition();
    /**
     * @brief
     *
     */
    virtual void normalClimaticCondition();
    /**
     * @brief
     *
     * @return std::map<std::string, ClimateConditions::Climate *>
     */
    virtual std::map<std::string, ClimateConditions::Climate*> getClimaticConditionCore();

    /**
     * @brief
     *
     * @return QMap<QString, Climatic *>
     */
    QMap<QString, Climatic *> climatic() const;
    /**
     * @brief
     *
     * @param QMap<QString
     * @param climatic
     */
    void setClimatic(const QMap<QString, Climatic *> &climatic);

private:
    /**
     * @brief
     *
     * @param urbanZone
     * @param incline
     * @param altitude
     * @param orientation
     * @param season
     * @return double
     */
    double calculationFlux(bool urbanZone,double incline,double altitude,Object::Orientation orientation,Object::Season season);
    /**
     * @brief
     *
     * @param incline
     * @param season
     * @return double
     */
    double calculationHe(double incline,Object::Season season);
    /**
     * @brief
     *
     * @param incline
     * @param season
     * @return double
     */
    double calculationHi(double incline, Object::Season season);
    /**
     * @brief
     *
     * @param zoneVE
     * @param season
     * @param altitude
     * @param orientation
     * @param inclinaison
     * @return double
     */
    double calculationTeMax(QString zoneVE, Object::Season season,double altitude, Object::Orientation orientation,double inclinaison);
    /**
     * @brief
     *
     * @param zoneVE
     * @param localClimate
     * @param isHeatedRoom
     * @param season
     * @param inclinaison
     * @param orientation
     * @param altitude
     * @return double
     */
    double calculationTi(QString zoneVE ,bool localClimate,bool isHeatedRoom,Object::Season season ,double inclinaison ,Object::Orientation orientation,double altitude);
    /**
     * @brief
     *
     * @param numDepartment
     * @param zoneVH
     * @param zoneVA
     * @param zoneCotiere
     * @param season
     * @param altitude
     * @return double
     */
    double calculationTeMin(int numDepartment, QString zoneVH, QString zoneVA, bool zoneCotiere, Object::Season season, double altitude);

    /**
     * @brief
     *
     * @param season
     * @param inclinaison
     * @param altitude
     * @return double
     */
    double calculationFluxStandard( Object::Season season  ,double inclinaison,double altitude);
    /**
     * @brief
     *
     * @param season
     * @param inclinaison
     * @return double
     */
    double calculationHeStandard( Object::Season season ,double inclinaison);
    /**
     * @brief
     *
     * @param season
     * @param inclinaison
     * @return double
     */
    double calculationHiStandard( Object::Season season ,double inclinaison);
    /**
     * @brief
     *
     * @param season
     * @param altitude
     * @return double
     */
    double calculationTeMaxStandard( Object::Season season ,double altitude);
    /**
     * @brief
     *
     * @param season
     * @param inclinaison
     * @return double
     */
    double calculationTiStandard( Object::Season season ,double inclinaison);
    /**
     * @brief
     *
     * @param season
     * @param altitude
     * @return double
     */
    double calculationTeMinStandard( Object::Season season ,double altitude);

private:
    QMap<QString, Climatic *> _climatic; /**< TODO: describe */
};

#endif // TMAXSEALINGJOINTCLIMATICCONDITION_H
