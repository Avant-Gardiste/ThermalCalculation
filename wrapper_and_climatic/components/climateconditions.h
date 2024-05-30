#ifndef CLIMATECONDITIONS_H
#define CLIMATECONDITIONS_H

#include "components_global.h"

#include <map>
#include <vector>

using namespace std;

namespace VD6 {
namespace Common{

/**
 * @brief
 *
 */
class COMPONENTSSHARED_EXPORT ClimateConditions
{
public:
    /**
     * @brief
     *
     */
    ClimateConditions();

    /**
     * @brief
     *
     */
    class SolarFactor
    {
    private:
        double _fi; /**< TODO: describe */
        double _he; /**< TODO: describe */
        double _hi; /**< TODO: describe */
        double _te; /**< TODO: describe */
        double _ti; /**< TODO: describe */
    };

    /**
     * @brief
     *
     */
    class COMPONENTSSHARED_EXPORT UValue
    {
    public:
        /**
         * @brief
         *
         * @return double
         */
        double fi() const;
        /**
         * @brief
         *
         * @param fi
         */
        void setFi(double fi);

        /**
         * @brief
         *
         * @return double
         */
        double he() const;
        /**
         * @brief
         *
         * @param he
         */
        void setHe(double he);

        /**
         * @brief
         *
         * @return double
         */
        double hi() const;
        /**
         * @brief
         *
         * @param hi
         */
        void setHi(double hi);

        /**
         * @brief
         *
         * @return double
         */
        double te() const;
        /**
         * @brief
         *
         * @param te
         */
        void setTe(double te);

        /**
         * @brief
         *
         * @return double
         */
        double ti() const;
        /**
         * @brief
         *
         * @param ti
         */
        void setTi(double ti);

    private:
        double _fi; /**< TODO: describe */
        double _he; /**< TODO: describe */
        double _hi; /**< TODO: describe */
        double _te; /**< TODO: describe */
        double _ti; /**< TODO: describe */
    };

    /**
     * @brief
     *
     */
    class COMPONENTSSHARED_EXPORT Climate
    {
    public:
        /**
         * @brief
         *
         */
        Climate();
        /**
         * @brief
         *
         * @param clone
         */
        Climate(Climate *clone);

        /**
         * @brief
         *
         * @param fi
         * @param he
         * @param hi
         * @param te
         * @param ti
         */
        Climate(double fi,double he,double hi,double te,double ti);

        /**
         * @brief
         *
         * @return double
         */
        double getFi() const;
        /**
         * @brief
         *
         * @param fi
         */
        void setFi(double fi);

        /**
         * @brief
         *
         * @return double
         */
        double getHe() const;
        /**
         * @brief
         *
         * @param he
         */
        void setHe(double he);

        /**
         * @brief
         *
         * @return double
         */
        double getHi() const;
        /**
         * @brief
         *
         * @param hi
         */
        void setHi(double hi);

        /**
         * @brief
         *
         * @return double
         */
        double getTe() const;
        /**
         * @brief
         *
         * @param te
         */
        void setTe(double te);

        /**
         * @brief
         *
         * @return double
         */
        double getTi() const;
        /**
         * @brief
         *
         * @param ti
         */
        void setTi(double ti);

        /**
         * @brief
         *
         * @return double
         */
        double getTeMin() const;
        /**
         * @brief
         *
         * @param teMin
         */
        void setTeMin(double teMin);

        /**
         * @brief
         *
         * @return double
         */
        double getFaflu() const;
        /**
         * @brief
         *
         * @param faflu
         */
        void setFaflu(double faflu);

        /**
         * @brief
         *
         * @param another
         * @return bool
         */
        bool equal(Climate *another);

    private:
        double _fi; /**< TODO: describe */
        double _he; /**< TODO: describe */
        double _hi; /**< TODO: describe */
        double _te; /**< TODO: describe */
        double _ti; /**< TODO: describe */
        double _teMin; /**< TODO: describe */
        double _faflu; /**< TODO: describe */
    };

    /**
     * @brief
     *
     */
    class COMPONENTSSHARED_EXPORT BaySolarFactor
    {
    public:
        /**
         * @brief
         *
         */
        class COMPONENTSSHARED_EXPORT Summer
        {
        public:
            /**
             * @brief
             *
             * @return double
             */
            double getFi() const;
            /**
             * @brief
             *
             * @param fi
             */
            void setFi(double fi);

            /**
             * @brief
             *
             * @return double
             */
            double getHe() const;
            /**
             * @brief
             *
             * @param he
             */
            void setHe(double he);

            /**
             * @brief
             *
             * @return double
             */
            double getHi() const;
            /**
             * @brief
             *
             * @param hi
             */
            void setHi(double hi);

            /**
             * @brief
             *
             * @return double
             */
            double getTe() const;
            /**
             * @brief
             *
             * @param te
             */
            void setTe(double te);

            /**
             * @brief
             *
             * @return double
             */
            double getTi() const;
            /**
             * @brief
             *
             * @param ti
             */
            void setTi(double ti);

        private:
            double _fi; /**< TODO: describe */
            double _he; /**< TODO: describe */
            double _hi; /**< TODO: describe */
            double _te; /**< TODO: describe */
            double _ti; /**< TODO: describe */
        };

        /**
         * @brief
         *
         */
        class COMPONENTSSHARED_EXPORT Winter
        {
        public:
            /**
             * @brief
             *
             * @return double
             */
            double getFi() const;
            /**
             * @brief
             *
             * @param fi
             */
            void setFi(double fi);

            /**
             * @brief
             *
             * @return double
             */
            double getHe() const;
            /**
             * @brief
             *
             * @param he
             */
            void setHe(double he);

            /**
             * @brief
             *
             * @return double
             */
            double getHi() const;
            /**
             * @brief
             *
             * @param hi
             */
            void setHi(double hi);

            /**
             * @brief
             *
             * @return double
             */
            double getTe() const;
            /**
             * @brief
             *
             * @param te
             */
            void setTe(double te);

            /**
             * @brief
             *
             * @return double
             */
            double getTi() const;
            /**
             * @brief
             *
             * @param ti
             */
            void setTi(double ti);

        private:
            double _fi; /**< TODO: describe */
            double _he; /**< TODO: describe */
            double _hi; /**< TODO: describe */
            double _te; /**< TODO: describe */
            double _ti; /**< TODO: describe */
        };

    public:
        /**
         * @brief
         *
         */
        BaySolarFactor(){
            _glazingBareInterior = false;
        }

        /**
         * @brief
         *
         * @return bool
         */
        bool getGlazingBareInterior() const;
        /**
         * @brief
         *
         * @param glazingBareInterior
         */
        void setGlazingBareInterior(bool glazingBareInterior);


        /**
         * @brief
         *
         * @return Summer
         */
        Summer *getSummer() const;
        /**
         * @brief
         *
         * @param summer
         */
        void setSummer(Summer *summer);

        /**
         * @brief
         *
         * @return Winter
         */
        Winter *getWinter() const;
        /**
         * @brief
         *
         * @param winter
         */
        void setWinter(Winter *winter);

        /**
         * @brief
         *
         * @return double
         */
        double getSigma() const;
        /**
         * @brief
         *
         * @param sigma
         */
        void setSigma(double sigma);

        /**
         * @brief
         *
         * @return double
         */
        double getBayAbsFrame() const;
        /**
         * @brief
         *
         * @param bayAbsFrame
         */
        void setBayAbsFrame(double bayAbsFrame);

        /**
         * @brief
         *
         * @return double
         */
        double getBayUfFrame() const;
        /**
         * @brief
         *
         * @param bayUfFrame
         */
        void setBayUfFrame(double bayUfFrame);

    private:
        bool _glazingBareInterior; /**< TODO: describe */
        double _bayUfFrame; /**< TODO: describe */
        double _bayAbsFrame; /**< TODO: describe */
        double _sigma; /**< TODO: describe */
        Summer* _summer; /**< TODO: describe */
        Winter* _winter; /**< TODO: describe */
    };

    /**
     * @brief
     *
     */
    class COMPONENTSSHARED_EXPORT MaximalTemperaturesSealingJoint
    {
    public:
        /**
         * @brief
         *
         */
        MaximalTemperaturesSealingJoint();

        /**
         * @brief
         *
         * @return map<string, Climate *>
         */
        map<string, Climate*> getMaximalTemperaturesSealingJoint() const;
        /**
         * @brief
         *
         * @param map<string
         * @param value
         */
        void setMaximalTemperaturesSealingJoint(map<string, Climate*> value);

    private:
        map<string, Climate*> _maximalTemperaturesSealingJoint; /**< TODO: describe */
    };

    /**
     * @brief
     *
     */
    class COMPONENTSSHARED_EXPORT ThermalBreakage
    {
    public:
        /**
         * @brief
         *
         * @return map<string, Climate *>
         */
        map<string, Climate*> getClimateConditions() const;
        /**
         * @brief
         *
         * @param map<string
         * @param value
         */
        void setClimateConditions(const map<string, Climate*> &value);

    private:
        map<string,ClimateConditions::Climate*> climateConditions; /**< TODO: describe */
    };

    /**
     * @brief
     *
     */
    class COMPONENTSSHARED_EXPORT GlazingSolarFactor
    {
    public:

        /**
         * @brief
         *
         * @return Climate
         */
        Climate getGlazingSolarFactor() const;
        /**
         * @brief
         *
         * @param glazingSolarFactor
         */
        void setGlazingSolarFactor(const Climate &glazingSolarFactor);

    private:
        Climate _climateConditions; /**< TODO: describe */
    };

    /**
     * @brief
     *
     */
    class COMPONENTSSHARED_EXPORT TmaxSealingJoint
    {
    private:
        vector<double> _value; /**< TODO: describe */
    };

    /**
     * @brief
     *
     */
    class COMPONENTSSHARED_EXPORT ThermalDymamic
    {
    private:
        vector<double> _value; /**< TODO: describe */
    };

    /**
     * @brief
     *
     */
    class COMPONENTSSHARED_EXPORT ThermalStatic
    {
    private:
        vector<double> _value; /**< TODO: describe */
    };

    /**
     * @brief
     *
     * @return SolarFactor
     */
    SolarFactor *solarFactor() const;
    /**
     * @brief
     *
     * @param solarFactor
     */
    void setSolarFactor(SolarFactor *solarFactor);

    /**
     * @brief
     *
     * @return UValue
     */
    UValue *uValue() const;
    /**
     * @brief
     *
     * @param uValue
     */
    void setUValue(UValue *uValue);

    /**
     * @brief
     *
     * @return BaySolarFactor
     */
    BaySolarFactor *getBaySolarFactor() const;
    /**
     * @brief
     *
     * @param baySolarFactor
     */
    void setBaySolarFactor(BaySolarFactor *baySolarFactor);

    /**
     * @brief
     *
     * @return MaximalTemperaturesSealingJoint
     */
    MaximalTemperaturesSealingJoint *getMaximalTemperaturesSealingJoint() const;
    /**
     * @brief
     *
     * @param maximalTemperaturesSealingJoint
     */
    void setMaximalTemperaturesSealingJoint(MaximalTemperaturesSealingJoint *maximalTemperaturesSealingJoint);

    /**
     * @brief
     *
     * @return ThermalBreakage
     */
    ThermalBreakage *getThermalBreakage() const;
    /**
     * @brief
     *
     * @param thermalBreakage
     */
    void setThermalBreakage(ThermalBreakage *thermalBreakage);

    /**
     * @brief
     *
     * @return GlazingSolarFactor
     */
    GlazingSolarFactor *getGlazingSolarFactor() const;
    /**
     * @brief
     *
     * @param climateSolarFactor
     */
    void setGlazingSolarFactor(GlazingSolarFactor *climateSolarFactor);

private:
    SolarFactor * _solarFactor; /**< TODO: describe */
    UValue * _uValue; /**< TODO: describe */
    BaySolarFactor * _baySolarFactor; /**< TODO: describe */
    MaximalTemperaturesSealingJoint *_maximalTemperaturesSealingJoint; /**< TODO: describe */
    ThermalBreakage *_thermalBreakage; /**< TODO: describe */
    GlazingSolarFactor *_glazingSolarFactor; /**< TODO: describe */

};

}
}

#endif // CLIMATECONDITIONS_H
