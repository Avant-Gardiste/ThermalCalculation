#ifndef DEFINEGLASS_H
#define DEFINEGLASS_H

#include "components_global.h"

#include <string>
#include <vector>

#include "glassvd.h"
#include "gasgap.h"

using namespace std;

namespace VD6 {
namespace Common {

/**
 * @brief
 *
 */
class COMPONENTSSHARED_EXPORT DefineGlass
{
public:
    /**
     * @brief
     *
     */
    DefineGlass();
    /**
     * @brief
     *
     * @param clone
     */
    DefineGlass(DefineGlass *clone);
    /**
     * @brief
     *
     */
    virtual ~DefineGlass();

    /**
     * @brief
     *
     * @return bool
     */
    bool getSpectralIndex() const;
    /**
     * @brief
     *
     * @param value
     */
    void setSpectralIndex(bool value);

    /**
     * @brief
     *
     * @return vector<GlassVD *>
     */
    vector<GlassVD*> getGlasses() const;
    /**
     * @brief
     *
     * @param value
     */
    void setGlasses(const vector<GlassVD*> &value);
    /**
     * @brief
     *
     * @return int
     */
    int glassCount();
    /**
     * @brief
     *
     * @param index
     * @return GlassVD
     */
    GlassVD *glass(int index);

    /**
     * @brief
     *
     * @return int
     */
    int getNumberPane() const;
    /**
     * @brief
     *
     * @param value
     */
    void setNumberPane(int value);

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
     * @return vector<GasGap *>
     */
    vector<GasGap*> getGasGaps() const;
    /**
     * @brief
     *
     * @param gasGaps
     */
    void setGasGaps(const vector<GasGap*> &gasGaps);
    /**
     * @brief
     *
     * @return int
     */
    int gasGapCount();
    /**
     * @brief
     *
     * @param index
     * @return GasGap
     */
    GasGap *gasGap(int index);

    /**
     * @brief
     *
     * @return vector<int>
     */
    vector<int> getListId() const;
    /**
     * @brief
     *
     * @param listId
     */
    void setListId(const vector<int> &listId);

    /**
     * @brief
     *
     * @return int
     */
    int getNumberGasgap() const;
    /**
     * @brief
     *
     * @param numberGasgap
     */
    void setNumberGasgap(int numberGasgap);

    /**
     * @brief
     *
     * @return vector<int>
     */
    vector<int> getReverse() const;
    /**
     * @brief
     *
     * @param reverse
     */
    void setReverse(const vector<int> &reverse);

    /**
     * @brief
     *
     * @return bool
     */
    bool getGlazingPressureEquilibrated() const;
    /**
     * @brief
     *
     * @param glazingPressureEquilibrated
     */
    void setGlazingPressureEquilibrated(bool glazingPressureEquilibrated);

    /**
     * @brief
     *
     * @return vector<int>
     */
    vector<int> getNumCompositionGlass();
    /**
     * @brief
     *
     * @return bool
     */
    bool getExistVentilationGasGaps();

    /**
     * @brief
     *
     * @param another
     * @return bool
     */
    bool equal(DefineGlass *another);

private:
    //Glazing definition
    vector<int> _listId; /**< TODO: describe */
    bool _spectralIndex; /**< TODO: describe */
    vector<int> _reverse; /**< TODO: describe */

    vector<GlassVD*> _glasses; /**< TODO: describe */
    vector<GasGap*> _gasGaps; /**< TODO: describe */

    int _numberPane; /**< TODO: describe */
    int _numberGasgap; /**< TODO: describe */
    double _thicknessTotal; /**< TODO: describe */

    bool _glazingPressureEquilibrated; /**< TODO: describe */

};

}
}
#endif // DEFINE_GLASS_H
