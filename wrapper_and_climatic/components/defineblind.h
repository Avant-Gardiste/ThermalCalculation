#ifndef DEFINEBLIND_H
#define DEFINEBLIND_H

#include "components_global.h"

#include <string>
#include <vector>

#include "blindvd.h"

using namespace std;

namespace VD6 {
namespace Common {

/**
 * @brief
 *
 */
class COMPONENTSSHARED_EXPORT DefineBlind
{
public:
    /**
     * @brief
     *
     */
    DefineBlind();
    /**
     * @brief
     *
     * @param clone
     */
    DefineBlind(DefineBlind *clone);
    /**
     * @brief
     *
     */
    virtual ~DefineBlind();

    /**
     * @brief
     *
     * @return bool
     */
    bool spectralIndex() const;
    /**
     * @brief
     *
     * @param spectralIndex
     */
    void setSpectralIndex(bool spectralIndex);

    /**
     * @brief
     *
     * @return int
     */
    int numberBlind() const;
    /**
     * @brief
     *
     * @param numberBlind
     */
    void setNumberBlind(int numberBlind);

    /**
     * @brief
     *
     * @return double
     */
    double getDistanceBlindGlazing() const;
    /**
     * @brief
     *
     * @param value
     */
    void setDistanceBlindGlazing(double value);

    /**
     * @brief
     *
     * @return int
     */
    int getPositionBlind() const;
    /**
     * @brief
     *
     * @param positionBlind
     */
    void setPositionBlind(int positionBlind);

    /**
     * @brief
     *
     * @return int
     */
    int getTypeMovementBlind() const;
    /**
     * @brief
     *
     * @param typeMovementBlind
     */
    void setTypeMovementBlind(int typeMovementBlind);

    /**
     * @brief
     *
     * @return double
     */
    double getTopSpace() const;
    /**
     * @brief
     *
     * @param value
     */
    void setTopSpace(double value);

    /**
     * @brief
     *
     * @return double
     */
    double getLateralSpace() const;
    /**
     * @brief
     *
     * @param lateralSpace
     */
    void setLateralSpace(double lateralSpace);

    /**
     * @brief
     *
     * @return double
     */
    double getBottomSpace() const;
    /**
     * @brief
     *
     * @param bottomSpace
     */
    void setBottomSpace(double bottomSpace);

    /**
     * @brief
     *
     * @return double
     */
    double getTth() const;
    /**
     * @brief
     *
     * @param tth
     */
    void setTth(double tth);

//    bool getTypeBlind() const;
//    void setTypeBlind(bool typeBlind);

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
     * @return vector<BlindVD *>
     */
    vector<BlindVD *> getBlinds() const;
    /**
     * @brief
     *
     * @param blinds
     */
    void setBlinds(const vector<BlindVD *> &blinds);
    /**
     * @brief
     *
     * @return int
     */
    int blindCount();
    /**
     * @brief
     *
     * @param index
     * @return BlindVD
     */
    BlindVD *blind(int index);

    /**
     * @brief
     *
     * @return vector<int>
     */
    vector<int> getReverse() const;
    /**
     * @brief
     *
     * @param value
     */
    void setReverse(const vector<int> &value);

    /**
     * @brief
     *
     * @return double
     */
    double getSlatsDistance() const;
    /**
     * @brief
     *
     * @param slatsDistance
     */
    void setSlatsDistance(double slatsDistance);

    /**
     * @brief
     *
     * @return double
     */
    double getSlatsWidth() const;
    /**
     * @brief
     *
     * @param slatsWidth
     */
    void setSlatsWidth(double slatsWidth);

    /**
     * @brief
     *
     * @return double
     */
    double getInfraredTransmission() const;
    /**
     * @brief
     *
     * @param infraredTransmission
     */
    void setInfraredTransmission(double infraredTransmission);

    /**
     * @brief
     *
     * @return int
     */
    int getPositionSlats() const;
    /**
     * @brief
     *
     * @param positionSlats
     */
    void setPositionSlats(int positionSlats);

    /**
     * @brief
     *
     * @return string
     */
    string getColorSlats() const;
    /**
     * @brief
     *
     * @param colorSlats
     */
    void setColorSlats(const string &colorSlats);

    /**
     * @brief
     *
     * @return vector<double>
     */
    vector<double> getCharacteristicsBlindVenetian() const;
    /**
     * @brief
     *
     * @param characteristicsBlindVenetian
     */
    void setCharacteristicsBlindVenetian(const vector<double> &characteristicsBlindVenetian);

    /**
     * @brief
     *
     * @return int
     */
    int getPositionVentilationToBlind() const;
    /**
     * @brief
     *
     * @param positionVentilationToBlind
     */
    void setPositionVentilationToBlind(int positionVentilationToBlind);

    /**
     * @brief
     *
     * @return double
     */
    double getPorosity() const;
    /**
     * @brief
     *
     * @param porosity
     */
    void setPorosity(double porosity);

    /**
     * @brief
     *
     * @return bool
     */
    bool getSpectralIndex() const;

    /**
     * @brief
     *
     * @param another
     * @return bool
     */
    bool equal(DefineBlind *another);

private:
    vector<int> _listId; /**< TODO: describe */
    bool _spectralIndex; /**< TODO: describe */

    vector<int> _reverse; /**< TODO: describe */
    int _numberBlind; /**< TODO: describe */

    double _distanceBlindGlazing; /**< TODO: describe */
    int _positionVentilationToBlind; /**< TODO: describe */
    int _positionBlind; /**< TODO: describe */
    int _typeMovementBlind;//0:Fixes,1:Movable /**< TODO: describe */

    double _topSpace; /**< TODO: describe */
    double _lateralSpace; /**< TODO: describe */
    double _bottomSpace; /**< TODO: describe */
    //bool _typeBlind;//FALSE:Toile,TRUE:Venitien

    double _tth; /**< TODO: describe */

    //if venitien
    double _slatsDistance; /**< TODO: describe */
    double _slatsWidth; /**< TODO: describe */
    double _infraredTransmission; /**< TODO: describe */
    double _porosity; /**< TODO: describe */

    int _positionSlats; /**< TODO: describe */
    string _colorSlats; /**< TODO: describe */

    vector<BlindVD*> _blinds; /**< TODO: describe */
    vector<double> _characteristicsBlindVenetian; /**< TODO: describe */

};

}
}
#endif // DEFINEBLIND_H
