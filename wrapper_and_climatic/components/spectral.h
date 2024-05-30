#ifndef SPECTRAL_H
#define SPECTRAL_H

#include "components_global.h"

#include <string>

using namespace std;

namespace VD6 {
namespace Common {

/**
 * @brief
 *
 */
class COMPONENTSSHARED_EXPORT Spectral
{
public:
    /**
     * @brief
     *
     */
    Spectral();
    /**
     * @brief
     *
     * @param clone
     */
    Spectral(Spectral *clone);
    /**
     * @brief
     *
     */
    ~Spectral();

    /**
     * @brief
     *
     * @param clone
     * @return Spectral *operator
     */
    Spectral *operator=(Spectral *clone);

    /**
     * @brief
     *
     * @return int
     */
    int getId() const;
    /**
     * @brief
     *
     * @param value
     */
    void setId(int value);

    /**
     * @brief
     *
     * @return int
     */
    int getLamda() const;
    /**
     * @brief
     *
     * @param value
     */
    void setLamda(int value);

    /**
     * @brief
     *
     * @return double
     */
    double getTe() const;
    /**
     * @brief
     *
     * @param value
     */
    void setTe(double value);

    /**
     * @brief
     *
     * @return double
     */
    double getRe1() const;
    /**
     * @brief
     *
     * @param value
     */
    void setRe1(double value);

    /**
     * @brief
     *
     * @return double
     */
    double getRe2() const;
    /**
     * @brief
     *
     * @param value
     */
    void setRe2(double value);

    /**
     * @brief
     *
     * @param another
     * @return bool
     */
    bool equal(Spectral *another);

private:
    int _id; /**< TODO: describe */

    int _lamda; /**< TODO: describe */

    double _te; /**< TODO: describe */
    double _re1; /**< TODO: describe */
    double _re2; /**< TODO: describe */

};

}
}

#endif // SPECTRAL_H
