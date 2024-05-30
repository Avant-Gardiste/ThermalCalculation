#ifndef GLAZINGUVALUECLIMATICCONDITION_H
#define GLAZINGUVALUECLIMATICCONDITION_H

#include "climaticconditionwrapper_global.h"

#include <QObject>
#include <QMap>

#include "baseclimaticcondition.h"
#include "climatic.h"
#include "thermalobject.h"

/**
 * @brief
 *
 */
class CLIMATICCONDITIONWRAPPERSHARED_EXPORT GlazingUValueClimaticCondition : public BaseClimaticCondition
{
    Q_OBJECT
public:
    /**
     * @brief
     *
     * @param parent
     */
    explicit GlazingUValueClimaticCondition(BaseClimaticCondition *parent = 0);

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

    /**
     * @brief
     *
     * @return double
     */
    double hi673() const;
    /**
     * @brief
     *
     * @param hi673
     */
    void setHi673(double hi673);

signals:

private:
    double _hi673; /**< TODO: describe */
    QMap<QString, Climatic *> _climatic; /**< TODO: describe */

};

#endif // GLAZINGUVALUECLIMATICCONDITION_H
