#ifndef PVBVD_H
#define PVBVD_H

#include "components_global.h"

#include <string>
#include <vector>

#include "spectral.h"

using namespace std;

namespace VD6 {
namespace Common {

/**
 * @brief
 *
 */
class COMPONENTSSHARED_EXPORT PVBVD
{
public:
    /**
     * @brief
     *
     */
    PVBVD();
    /**
     * @brief
     *
     */
    ~PVBVD();

    /**
     * @brief
     *
     * @return unsigned int
     */
    unsigned int getId() const;
    /**
     * @brief
     *
     * @param value
     */
    void setId(unsigned int value);

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
    string getRange() const;
    /**
     * @brief
     *
     * @param value
     */
    void setRange(const string &value);

    /**
     * @brief
     *
     * @return double
     */
    double getThicknessTotal() const;
    /**
     * @brief
     *
     * @param value
     */
    void setThicknessTotal(double value);

    /**
     * @brief
     *
     * @return double
     */
    double getThickness1() const;
    /**
     * @brief
     *
     * @param value
     */
    void setThickness1(double value);

    /**
     * @brief
     *
     * @return double
     */
    double getThickness2() const;
    /**
     * @brief
     *
     * @param value
     */
    void setThickness2(double value);

    /**
     * @brief
     *
     * @return double
     */
    double getThickness3() const;
    /**
     * @brief
     *
     * @param value
     */
    void setThickness3(double value);

    /**
     * @brief
     *
     * @return double
     */
    double getThickness4() const;
    /**
     * @brief
     *
     * @param value
     */
    void setThickness4(double value);

    /**
     * @brief
     *
     * @return double
     */
    double getThickness5() const;
    /**
     * @brief
     *
     * @param value
     */
    void setThickness5(double value);

    /**
     * @brief
     *
     * @return double
     */
    double getTl() const;
    /**
     * @brief
     *
     * @param value
     */
    void setTl(double value);

    /**
     * @brief
     *
     * @return double
     */
    double getRl1() const;
    /**
     * @brief
     *
     * @param value
     */
    void setRl1(double value);

    /**
     * @brief
     *
     * @return double
     */
    double getRl2() const;
    /**
     * @brief
     *
     * @param value
     */
    void setRl2(double value);

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
    double getEmn1() const;
    /**
     * @brief
     *
     * @param value
     */
    void setEmn1(double value);

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
     * @return double
     */
    double getEmn2() const;
    /**
     * @brief
     *
     * @param value
     */
    void setEmn2(double value);

    /**
     * @brief
     *
     * @return int
     */
    int getStatus() const;
    /**
     * @brief
     *
     * @param value
     */
    void setStatus(int value);

    /**
     * @brief
     *
     * @return string
     */
    string getMaterial() const;
    /**
     * @brief
     *
     * @param value
     */
    void setMaterial(const string &value);

    /**
     * @brief
     *
     * @return string
     */
    string getManufacturer() const;
    /**
     * @brief
     *
     * @param value
     */
    void setManufacturer(const string &value);

    /**
     * @brief
     *
     * @return std::vector<Spectral *>
     */
    std::vector<Spectral *> getSpectral() const;
    /**
     * @brief
     *
     * @param value
     */
    void setSpectral(const std::vector<Spectral *> &value);

private:
    unsigned int id; /**< TODO: describe */

    string name; /**< TODO: describe */
    string range; /**< TODO: describe */

    double thicknessTotal; /**< TODO: describe */
    double thickness1; /**< TODO: describe */
    double thickness2; /**< TODO: describe */
    double thickness3; /**< TODO: describe */
    double thickness4; /**< TODO: describe */
    double thickness5; /**< TODO: describe */

    double tl; /**< TODO: describe */
    double rl1; /**< TODO: describe */
    double rl2; /**< TODO: describe */

    double te; /**< TODO: describe */
    double re1; /**< TODO: describe */
    double emn1; /**< TODO: describe */
    double re2; /**< TODO: describe */
    double emn2; /**< TODO: describe */

    int status; /**< TODO: describe */

    string material; /**< TODO: describe */
    string manufacturer; /**< TODO: describe */
    std::vector<Spectral*> spectral; /**< TODO: describe */

};

}
}

#endif // PVB_H
