#ifndef BASECLIMATICCONDITION_H
#define BASECLIMATICCONDITION_H

#include "climaticconditionwrapper_global.h"

#include <QObject>

#include <QMap>
#include <map>

#include "thermalobject.h"
#include "object.h"
#include "climateconditions.h"

using namespace VD6::Common;

/**
 * @brief
 *
 */
class CLIMATICCONDITIONWRAPPERSHARED_EXPORT BaseClimaticCondition : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief
     *
     * @param parent
     */
    explicit BaseClimaticCondition(QObject *parent = 0);

    /**
     * @brief
     *
     * @param parent
     */
    void updateData(BaseClimaticCondition *parent);

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
    virtual std::map<std::string, ClimateConditions::Climate *> getClimaticConditionCore();

    /**
     * @brief
     *
     * @param season
     * @param orientation
     * @param inclination
     * @return double
     */
    double approxVect(int season, int orientation, double inclination);

    /**
     * @brief
     *
     * @return QList<Object::Orientation>
     */
    QList<Object::Orientation> orientations() const;
    /**
     * @brief
     *
     * @param orientations
     */
    void setOrientations(const QList<Object::Orientation> &orientations);

    /**
     * @brief
     *
     * @return QList<Object::Season>
     */
    QList<Object::Season> seasons() const;
    /**
     * @brief
     *
     * @param seasons
     */
    void setSeasons(const QList<Object::Season> &seasons);

private:
    /**
     * @brief
     *
     * @param list
     * @return vector<double>
     */
    vector<double> convertVector(QList<double> list);

signals:
    /**
     * @brief
     *
     */
    void basedataClimaticChanged();

protected:
    QList<Object::Season> _seasons; /**< TODO: describe */
    QList<Object::Orientation> _orientations; /**< TODO: describe */

    QMap<QString, QList<double> > _fluxApproximately; /**< TODO: describe */

};

#endif // BASECLIMATICCONDITION_H
