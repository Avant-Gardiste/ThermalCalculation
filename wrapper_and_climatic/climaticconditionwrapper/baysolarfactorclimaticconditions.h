#ifndef BAYSOLARFACTORCLIMATICCONDITIONS_H
#define BAYSOLARFACTORCLIMATICCONDITIONS_H

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
class CLIMATICCONDITIONWRAPPERSHARED_EXPORT BaySolarFactorClimaticConditions : public BaseClimaticCondition
{
    Q_OBJECT
public:
   /**
    * @brief
    *
    * @param parent
    */
   explicit BaySolarFactorClimaticConditions(BaseClimaticCondition *parent = 0);

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
    std::map<std::string, ClimateConditions::Climate *> getClimaticConditionCore();

    /**
     * @brief
     *
     * @return QMap<QString, Climatic *>
     */
    QMap<QString, Climatic *> getClimatic() const;
   /**
    * @brief
    *
    * @param QMap<QString
    * @param climatic
    */
   void setClimatic(const QMap<QString, Climatic *> &climatic);

signals:


private:
   QMap<QString, Climatic *> _climatic; /**< TODO: describe */
};

#endif // BAYSOLARFACTORCLIMATICCONDITIONS_H
