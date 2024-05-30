#ifndef MODULE_H
#define MODULE_H

#include "components_global.h"

#include <string>

using namespace std;

namespace VD6 {
namespace Common {

/**
 * @brief
 *
 */
class COMPONENTSSHARED_EXPORT Module
{
public:
    /**
     * @brief
     *
     */
    Module();
    /**
     * @brief
     *
     */
    ~Module();

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

private:
    string _name; /**< TODO: describe */
//    bool _status;

};

}
}

#endif // MODULE_H
