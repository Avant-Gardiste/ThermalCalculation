#ifndef BLINDVD_H
#define BLINDVD_H

#include "components_global.h"

#include <string>
#include <vector>

#include "spectral.h"

using namespace std;
using namespace VD6::Common;

namespace VD6 {
namespace Common {

/**
 * @brief
 *
 */
class COMPONENTSSHARED_EXPORT BlindVD
{
public:
    /**
     * @brief
     *
     */
    BlindVD();
    /**
     * @brief
     *
     * @param clone
     */
    BlindVD(BlindVD *clone);
    /**
     * @brief
     *
     */
    ~BlindVD();

    /**
     * @brief
     *
     * @return unsigned int
     */
    unsigned int getId() const;
    /**
     * @brief
     *
     * @param id
     */
    void setId(unsigned int id);

    /**
     * @brief
     *
     * @return string
     */
    string getName() const;
    /**
     * @brief
     *
     * @param name
     */
    void setName(const string &name);

    /**
     * @brief
     *
     * @return string
     */
    string getRange() const;
    /**
     * @brief
     *
     * @param range
     */
    void setRange(const string &range);

    /**
     * @brief
     *
     * @return double
     */
    double getTl() const;
    /**
     * @brief
     *
     * @param tl
     */
    void setTl(double tl);

    /**
     * @brief
     *
     * @return double
     */
    double getRl1() const;
    /**
     * @brief
     *
     * @param rl1
     */
    void setRl1(double rl1);

    /**
     * @brief
     *
     * @return double
     */
    double getRl2() const;
    /**
     * @brief
     *
     * @param rl2
     */
    void setRl2(double rl2);

    /**
     * @brief
     *
     * @return double
     */
    double getTe1() const;
    /**
     * @brief
     *
     * @param te
     */
    void setTe1(double te);

    /**
     * @brief
     *
     * @return double
     */
    double getRe1() const;
    /**
     * @brief
     *
     * @param re1
     */
    void setRe1(double re1);

    /**
     * @brief
     *
     * @return double
     */
    double getEmn1() const;
    /**
     * @brief
     *
     * @param emn1
     */
    void setEmn1(double emn1);

    /**
     * @brief
     *
     * @return double
     */
    double getTe2() const;
    /**
     * @brief
     *
     * @param te
     */
    void setTe2(double te);

    /**
     * @brief
     *
     * @return double
     */
    double getRe2() const;
    /**
     * @brief
     *
     * @param re2
     */
    void setRe2(double re2);

    /**
     * @brief
     *
     * @return double
     */
    double getEmn2() const;
    /**
     * @brief
     *
     * @param emn2
     */
    void setEmn2(double emn2);

    /**
     * @brief
     *
     * @return double
     */
    double getThickness() const;
    /**
     * @brief
     *
     * @param thickness
     */
    void setThickness(double thickness);

    /**
     * @brief
     *
     * @return double
     */
    double getDensity() const;
    /**
     * @brief
     *
     * @param density
     */
    void setDensity(double density);

    /**
     * @brief
     *
     * @return double
     */
    double getOpennessFactor() const;
    /**
     * @brief
     *
     * @param opennessFactor
     */
    void setOpennessFactor(double opennessFactor);

    /**
     * @brief
     *
     * @return string
     */
    string getHexColor() const;
    /**
     * @brief
     *
     * @param hexColor
     */
    void setHexColor(const string &hexColor);

    /**
     * @brief
     *
     * @return string
     */
    string getFireRating() const;
    /**
     * @brief
     *
     * @param fireRating
     */
    void setFireRating(const string &fireRating);

    /**
     * @brief
     *
     * @return int
     */
    int getStatus() const;
    /**
     * @brief
     *
     * @param status
     */
    void setStatus(int status);

    /**
     * @brief
     *
     * @return string
     */
    string getMaterial() const;
    /**
     * @brief
     *
     * @param material
     */
    void setMaterial(const string &material);

    /**
     * @brief
     *
     * @return string
     */
    string getManufacturer() const;
    /**
     * @brief
     *
     * @param manufacturer
     */
    void setManufacturer(const string &manufacturer);

    /**
     * @brief
     *
     * @return std::vector<Spectral *>
     */
    std::vector<Spectral *> getSpectral() const;
    /**
     * @brief
     *
     * @param spectral
     */
    void setSpectral(const std::vector<Spectral*> &spectral);
    /**
     * @brief
     *
     * @return int
     */
    int spectralCount();
    /**
     * @brief
     *
     * @param index
     * @return Spectral
     */
    Spectral *spectral(int index);

    /**
     * @brief
     *
     * @return string
     */
    string getType() const;
    /**
     * @brief
     *
     * @param type
     */
    void setType(const string &type);

    /**
     * @brief
     *
     * @return int
     */
    int typeIndex() const;
    /**
     * @brief
     *
     * @param typeIndex
     */
    void setTypeIndex(int typeIndex);

    /**
     * @brief
     *
     * @param another
     * @return bool
     */
    bool equal(BlindVD *another);

private:
    unsigned int _id; /**< TODO: describe */

    string _type; /**< TODO: describe */
    string _name; /**< TODO: describe */
    string _range; /**< TODO: describe */

    int _typeIndex; /**< TODO: describe */

    double _tl; /**< TODO: describe */
    double _rl1; /**< TODO: describe */
    double _rl2; /**< TODO: describe */

    double _te1; /**< TODO: describe */
    double _re1; /**< TODO: describe */
    double _emn1; /**< TODO: describe */

    double _te2; /**< TODO: describe */
    double _re2; /**< TODO: describe */
    double _emn2; /**< TODO: describe */

    double _thickness; /**< TODO: describe */
    double _density; /**< TODO: describe */
    double _opennessFactor; /**< TODO: describe */

    string _hexColor; /**< TODO: describe */
    string _fireRating; /**< TODO: describe */
    int _status;//0: intergrated, 1: intergrated and spectral, 2 :spectral /**< TODO: describe */

    string _material; /**< TODO: describe */
    string _manufacturer; /**< TODO: describe */

    std::vector<Spectral *> _spectral; /**< TODO: describe */

};

}
}
#endif // BLIND_H
