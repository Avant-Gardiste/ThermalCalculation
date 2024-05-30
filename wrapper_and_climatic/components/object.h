#ifndef OBJECT_H
#define OBJECT_H

#include "components_global.h"

#include <math.h>
#include <vector>

#include "glassvd.h"
#include "blindvd.h"

#include "gasgap.h"
#include "obstaclevd.h"

#include "defineblind.h"
#include "defineglass.h"

#include "climateconditions.h"

using namespace std;

namespace VD6 {
namespace Common {

/**
 * @brief
 *
 */
class COMPONENTSSHARED_EXPORT Object
{
public:
    /**
     * @brief
     *
     */
    enum ModuleEnergy {
        Solar,
        Light
    };

    /**
     * @brief
     *
     */
    enum ObjectType {
        Glass,
        Blind,
        Obstacle,
        Film,
        PVB
    };

    /**
     * @brief
     *
     */
    enum ProjectType {
        OnlyGlass,
        WithBlind,
        WithObstacle,
        BlindAndObstacle
    };

    /**
     * @brief
     *
     */
    enum Orientation {
        North,
        NorthEast,
        East,
        SouthEast,
        South,
        SouthWest,
        West,
        NorthWest,
        StandardConditions
    };

    /**
     * @brief
     *
     */
    enum ObstacleType {
        Opaque,
        High,
        MidHigh,
        Low,
        Mullion,
        Dividing,
        Heater
    };

    /**
     * @brief
     *
     */
    enum Season {
        Spring,
        Summer,
        Autumn,
        Winter
    };

    /**
     * @brief
     *
     */
    enum GasType {
        Air,
        Mixed,
        Ventilation
    };

    /**
     * @brief
     *
     */
    enum VentilationType {
        Forced,
        Natural,
        Respiration
    };

    /**
     * @brief
     *
     */
    struct EnergyCharacteristics {
        double transmission[2]; /**< TODO: describe */
        double reflection[2]; /**< TODO: describe */
        double absorption[2]; /**< TODO: describe */
        double emissivity[2]; /**< TODO: describe */

        /**
         * @brief
         *
         */
        EnergyCharacteristics()
        {
            for (unsigned int i = 0; i <  2 ; i++) {
                transmission[i] = 0;
                reflection[i] = 0;
                absorption[i] = 0;
                emissivity[i] = 0;
            }
        }

        /**
         * @brief
         *
         * @param data
         */
        EnergyCharacteristics(vector<double> data)
        {
            transmission[0] = data[0];
            transmission[1] = data[0];
            reflection[0] = data[1];
            reflection[1] = data[2];
            absorption[0] = 1 - data[0] - data[1];
            absorption[1] = 1 - data[0] - data[2];
            emissivity[0] = 0;
            emissivity[1]  = 0;
        }

        /**
         * @brief
         *
         * @param tr
         * @param ref1
         * @param ref2
         */
        EnergyCharacteristics(double tr, double ref1, double ref2)
        {
            if ((tr <= 1) && (ref1 <= 1) && (ref2 <= 1)) {
                transmission[0] = tr;
                transmission[1] = tr;
                reflection[0] = ref1;
                reflection[1] = ref2;
            } else {
                transmission[0] = round(tr) / 100;
                transmission[1] = round(tr) / 100;
                reflection[0] = round(ref1) / 100;
                reflection[1] = round(ref2) / 100;
            }

            absorption[0] = 1 - transmission[0] - reflection[0];
            absorption[1] = 1 - transmission[1] - reflection[1];

            emissivity[0] = 0;
            emissivity[1]  = 0;
        }

        /**
         * @brief
         *
         * @param tr1
         * @param ref1
         * @param tr2
         * @param ref2
         */
        EnergyCharacteristics(double tr1, double ref1, double tr2, double ref2)
        {
            if ((tr1 <= 1) && (tr2 <= 1) && (ref1 <= 1) && (ref2 <= 1)) {
                transmission[0] = tr1;
                transmission[1] = tr2;
                reflection[0] = ref1;
                reflection[1] = ref2;
            } else {
                transmission[0] = round(tr1) / 100;
                transmission[1] = round(tr2) / 100;
                reflection[0] = round(ref1) / 100;
                reflection[1] = round(ref2) / 100;
            }

            absorption[0] = 1 - transmission[0] - reflection[0];
            absorption[1] = 1 - transmission[1] - reflection[1];

            emissivity[0] = 0;
            emissivity[1]  = 0;
        }
    };

    /**
     * @brief
     *
     */
    struct Energy {
        double transmission; /**< TODO: describe */
        double reflection; /**< TODO: describe */
        double absorption; /**< TODO: describe */

        /**
         * @brief
         *
         * @param tr
         * @param ref
         * @param abs
         */
        Energy(double tr, double ref, double abs)
        {
            this->transmission = tr;
            this->reflection = ref;
            this->absorption = abs;
        }

        /**
         * @brief
         *
         * @param a
         * @return bool operator
         */
        bool operator ==(const Energy &a) const
        {
            if (transmission == a.transmission && reflection == a.reflection && absorption == a.absorption) {
                return true;
            } else {
                return false;
            }
        }

        /**
         * @brief
         *
         * @param a
         * @return Energy operator
         */
        Energy operator -(const Energy &a) const
        {
            Energy temp(0, 0, 0);

            temp.transmission = transmission - a.transmission;
            temp.reflection = reflection - a.reflection;
            temp.absorption = absorption - a.absorption;

            return temp;
        }
    };

    /**
     * @brief
     *
     */
    struct EnergySpectral {
        unsigned int lamda; /**< TODO: describe */

        double transmission; /**< TODO: describe */
        double reflection; /**< TODO: describe */
        double absorption; /**< TODO: describe */

        vector<double> effectiveAbsorption; /**< TODO: describe */

        /**
         * @brief
         *
         */
        EnergySpectral()
        {
            lamda = 0;
            transmission = 0;
            reflection = 0;
            absorption = 0;
        }

        /**
         * @brief
         *
         * @param ld
         * @param energy
         * @param effAbs
         */
        EnergySpectral(unsigned int ld, vector<double > energy, vector<double> effAbs)
        {
            this->lamda = ld;
            this->transmission = energy[0];
            this->reflection = energy[1];
            this->absorption = energy[2];
            this->effectiveAbsorption = effAbs;
        }
    };

    /**
     * @brief
     *
     */
    struct InterpolationData {
        int lamda; /**< TODO: describe */

        double transmission; /**< TODO: describe */
        double reflection1; /**< TODO: describe */
        double reflection2; /**< TODO: describe */

        /**
         * @brief
         *
         * @param data
         * @return InterpolationData
         */
        InterpolationData convertFromSpectral(Spectral *data)
        {
            InterpolationData tmp;
            tmp.lamda = data->getLamda();
            tmp.transmission = data->getTe();
            tmp.reflection1 = data->getRe1();
            tmp.reflection2 = data->getRe2();
            return tmp;
        }

        /**
         * @brief
         *
         * @param lamda
         * @param trans
         * @param ref1
         * @param ref2
         */
        InterpolationData(int lamda, double trans, double ref1, double ref2)
        {
            this->lamda = lamda;
            this->transmission = trans;
            this->reflection1 = ref1;
            this->reflection2 = ref2;
        }

        /**
         * @brief
         *
         */
        InterpolationData()
        {
            lamda = transmission = reflection1 = reflection2 = 0;
        }

        /**
         * @brief
         *
         * @param a
         * @return InterpolationData operator
         */
        InterpolationData operator +(const InterpolationData &a) const
        {
            InterpolationData temp;
            temp.transmission = transmission + a.transmission;
            temp.reflection1 = reflection1 + a.reflection1;
            temp.reflection2 = reflection2 + a.reflection2;
            return temp;
        }

        /**
         * @brief
         *
         */
        void swapReflection()
        {
            double tmp;
            tmp = reflection1;
            reflection1 = reflection2;
            reflection2 = tmp;
        }

        /**
         * @brief
         *
         * @param l
         * @param trr
         */
        void setData(double l, vector<double> trr)
        {
            this->lamda = l;
            this->transmission = trr[0];
            this->reflection1 = trr[1];
            this->reflection2 = trr[2];
        }
    };

    /**
     * @brief
     *
     */
    struct ZoneClimate {
        int numDepartment; /**< TODO: describe */

        string nomDepartment; /**< TODO: describe */

        string zoneClimateVA; /**< TODO: describe */
        string zoneClimateVE; /**< TODO: describe */
        string zoneClimateVH; /**< TODO: describe */

    };

    /**
     * @brief
     *
     */
    struct Climate {
        double fi; /**< TODO: describe */
        double he; /**< TODO: describe */
        double hi; /**< TODO: describe */
        double te; /**< TODO: describe */
        double ti; /**< TODO: describe */

        /**
         * @brief
         *
         */
        Climate()
        {
            fi = 0;
            he = 0;
            hi = 0;
            te = 0;
            ti = 0;
        }

        /**
         * @brief
         *
         * @param fi
         * @param he
         * @param hi
         * @param te
         * @param ti
         */
        Climate(double fi, double he, double hi, double te, double ti)
        {
            this->fi = fi;
            this->he = he;
            this->hi = hi;
            this->te = te;
            this->ti = ti;
        }

        /**
         * @brief
         *
         * @param value
         */
        Climate(ClimateConditions::BaySolarFactor::Summer value)
        {
            fi = value.getFi();
            he = value.getHe();
            hi = value.getHi();
            te = value.getTe();
            ti = value.getTi();
        }

        /**
         * @brief
         *
         * @param value
         */
        Climate(ClimateConditions::BaySolarFactor::Winter value)
        {
            this->fi = value.getFi();
            this->he = value.getHe();
            this->hi = value.getHi();
            this->te = value.getTe();
            this->ti = value.getTi();
        }
    };

    /**
     * @brief
     *
     */
    struct ComponentsFlux {
        double _factorSolar; /**< TODO: describe */
        double _fluxCLO; /**< TODO: describe */
        double _fluxCONV; /**< TODO: describe */
        double _fluxAir; /**< TODO: describe */
        double _fluxGLO; /**< TODO: describe */

        /**
         * @brief
         *
         */
        ComponentsFlux()
        {
            _factorSolar = 0;
            _fluxCLO = 0;
            _fluxCONV = 0;
            _fluxAir = 0;
            _fluxGLO = 0;
        }
    };

    /**
     * @brief
     *
     */
    struct BaySolarFactorResult {
        double _glazingSolarFactor; /**< TODO: describe */
        double _correctedSolarFactor ; /**< TODO: describe */
        double _frameSolarFactor; /**< TODO: describe */
        double _baySolarFactor; /**< TODO: describe */
        double _shortWaveComponent; /**< TODO: describe */
        double _convectiveComponentGLO; /**< TODO: describe */
        double _airSpaceComponent ; /**< TODO: describe */

        /**
         * @brief
         *
         */
        BaySolarFactorResult()
        {
            _glazingSolarFactor = 0;
            _correctedSolarFactor = 0;
            _frameSolarFactor = 0;
            _baySolarFactor = 0;
            _shortWaveComponent = 0;
            _convectiveComponentGLO = 0;
            _airSpaceComponent = 0;
        }
    };

    /**
     * @brief
     *
     */
    struct SealingJointResult {
        vector<double> _tempratures; /**< TODO: describe */

        vector<double> _deflections; /**< TODO: describe */
        vector<double> _stresses; /**< TODO: describe */
        vector<double> _efforts; /**< TODO: describe */

        vector<double> _pressures; /**< TODO: describe */
        vector<double> _deltaPressures; /**< TODO: describe */

        double _effortSealingJoint; /**< TODO: describe */
        double _sealTemperature[2]; /**< TODO: describe */

        double _valHR; /**< TODO: describe */
        double _valHXA; /**< TODO: describe */
        double _valHe; /**< TODO: describe */
        double _valHi; /**< TODO: describe */

        double _ts; /**< TODO: describe */
    };

    /**
     * @brief
     *
     */
    struct MaximalTemperaturesResult {
        vector<double> _maximalTemperatures; /**< TODO: describe */
        double _temperaturesOfExit; /**< TODO: describe */

        /**
         * @brief
         *
         */
        MaximalTemperaturesResult()
        {
            _temperaturesOfExit = 0;
        }

        /**
         * @brief
         *
         * @param tmax
         * @param tExit
         */
        MaximalTemperaturesResult(vector<double> tmax, double tExit = 0)
        {
            this->_maximalTemperatures = tmax;
            this->_temperaturesOfExit = tExit;
        }
    };

    /**
     * @brief
     *
     */
    struct SealingJointVECResult {
        map<string, MaximalTemperaturesResult *> _resultMaximalTemperatures; /**< TODO: describe */
        map<string, vector<double> > _resultSealingJointVECPart1; /**< TODO: describe */
        map<string, vector<double> > _resultSealingJointVECPart2; /**< TODO: describe */
        map<string, vector<double> > _resultSealingJointVECPart3; /**< TODO: describe */
        map<string, vector<double> > _resultSealingJointVECSpecific; /**< TODO: describe */
    };

    /**
     * @brief
     *
     */
    struct ThermalBreakageResult {
        double _maxDifference; /**< TODO: describe */
        double _day; /**< TODO: describe */
        string _Hour; /**< TODO: describe */

        double _thermalMaxSun; /**< TODO: describe */
        double _tfRebate; /**< TODO: describe */
        double _thermalMinShadow; /**< TODO: describe */
    };

    //Frame data using for Themal with Obstacle || Ventilation Gas Gaps || 4 Glazing
    /**
     * @brief
     *
     */
    struct ThermalBreakageSpecificResult {
        map<string, vector<double> > _maximalTemperaturesPane; /**< TODO: describe */
        map<string, vector<double> > _maxDifference; /**< TODO: describe */
    };

    /**
     * @brief
     *
     */
    struct SlidingSashResult {
        vector <vector<double> > _completelyOpenFrame; /**< TODO: describe */
        vector <vector<double> > _partiallyOpenFrame; /**< TODO: describe */
    };

    /**
     * @brief
     *
     */
    struct StressAndDeflectionResult {
        vector<double> _pressureURS; /**< TODO: describe */
        vector<vector<vector<double> > > _stress; /**< TODO: describe */
        vector<double> _pressureSRS; /**< TODO: describe */
        vector<vector<double> > _deflection; /**< TODO: describe */
    };

    //module 1
    /**
     * @brief
     *
     */
    class ObjectSolarCharacteristics
    {
    public:
        /**
         * @brief
         *
         */
        ObjectSolarCharacteristics()
        {
            this->_blind = NULL;
            this->_obstacle = NULL;
        }

        /**
         * @brief
         *
         */
        ~ObjectSolarCharacteristics()
        {
            for (vector<GlassVD *>::iterator it = _listGlass.begin(); it != _listGlass.end(); it++) {
                delete (*it);
            }
            delete _blind;
            delete _obstacle;
        }

        vector<GlassVD *> _listGlass; /**< TODO: describe */
        BlindVD *_blind; /**< TODO: describe */
        ObstacleVD *_obstacle; /**< TODO: describe */
        int _positionBlindOrObs;// 0: extorior /**< TODO: describe */
    };

    //module 2
    /**
     * @brief
     *
     */
    class ObjectAnalysisSpectralSolar
    {
    public:
        /**
         * @brief
         *
         */
        ObjectAnalysisSpectralSolar()
        {
            _listGlass = vector<GlassVD *> {};
            _listGasGap = vector<GasGap *> {};
            _obstacles = vector<ObstacleVD *> {};

            _blind = NULL;
            _obstacle = NULL;
            _glassIsReversed = vector <int> ( 5, 0);

            _objectIsReversed = 0;
            _positionBlindOrObsj = -1;
            _spectralBlindIndex = 0;
        }

        /**
         * @brief
         *
         */
        ~ObjectAnalysisSpectralSolar() {
            for(vector<GlassVD *>::iterator it = _listGlass.begin(); it != _listGlass.end(); it++) {
                delete (*it);
            }

            for(vector<ObstacleVD *>::iterator it =  _obstacles.begin(); it !=  _obstacles.end(); it++) {
                delete (*it);
            }
            delete _blind;
            delete  _obstacle;
        }


        vector<GlassVD *> _listGlass; /**< TODO: describe */
        vector<GasGap *> _listGasGap; /**< TODO: describe */
        vector<ObstacleVD *> _obstacles; /**< TODO: describe */
        BlindVD *_blind; /**< TODO: describe */
        ObstacleVD *_obstacle ; /**< TODO: describe */
        vector <int> _glassIsReversed; /**< TODO: describe */

        int _objectIsReversed; /**< TODO: describe */
        int _positionBlindOrObsj; /**< TODO: describe */
        int _spectralBlindIndex; /**< TODO: describe */
    };
    //module 3

    /**
     * @brief
     *
     */
    class ObjectClimateData
    {
    public:
        /**
         * @brief
         *
         */
        ObjectClimateData()
        {
            _title = "";
            _latitude = 0.0;
            _altitude = 0.0;
            _climate = 0;
            _urbanArea = 0;
            _maxThermal = 0;
            _minThermal = 0;
            _slope  = 0.0;
            _albedo = 0.0;
            _amplitude = 0.0;
        }

        //parameter input
        string _title;          //", "Lille" /**< TODO: describe */
        double _latitude;        //50.5666656494141 /**< TODO: describe */
        double _altitude;        //100 /**< TODO: describe */
        int _climate;           //", 2 /**< TODO: describe */
        int _urbanArea;         //", 2 /**< TODO: describe */
        double _maxThermal;      //" 36 /**< TODO: describe */
        double _minThermal;      // "T min" - 18 /**< TODO: describe */
        double _slope;           //" 90 /**< TODO: describe */
        double _albedo;          //" 0.2 what is this? /**< TODO: describe */
        double _amplitude;       //" 10 /**< TODO: describe */

    };

    //Module 4
    /**
     * @brief
     *
     */
    class ObjectBaySolarFactor
    {
    public:
        //function
        /**
         * @brief
         *
         */
        ObjectBaySolarFactor()
        {
            _incline = 0;
            _height = 0;
            _width = 0;

            _blind = NULL;
            _glass = NULL;

            _absorptionEffectiveGlobal = vector<double> {};
            _absorptionEffectiveGlass = vector<double> {};

            _solarAverage = vector<double> {};

            _spectralIndex  = 0;
            _spectralIndexBlind = false;

            _glazingBareInterior = false;
            _bayUfFrame = 0;
            _bayAbsFrame = 0;
            _sigma = 0;

            _climates = map<string, ClimateConditions::Climate*> {};
        }

        /**
         * @brief
         *
         */
        ~ObjectBaySolarFactor()
        {
            delete _blind;
            delete _glass;

            for(map<string, ClimateConditions::Climate*>::iterator it =  _climates.begin(); it !=  _climates.end(); it++) {
                delete (*it).second;
            }
        }

        double _incline; /**< TODO: describe */
        double _height; /**< TODO: describe */
        double _width; /**< TODO: describe */

        DefineBlind *_blind; /**< TODO: describe */
        DefineGlass *_glass; /**< TODO: describe */

        vector<double> _absorptionEffectiveGlobal; /**< TODO: describe */
        vector<double> _absorptionEffectiveGlass; /**< TODO: describe */

        vector<double>_solarAverage; /**< TODO: describe */

        int _spectralIndex; /**< TODO: describe */
        bool _spectralIndexBlind; /**< TODO: describe */

        bool _glazingBareInterior; /**< TODO: describe */
        double _bayUfFrame; /**< TODO: describe */
        double _bayAbsFrame; /**< TODO: describe */
        double _sigma; /**< TODO: describe */

        map<string, ClimateConditions::Climate*> _climates; /**< TODO: describe */

    };

    //module 5
    /**
     * @brief
     *
     */
    class ObjectSealingJoint
    {
    public:
        /**
         * @brief
         *
         */
        ObjectSealingJoint()
        {
            _incline                  = 0;
            _height                   = 0;
            _width                    = 0;

            _heightManufacturing       = 0;
            _projectAltitude          = 0;
            _manufacturingTemprature  = 0;
            _pressureManufacturing    = 0;

            _certifiedWorkingStress   = 0;
            _wedgingGlazing           = -1;

            _temperatureCondition     = -1;
            _temperatureGlass         = 0;
            _tempratureFrame          = 0;
            _gammad                   = 0;

            _pressureEquilibratedEnabled  = false;
            _coefExternalTradeHE      = false;
            _sideOfGlass              = false;
            _stickFrame               = false;

            _existencePart1           = false;
            _existencePart2           = false;
            _existencePart3           = false;
            _existenceSpecific        = false;

            _blind = NULL;
            _glass = NULL;

            _orientations = vector<Object::Orientation> {};
        }
        /**
         * @brief
         *
         */
        ~ObjectSealingJoint() {
            delete _blind;
            delete _glass;

            for (map<string, ClimateConditions::Climate *>::iterator it = _climates.begin();it != _climates.begin(); it++) {
                delete (*it).second;
            }

        }

        double _incline; /**< TODO: describe */
        double _height; /**< TODO: describe */
        double _width; /**< TODO: describe */

        double _heightManufacturing; /**< TODO: describe */
        double _projectAltitude; /**< TODO: describe */

        double _manufacturingTemprature; /**< TODO: describe */
        double _pressureManufacturing; /**< TODO: describe */

        DefineBlind *_blind; /**< TODO: describe */
        DefineGlass *_glass; /**< TODO: describe */

        vector<double> _absorptionEffectiveGlobal; /**< TODO: describe */
        vector<double> _absorptionEffectiveGlass; /**< TODO: describe */

        map<string, ClimateConditions::Climate *> _climates; /**< TODO: describe */
        vector<Object::Orientation> _orientations; /**< TODO: describe */

        vector<double> _glazingPart1; /**< TODO: describe */
        vector<double> _glazingPart2; /**< TODO: describe */
        vector<double> _glazingPart3; /**< TODO: describe */
        vector<double> _glazingPartSpecific; /**< TODO: describe */

        int _wedgingGlazing; /**< TODO: describe */
        int _temperatureCondition; /**< TODO: describe */

        double _certifiedWorkingStress; /**< TODO: describe */
        double _temperatureGlass; /**< TODO: describe */
        double _tempratureFrame; /**< TODO: describe */
        double _gammad; /**< TODO: describe */

        bool _coefExternalTradeHE; /**< TODO: describe */
        bool _pressureEquilibratedEnabled; /**< TODO: describe */
        bool _sideOfGlass; /**< TODO: describe */
        bool _stickFrame; /**< TODO: describe */

        bool _existencePart1; /**< TODO: describe */
        bool _existencePart2; /**< TODO: describe */
        bool _existencePart3; /**< TODO: describe */
        bool _existenceSpecific; /**< TODO: describe */
    };

    //module 6
    /**
     * @brief
     *
     */
    class ObjectThermalBreakage
    {
    public:
        /**
         * @brief
         *
         */
        ObjectThermalBreakage()
        {
            _spectralAnalysis = false;
            _incline = 0;
            _height = 0;
            _width = 0;

            _hightManufacturing = 0;
            _projectAltitude = 0;
            _manufacturingTemprature = 0;
            _pressureManufacturing = 0;

            _menuiserie = 0;
            _menuiserieMaterial = 0;

            _absorptionEffectiveGlobal = vector<double> {};
            _absorptionEffectiveGlass = vector<double> {};

            _climate = map<string, ClimateConditions::Climate *> {};
            _orientations = vector<Object::Orientation> {};

            _glass = NULL;
            _blind = NULL;
        }

        bool _spectralAnalysis; /**< TODO: describe */
        double _incline; /**< TODO: describe */
        double _height; /**< TODO: describe */
        double _width; /**< TODO: describe */

        double _hightManufacturing; /**< TODO: describe */
        double _projectAltitude; /**< TODO: describe */
        double _manufacturingTemprature; /**< TODO: describe */
        double _pressureManufacturing; /**< TODO: describe */

        int _menuiserie; /**< TODO: describe */
        int _menuiserieMaterial; /**< TODO: describe */

        vector<double> _absorptionEffectiveGlobal; /**< TODO: describe */
        vector<double> _absorptionEffectiveGlass; /**< TODO: describe */

        map<string, ClimateConditions::Climate *> _climate; /**< TODO: describe */
        vector<Object::Orientation> _orientations; /**< TODO: describe */

        DefineBlind *_blind; /**< TODO: describe */
        DefineGlass *_glass; /**< TODO: describe */
    };

    //module Uvalue b
    /**
     * @brief
     *
     */
    class ObjectUValue
    {
    public:
        /**
         * @brief
         *
         */
        ObjectUValue() {
            _incline = 0;
            _height = 0;
            _width = 0;

            _glass = NULL;
            _blind = NULL;

            _absorptionEffectiveGlass = vector<double> {};
            _absorptionEffectiveGlobal = vector<vector<double> >{};
            _climate = NULL;

            _numberSpandrel = 0;
            _isIndoorsBackup = false;

            _obstacle = vector<ObstacleVD *> {};
        }

        /**
         * @brief
         *
         */
        virtual ~ObjectUValue() {
            delete _climate;
            delete _glass;
            delete _blind;

            for (vector<ObstacleVD *>::iterator it = _obstacle.begin(); it != _obstacle.end(); it++) {
                delete *it;
            }
        }

        double _incline; /**< TODO: describe */
        double _height; /**< TODO: describe */
        double _width; /**< TODO: describe */

        DefineGlass *_glass; /**< TODO: describe */
        DefineBlind *_blind; /**< TODO: describe */

        vector<double> _absorptionEffectiveGlass; /**< TODO: describe */
        vector<vector<double> > _absorptionEffectiveGlobal; /**< TODO: describe */

        ClimateConditions::Climate *_climate; /**< TODO: describe */

        //Obstacle
        int   _numberSpandrel; /**< TODO: describe */
        bool _isIndoorsBackup; /**< TODO: describe */

        vector<ObstacleVD *> _obstacle; /**< TODO: describe */
    };

    // module 7
    /**
     * @brief
     *
     */
    class ObjectGlazingSolarFactor
    {
    public:
        //function
        /**
         * @brief
         *
         */
        ObjectGlazingSolarFactor()
        {
            _incline = 0;
            _height = 0;
            _width = 0;

            _blind = NULL;
            _glass = NULL;

            _climate = NULL;

            _absorptionEffectiveGlobal = vector<double> {};
            _absorptionEffectiveGlass = vector<double> {};

            _spectralIndex = 0;
        }

        /**
         * @brief
         *
         */
        ~ObjectGlazingSolarFactor() {
            delete _blind;
            delete _glass;
            delete _climate;
        }

        double _incline; /**< TODO: describe */
        double _height; /**< TODO: describe */
        double _width; /**< TODO: describe */

        DefineBlind *_blind; /**< TODO: describe */
        DefineGlass *_glass; /**< TODO: describe */

        ClimateConditions::Climate* _climate; /**< TODO: describe */

        vector<double> _absorptionEffectiveGlobal; /**< TODO: describe */
        vector<double> _absorptionEffectiveGlass; /**< TODO: describe */

        int _spectralIndex; /**< TODO: describe */
    };

    /**
     * @brief
     *
     */
    class ObjectMaximalTemperatures
    {
    public:
        /**
         * @brief
         *
         */
        ObjectMaximalTemperatures()
        {
            _incline = 0;
            _height = 0;
            _width = 0;

            _blind = NULL;
            _glass = NULL;

            _numberSeason = 3; //default
            _isThermal = false;

            _opaqueEnabled = false;
            _varHe = false;

            _existenceBlind = false;
            _existenceObstacle = false;
            _slidingSashExistence = false;
            _isIndoorsBackup = false;

            _absorptionEffectiveGlass = vector<double> {};
            _absorptionEffectiveGlobal = vector<vector<double> >{} ;

            _climates = map<string, ClimateConditions::Climate *> {};

            _orientations = vector<Object::Orientation> {};
            _seasons = vector<Object::Season> {};
        }

        /**
         * @brief
         *
         */
        ~ObjectMaximalTemperatures() {
            delete _blind;
            delete _glass;

            for (vector<ObstacleVD *>::iterator it = _obstacles.begin(); it != _obstacles.end(); it++) {
                delete (*it);
            }

            for (map<string, ClimateConditions::Climate *>::iterator it = _climates.begin(); it != _climates.end(); it++) {
                delete (*it).second;
            }
        }

        double _incline; /**< TODO: describe */
        double _height; /**< TODO: describe */
        double _width; /**< TODO: describe */

        DefineBlind *_blind; /**< TODO: describe */
        DefineGlass *_glass; /**< TODO: describe */
        vector<ObstacleVD *> _obstacles; /**< TODO: describe */

        int _numberSeason; /**< TODO: describe */
        bool _isThermal; /**< TODO: describe */

        bool _opaqueEnabled; /**< TODO: describe */
        bool _varHe; /**< TODO: describe */
        bool _existenceBlind; /**< TODO: describe */
        bool _existenceObstacle; /**< TODO: describe */
        bool _slidingSashExistence; /**< TODO: describe */
        bool _isIndoorsBackup; /**< TODO: describe */

        vector<double> _absorptionEffectiveGlass; /**< TODO: describe */
        vector<vector<double> > _absorptionEffectiveGlobal; /**< TODO: describe */

        map<string, ClimateConditions::Climate *> _climates; /**< TODO: describe */

        vector<Object::Orientation> _orientations; /**< TODO: describe */
        vector<Object::Season> _seasons; /**< TODO: describe */
    };

    /**
     * @brief
     *
     */
    class ObjectMaximalTemperaturesHeater : public ObjectMaximalTemperatures
    {

    public  :
        /**
         * @brief
         *
         */
        ObjectMaximalTemperaturesHeater()
        {
            ObjectMaximalTemperatures();

            _widthRadiator = 0;
            _heightRadiator = 0;
            _distanceToGlass = 0;
            _emissivityRadiator = 0;
            _temperatureRadiator = 0;
        }

        /**
         * @brief
         *
         * @param parent
         */
        ObjectMaximalTemperaturesHeater(ObjectMaximalTemperatures *parent)
        {
            _incline = parent->_incline;
            _height = parent->_height;
            _width = parent->_width;

            _blind = parent->_blind;
            _glass = parent->_glass;

            _numberSeason = parent->_numberSeason; //default
            _isThermal = parent->_isThermal;

            _opaqueEnabled = parent->_opaqueEnabled;
            _varHe = parent->_varHe;

            _existenceBlind = parent->_existenceBlind;
            _existenceObstacle = parent->_existenceObstacle;
            _slidingSashExistence = parent->_slidingSashExistence;
            _isIndoorsBackup = parent->_isIndoorsBackup;

            _absorptionEffectiveGlass = parent->_absorptionEffectiveGlass;
            _absorptionEffectiveGlobal = parent->_absorptionEffectiveGlobal;

            _climates = parent->_climates;

            _orientations = parent->_orientations;
            _seasons = parent->_seasons;

            _widthRadiator = 0;
            _heightRadiator = 0;
            _distanceToGlass = 0;
            _emissivityRadiator = 0;
            _temperatureRadiator = 0;
        }

        double _widthRadiator; /**< TODO: describe */
        double _heightRadiator; /**< TODO: describe */
        double _distanceToGlass; /**< TODO: describe */
        double _emissivityRadiator; /**< TODO: describe */
        double _temperatureRadiator; /**< TODO: describe */
    };

    /**
     * @brief
     *
     */
    class ObjectStressesAndDeflections
    {
    public:
        /**
         * @brief
         *
         */
        ObjectStressesAndDeflections()
        {
            _incline = 0;
            _height = 0;
            _width = 0;

            _hightManufacturing = 0;
            _projectAltitude = 0;
            _manufacturingTemprature = 0;
            _pressureManufacturing = 0;

            _spectralIndex = 0;
            _numberSills = 0;
            _freeLength = 0;

            _absorptionEffectiveGlobal = vector<double> {};
            _absorptionEffectiveGlass = vector<double> {};

            _glazingPart1 = vector<double> {};
            _glazingPart2 = vector<double> {};
            _glazingPart3 = vector<double> {};

            _glazingPartSpecific = vector<double> {};

            _certifiedWorkingStress = 0;
            _wedgingGlazing = 0;
            _temperatureCondition = 0;
            _temperatureGlass = 0;
            _tempratureFrame = 0;
            _gammad = 0;

            _climateConditions = map<string, ClimateConditions::Climate *> {};
            _orientations = vector<Object::Orientation> {};

            _blind = NULL;
            _glass = NULL;

            _coefExternalTradeHE = false;
            _glazingPressureEquilibrated = false;
            _sideOfGlass = false;
            _stickFrame = false;

            _existencePart1 = false;
            _existencePart2 = false;
            _existencePart3 = false;
            _existenceSpecific = false;

            _existenceCurrentPart = false;
            _existenceRoofEdgesLower500 = false;
            _existenceRoofEdgesHigher500 = false;
            _existenceNearObstacle = false;
            _existenceRedans = false;
            _existenceTieUpsets = false;
            _existenceOverHangingRoof = false;
            _existenceSpecificNV65 = false;
            _existenceSpecificNV84 = false;

            _valueCurrentPart = vector<double> {};
            _valueRoofEdgesLower500 = vector<double> {};
            _valueRoofEdgesHigher500 = vector<double> {};
            _valueNearObstacle = vector<double> {};
            _valueRedans = vector<double> {};
            _valueTieUpsets = vector<double> {};
            _valueOverHangingRoof = vector<double> {};
            _valueSpecificNV65 = vector<double> {};
            _valueSpecificNV84 = vector<double> {};
        }

        double _incline; /**< TODO: describe */
        double _height; /**< TODO: describe */
        double _width; /**< TODO: describe */

        double _hightManufacturing; /**< TODO: describe */
        double _projectAltitude; /**< TODO: describe */
        double _manufacturingTemprature; /**< TODO: describe */
        double _pressureManufacturing; /**< TODO: describe */

        int _spectralIndex; /**< TODO: describe */
        int _numberSills; /**< TODO: describe */
        int _freeLength; /**< TODO: describe */

        vector<double> _absorptionEffectiveGlobal; /**< TODO: describe */
        vector<double> _absorptionEffectiveGlass; /**< TODO: describe */

        vector<double> _glazingPart1; /**< TODO: describe */
        vector<double> _glazingPart2; /**< TODO: describe */
        vector<double> _glazingPart3; /**< TODO: describe */

        vector<double> _glazingPartSpecific; /**< TODO: describe */

        double _certifiedWorkingStress; /**< TODO: describe */
        int _wedgingGlazing; /**< TODO: describe */
        int _temperatureCondition; /**< TODO: describe */
        double _temperatureGlass; /**< TODO: describe */
        double _tempratureFrame; /**< TODO: describe */
        double _gammad; /**< TODO: describe */

        map<string, ClimateConditions::Climate *> _climateConditions; /**< TODO: describe */
        vector<Object::Orientation> _orientations; /**< TODO: describe */

        DefineBlind *_blind; /**< TODO: describe */
        DefineGlass *_glass; /**< TODO: describe */

        bool _coefExternalTradeHE; /**< TODO: describe */
        bool _glazingPressureEquilibrated; /**< TODO: describe */
        bool _sideOfGlass; /**< TODO: describe */
        bool _stickFrame; /**< TODO: describe */

        bool _existencePart1; /**< TODO: describe */
        bool _existencePart2; /**< TODO: describe */
        bool _existencePart3; /**< TODO: describe */
        bool _existenceSpecific; /**< TODO: describe */

        bool _existenceCurrentPart; /**< TODO: describe */
        bool _existenceRoofEdgesLower500; /**< TODO: describe */
        bool _existenceRoofEdgesHigher500; /**< TODO: describe */
        bool _existenceNearObstacle; /**< TODO: describe */
        bool _existenceRedans; /**< TODO: describe */
        bool _existenceTieUpsets; /**< TODO: describe */
        bool _existenceOverHangingRoof; /**< TODO: describe */
        bool _existenceSpecificNV65; /**< TODO: describe */
        bool _existenceSpecificNV84; /**< TODO: describe */

        vector<double> _valueCurrentPart; /**< TODO: describe */
        vector<double> _valueRoofEdgesLower500; /**< TODO: describe */
        vector<double> _valueRoofEdgesHigher500; /**< TODO: describe */
        vector<double> _valueNearObstacle; /**< TODO: describe */
        vector<double> _valueRedans; /**< TODO: describe */
        vector<double> _valueTieUpsets; /**< TODO: describe */
        vector<double> _valueOverHangingRoof; /**< TODO: describe */
        vector<double> _valueSpecificNV65; /**< TODO: describe */
        vector<double> _valueSpecificNV84; /**< TODO: describe */
    };

};

}
}

#endif // OBJECT_H
