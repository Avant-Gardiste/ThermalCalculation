#ifndef INFORMATION_H
#define INFORMATION_H

#include "components_global.h"

#include <string>

using namespace std;

namespace VD6 {
namespace Common {

/**
 * @brief
 *
 */
class COMPONENTSSHARED_EXPORT Information
{
public:
    /**
     * @brief
     *
     */
    Information();
    /**
     * @brief
     *
     */
    ~Information();

    /**
     * @brief
     *
     * @return string
     */
    string getName() const;
    /**
     * @brief
     *
     * @param value
     */
    void setName(const string &value);

    /**
     * @brief
     *
     * @return string
     */
    string getDescription() const;
    /**
     * @brief
     *
     * @param value
     */
    void setDescription(const string &value);

    /**
     * @brief
     *
     * @return string
     */
    string getGlazing() const;
    /**
     * @brief
     *
     * @param value
     */
    void setGlazing(const string &value);

private:
    //Informations
    string name; /**< TODO: describe */
    string description; /**< TODO: describe */
    string glazing; /**< TODO: describe */

};

}
}

#endif // INFORMATION_H
