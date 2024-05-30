/*
 onlyGlass         ---calculate characteristic energy when sunlight go through N glass
 withBlind         ---calculate characteristics energy when sunlight go through N glass and blind
                          ---This depend position of blind in list object about glass and blind
 withObstacle   ---It same this withBlind, difference is obstacle position,it always at the last in list object.
*/

#ifndef SOLARCHARIACTERISTICS_H
#define SOLARCHARIACTERISTICS_H

#include "solarcharacteristics_global.h"

#include <vector>
#include <cmath>
#include <memory>
#include <iostream>

#include "object.h"

using namespace std;
using namespace VD6::Common;

namespace VD6 {
namespace Calculation {

/**
 * @brief
 *
 */
class SOLARCHARIACTERISTICSSHARED_EXPORT SolarCharacteristics
{
public:
    /**
     * @brief
     *
     */
    SolarCharacteristics();
    /**
     * @brief
     *
     */
    ~SolarCharacteristics();

    /**
     * @brief
     *
     * @param numGlass
     * @param glass1Data
     * @param glass2Data
     * @param glass3Data
     * @param glass4Data
     * @param blindExistence
     * @param positionBlind
     * @param blindData
     * @param obstacleExistence
     * @param obstaclesExistence
     * @param dataObstacles
     * @param mode
     * @param slidingSashEnable
     * @return vector<vector<double> >
     */
    vector<vector<double> >execute(int numGlass,
                                   GlassVD *glass1Data,
                                   GlassVD *glass2Data ,
                                   GlassVD *glass3Data,
                                   GlassVD *glass4Data,
                                   bool blindExistence,
                                   int positionBlind,
                                   BlindVD *blindData,
                                   bool obstacleExistence,
                                   vector<bool> obstaclesExistence,
                                   vector<ObstacleVD *> dataObstacles,
                                   Object::ModuleEnergy mode, bool slidingSashEnable = false);

    /**
     * @brief
     *
     * @param glass1Data
     * @param glass2Data
     * @param glass3Data
     * @param glass4Data
     * @param gas1
     * @param gas2
     * @param gas3
     * @param numGlass
     * @param mode
     */
    void setGasAndGlassThickness(GlassVD *glass1Data, GlassVD *glass2Data, GlassVD *glass3Data, GlassVD *glass4Data,
                GasGap *gas1, GasGap *gas2, GasGap *gas3, int numGlass, Object::ModuleEnergy mode);

    /**
     * @brief
     *
     * @param pos
     */
    void setPostisionObject(int &pos);
    /**
     * @brief
     *
     * @param characteristic
     * @param type
     */
    void setCharacteristicsObject(vector<VD6::Common::Object::EnergyCharacteristics> characteristic, Object::ProjectType type);
    /**
     * @brief
     *
     * @param data
     * @param type
     */
    void setDataObject(Object::ObjectSolarCharacteristics *data, Object::ModuleEnergy type);

    /**
     * @brief
     *
     * @return unsigned int
     */
    unsigned int getPositionObject();

    /**
     * @brief
     *
     * @param type
     * @return vector<double>
     */
    vector<double> calculationEnergy(Object::ProjectType type);
    /**
     * @brief
     *
     * @param TRA
     * @param type
     * @return vector<double>
     */
    vector<double> characteristicsEnergy(vector<VD6::Common::Object::EnergyCharacteristics> TRA, Object::ProjectType type);

    /**
     * @brief
     *
     * @return vector<double>
     */
    vector<double> getEnergyGlobal();
    /**
     * @brief
     *
     * @return vector<double>
     */
    vector<double> getEffectiveAbsorption();

    /**
     * @brief
     *
     * @return VD6::Common::Object::Energy
     */
    VD6::Common::Object::Energy getGlobalEnergy();

    /**
     * @brief
     *
     * @return vector<Object::EnergyCharacteristics>
     */
    vector<Object::EnergyCharacteristics> getListGlass() const;
    /**
     * @brief
     *
     * @param value
     */
    void setListGlass(const vector<Object::EnergyCharacteristics> &value);

    /**
     * @brief
     *
     * @return vector<Object::EnergyCharacteristics>
     */
    vector<Object::EnergyCharacteristics> getListBlind() const;
    /**
     * @brief
     *
     * @param value
     */
    void setListBlind(const vector<Object::EnergyCharacteristics> &value);

    /**
     * @brief
     *
     * @return vector<Object::EnergyCharacteristics>
     */
    vector<Object::EnergyCharacteristics> getListObstacle() const;
    /**
     * @brief
     *
     * @param value
     */
    void setListObstacle(const vector<Object::EnergyCharacteristics> &value);

    /**
     * @brief
     *
     * @return int
     */
    int getPositionBlindOrObs() const;
    /**
     * @brief
     *
     * @param value
     */
    void setPositionBlindOrObs(int value);

    bool isOpaque = false; /**< TODO: describe */

    /**
     * @brief
     *
     * @param qi
     * @param qe
     * @param result
     * @param listGas
     * @param listGlass
     */
    void calculateQiQe(double &qi, double &qe, vector<double> result, vector<GasGap *> listGas, vector<GlassVD *> listGlass);
    vector<double> SolarCharacteristics::calculateHs(vector<GasGap *> listGas, vector<GlassVD *> listGlass);
    double getincline() const;
    void setIncline(double incline); ////b1206 EN673

private:
    /**
     * @brief
     *
     * @param glass
     * @param object
     * @param posObj
     * @return vector<VD6::Common::Object::EnergyCharacteristics>
     */
    vector<VD6::Common::Object::EnergyCharacteristics> calculationTRAEMValues(vector<VD6::Common::Object::EnergyCharacteristics> glass, Object::EnergyCharacteristics object, unsigned int posObj);

    /**
     * @brief
     *
     * @param TRAEM
     * @return vector<vector<double> >
     */
    vector<vector<double> > establishMatrix(vector<VD6::Common::Object::EnergyCharacteristics> TRAEM);
    /**
     * @brief
     *
     * @param matrixCX
     * @return vector<double>
     */
    vector<double> resolutionSystem(vector<vector<double> > &matrixCX);

private:
    vector<double> _effectiveReflection; /**< TODO: describe */

    double _globalTransmission; /**< TODO: describe */
    double _globalReflection; /**< TODO: describe */
    double _globalAbsorption; /**< TODO: describe */
    double _incline;

    vector<double> _effectiveAbsorption; /**< TODO: describe */

    vector<Object::EnergyCharacteristics> _listGlass; /**< TODO: describe */
    vector<GasGap *> _listGas; /**< TODO: describe */
    vector<GlassVD *> _listGlassVD; /**< TODO: describe */
    Object::EnergyCharacteristics _listBlind; /**< TODO: describe */
    Object::EnergyCharacteristics _listObstacle; /**< TODO: describe */

    unsigned int _positionBlindOrObs; /**< TODO: describe */

    bool _isOpaque; /**< TODO: describe */
};

}
}

#endif // SolarCharacteristics_H
