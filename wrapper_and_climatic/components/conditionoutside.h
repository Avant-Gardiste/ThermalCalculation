#ifndef CONDITIONOUTSIDE_H
#define CONDITIONOUTSIDE_H

#include "components_global.h"

#include <string>

using namespace std;

namespace VD6 {
namespace Common {

/**
 * @brief
 *
 */
class COMPONENTSSHARED_EXPORT ConditionOutside
{
public:
    /**
     * @brief
     *
     */
    ConditionOutside();
    /**
     * @brief
     *
     */
    ~ConditionOutside();

private:
    string name; /**< TODO: describe */
    double factor; /**< TODO: describe */
    double normalSnowPressure; /**< TODO: describe */
    double extremeSnowPressure; /**< TODO: describe */
    double accidentSnowPressure; /**< TODO: describe */

};

}
}
#endif // CONDITIONOUTSIDE_H
