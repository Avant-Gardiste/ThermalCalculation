#ifndef THERMALBREAKAGECLIMATICCONDITION_H
#define THERMALBREAKAGECLIMATICCONDITION_H

#include "climaticconditionwrapper_global.h"

#include <QObject>
#include <QMap>
#include <QtCore>
#include <QDir>
#include <QFile>

#include "baseclimaticcondition.h"
#include "climatic.h"
#include "thermalobject.h"
#include "object.h"

class CLIMATICCONDITIONWRAPPERSHARED_EXPORT ThermalBreakageClimaticCondition : public BaseClimaticCondition
{
    Q_OBJECT
public:
    explicit ThermalBreakageClimaticCondition(BaseClimaticCondition *parent = 0);

    virtual void specificClimaticCondition();
    virtual void normalClimaticCondition();
    virtual std::map<std::string, ClimateConditions::Climate*> getClimaticConditionCore();

    QMap<QString, Climatic *> climatic() const;
    void setClimatic(const QMap<QString, Climatic *> &climatic);

    int modeThermalBreakage() const;

    int getModeThermalBreakage() const;
    void setModeThermalBreakage(int mode);

private:
    double calculationFluxRegTrans( bool urbanZone, double incline, double altitude);
    double calculationHeRegTrans(double incline, Object::Season season);
    double calculationHiRegTrans(double incline, Object::Season season);

    double calculationTeMaxRegTrans(int numDepartment, QString zoneVH, QString zoneVA, QString zoneVE, bool zoneCotiere, double altitude, Object::Season season);
    double calculationTiRegTrans(Object::Season season);

    double calculationTeMinRegTrans(int numDepartment, QString zoneVH, QString zoneVA, QString zoneVE, bool zoneCotiere, double altitude, Object::Season season);
    double calculationFafluRegTrans(bool urbanZone, double incline, double altitude);

    double calculationFluxGS6(bool urbanZone, double inclinaison,double  altitude,Object::Orientation  orientation,Object::Season saison);
    double calculationHeGS6(double inclinaison, Object::Season saison);
    double calculationHiGS6(double inclinaison, Object::Season saison);
    double calculationTeMaxGS6(QString zoneVE, Object::Season saison, double altitude, Object::Orientation orientation, double  inclinaison);
    double calculationTiGS6(QString zoneVE, bool isAirCondition, bool isHeated, Object::Season saison, double inclinaison, Object::Orientation orientation, double altitude);
    double calculationTeMinGS6(int numDepartment, QString zoneVH, QString zoneVA, bool cityZone, Object::Season saison, double altitude);

    double calculationTiRegPerm(QString zoneVE, bool isAirCondition, bool isHeated, int saison, double inclinaison, int orientation, double altitude);
    double calculationFluxRegPerm(int saison, bool urbanZone, double inclinaison, double altitude, int orient);

    double calculationTeMin(int numDepartment, QString zoneVH, QString zoneVA, bool cityZone, double altitude);
    double calculationTeMax(bool cityZone, QString zoneVE, QString zoneVA, double altitude);

    double calculationFluxSlidingSash();

    QMap<QString, Climatic *> climaticConditionGS6();
    QMap<QString, Climatic *> climaticConditionsThermalBreakageSlidingSlash();

signals:

private:
    int _modeThermalBreakage;  // ? RegTrans : Reg Perm : sliding sash

    QMap<QString, Climatic *> _climatic;
};

#endif // THERMALBREAKAGECLIMATICCONDITION_H
