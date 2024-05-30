#ifndef GLAZINGSITUATION_H
#define GLAZINGSITUATION_H

#include "components_global.h"

#include <string>

using namespace std;

namespace VD6 {
namespace Common {

/**
 * @brief
 *
 */
class COMPONENTSSHARED_EXPORT GlazingSituation
{
public:
    /**
     * @brief
     *
     */
    GlazingSituation();
    /**
     * @brief
     *
     */
    ~GlazingSituation();
private:

    string name; /**< TODO: describe */

    double ce1WindNV65; /**< TODO: describe */
    double ci1WindNV65; /**< TODO: describe */
    double c1WindNV65; /**< TODO: describe */
    double ce2WindNV65; /**< TODO: describe */
    double ci2WindNV65; /**< TODO: describe */
    double c2WindNV65; /**< TODO: describe */

    double ELS1WindNV65; /**< TODO: describe */
    double ELU1WindNV65; /**< TODO: describe */
    double ELS2WindNV65; /**< TODO: describe */
    double ELU2WindNV65; /**< TODO: describe */

};

}
}

#endif // GLAZING_SITUATION_H
