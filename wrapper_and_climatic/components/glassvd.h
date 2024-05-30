#ifndef GLASSVD_H
#define GLASSVD_H

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
class COMPONENTSSHARED_EXPORT GlassVD
{
public:
    /**
     * @brief
     *
     */
    GlassVD();
    /**
     * @brief
     *
     * @param clone
     */
    GlassVD(GlassVD *clone);

    /**
     * @brief
     *
     */
    ~GlassVD();

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
     * @return int
     */
    int getPositionSolarControlLayer() const;
    /**
     * @brief
     *
     * @param value
     */
    void setPositionSolarControlLayer(int value);

    /**
     * @brief
     *
     * @return int
     */
    int getPositionSelfCleaningLayer() const;
    /**
     * @brief
     *
     * @param value
     */
    void setPositionSelfCleaningLayer(int value);

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
     * @return std::vector<Spectral *>
     */
    std::vector<Spectral*> getSpectral() const;
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
    string getResearch() const;
    /**
     * @brief
     *
     * @param research
     */
    void setResearch(const string &research);

    /**
     * @brief
     *
     * @param another
     * @return bool
     */
    bool equal(GlassVD *another);

private:
    unsigned int _id; /**< TODO: describe */

    string _name; /**< TODO: describe */
    string _range; /**< TODO: describe */

    double _thicknessTotal; /**< TODO: describe */
    double _thickness1; /**< TODO: describe */
    double _thickness2; /**< TODO: describe */
    double _thickness3; /**< TODO: describe */
    double _thickness4; /**< TODO: describe */
    double _thickness5; /**< TODO: describe */

    double _tl; /**< TODO: describe */
    double _rl1; /**< TODO: describe */
    double _rl2; /**< TODO: describe */

    double _te; /**< TODO: describe */
    double _re1; /**< TODO: describe */
    double _emn1; /**< TODO: describe */
    double _re2; /**< TODO: describe */
    double _emn2; /**< TODO: describe */

    int _positionSolarControlLayer; /**< TODO: describe */
    int _positionSelfCleaningLayer; /**< TODO: describe */
    int _status; /**< TODO: describe */

    string _material; /**< TODO: describe */
    string _manufacturer; /**< TODO: describe */
    string _research; /**< TODO: describe */

    std::vector<Spectral*> _spectral; /**< TODO: describe */

};

}
}
#endif // GLASS_H
