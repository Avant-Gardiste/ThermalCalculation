#ifndef GLAZINGSOLARFACTORCLIMATICCONDITION_H
#define GLAZINGSOLARFACTORCLIMATICCONDITION_H

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
class CLIMATICCONDITIONWRAPPERSHARED_EXPORT GlazingSolarFactorClimaticCondition : public BaseClimaticCondition
{
    Q_OBJECT
public:
    /**
     * @brief
     *
     * @param parent
     */
    explicit GlazingSolarFactorClimaticCondition(BaseClimaticCondition *parent = 0);

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

    QMap<QString, Climatic *> _climatic; /**< TODO: describe */
};

#endif // GLAZINGSOLARFACTORCLIMATICCONDITION_H
