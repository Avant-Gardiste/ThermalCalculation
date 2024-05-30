/*
Note: value Beta (openness coefficient( porosity))
      line -> position_store = Nbr_vit + Nbr_store - 1
*/

#ifndef SOLARFACTORXPP50_H
#define SOLARFACTORXPP50_H

#include "solarfactorxpp50_global.h"

#include <iostream>
#include "object.h"

#include "frame.h"
#include "glazingwall.h"
#include "glazingxp50.h"
#include "mobileprotection.h"
#include "opaquewall.h"
#include "roller.h"

#include "solarcharacteristics.h"
#include "baysolarfactorxpp50.h"
#include "baysolarfactorventilationxpp50.h"

using namespace VD6::Common;

namespace VD6 {
namespace Calculation {

/**
 * @brief
 *
 */
class SOLARFACTORXPP50SHARED_EXPORT SolarFactorXPP50
{
public:
    /**
     * @brief
     *
     */
    SolarFactorXPP50();
    /**
     * @brief
     *
     */
    ~SolarFactorXPP50();

    boost::thread_specific_ptr<double > threadPor; /**< TODO: describe */

    /**
     * @brief
     *
     */
    void execute();

    /**
     * @brief
     *
     * @param frame
     */
    void setFrame(Frame *frame);

    /**
     * @brief
     *
     * @param glazingWall
     */
    void setGlazingWall(GlazingWall *glazingWall);

    /**
     * @brief
     *
     * @param glazingXP50
     */
    void setGlazingXP50(GlazingXP50 *glazingXP50);

    /**
     * @brief
     *
     * @param mobileProtection
     */
    void setMobileProtection(MobileProtection *mobileProtection);

    /**
     * @brief
     *
     * @param opaqueWall
     */
    void setOpaqueWall(OpaqueWall *opaqueWall);

    /**
     * @brief
     *
     * @param roller
     */
    void setRoller(Roller *roller);

    /**
     * @brief
     *
     * @param map<string
     * @param climatic
     */
    void setClimatic(const map<string, ClimateConditions::Climate *> &climatic);

    /**
     * @brief
     *
     * @return map<std::string, vector<double> >
     */
    map<std::string, vector<double> > solarFactor() const;

    /**
     * @brief
     *
     * @return map<std::string, vector<double> >
     */
    map<std::string, vector<double> > lightTransmittance() const;

    /**
     * @brief
     *
     * @return map<std::string, vector<double> >
     */
    map<std::string, vector<double> > solarFactorBackUp() const;

    /**
     * @brief
     *
     * @return map<std::string, vector<double> >
     */
    map<std::string, vector<double> > lightTransmittanceBackUp() const;

    /**
     * @brief
     *
     * @return vector<double>
     */
    vector<double> component() const;

    /**
     * @brief
     *
     * @return vector<double>
     */
    vector<double> uValue() const;

private:
    /**
     * @brief
     *
     * @param angle1
     * @param angle2
     * @param por
     */
    void workInThread(int angle1, int angle2, double por);

private:
    /**
     * @brief
     *
     */
    void calculationUValue();

    /**
     * @brief
     *
     * @param i
     * @param key
     * @param map<string
     * @param solarFactor
     * @param text
     * @param rext
     * @param coefSwGlobalAvecSto
     * @param coefSw1Dir
     * @param coefSw1Dif
     * @param coefSw1Ref
     * @param coefSws
     * @param coefSws1
     * @param coefSws2
     * @param coefSws3
     * @param coefSw1AlphaEta
     * @param coefSw2AlphaEta
     * @param coefSw3AlphaEta
     * @return vector<double>
     */
    vector<double> solarFactorWithProtection(int i, string key, map<string, Object::ComponentsFlux> solarFactor, double text, double rext,
                                             double &coefSwGlobalAvecSto, double &coefSw1Dir, double &coefSw1Dif, double &coefSw1Ref,
                                             double &coefSws, double &coefSws1, double  &coefSws2, double &coefSws3,
                                             double &coefSw1AlphaEta, double &coefSw2AlphaEta, double &coefSw3AlphaEta);

    /**
     * @brief
     *
     * @param key
     * @param rext
     * @param text
     * @param map<string
     * @param solarFactor
     * @param coefSw
     * @param coefSw1
     * @param coefSw2
     * @param coefSw3
     * @return vector<double>
     */
    vector<double> solarFactorWithoutProtection(string key, double rext, double text, map<string, Object::ComponentsFlux> solarFactor,
                                                double &coefSw, double &coefSw1, double &coefSw2, double &coefSw3);

    /**
     * @brief
     *
     * @param i
     * @param key
     * @param map<string
     * @param solarFactor
     * @param coefTLws
     * @param coefTLwDir
     * @param coefTLwDif
     * @param coefTLwRef
     * @param coefTLwDirDif
     * @param coefTLwRefDir
     * @return vector<double>
     */
    vector<double> lightTransmitanceWithProtection(int i, string key, map<string, Object::ComponentsFlux> solarFactor,
                                                   double &coefTLws, double &coefTLwDir, double &coefTLwDif, double &coefTLwRef, double &coefTLwDirDif, double &coefTLwRefDir);

    /**
     * @brief
     *
     * @param key
     * @param map<string
     * @param solarFactor
     * @param TLw
     * @return double
     */
    double lightTransmitanceWithoutProtection(string key, map<string, Object::ComponentsFlux> solarFactor, double &TLw);

    /**
     * @brief
     *
     * @param TRR
     * @param key
     */
    void calculationBaySolarFactor(vector<vector<double> > TRR, string key = "");
    /**
     * @brief
     *
     * @param >
     * @param key
     */
    void calculationBaySolarFactorLight(vector<vector<double> >, string key = "");

    /**
     * @brief
     *
     * @param isLight
     * @param tr
     * @param re1
     * @param re2
     * @return std::map<string, Object::ComponentsFlux>
     */
    std::map<string, Object::ComponentsFlux> solarFactorXPNormal(bool isLight, double tr, double re1, double re2);
    /**
     * @brief
     *
     * @param isLight
     * @param tr
     * @param re1
     * @param re2
     * @return std::map<string, Object::ComponentsFlux>
     */
    std::map<string, Object::ComponentsFlux> solarFactorXPVentilation(bool isLight, double tr, double re1, double re2);

    /**
     * @brief
     *
     * @param isLight
     * @param tr
     * @param re1
     * @param re2
     * @return vector<vector<double> >
     */
    vector<vector<double> > calculationCharacteristicsEnergy(bool isLight, double tr, double re1, double re2);

    /**
     * @brief
     *
     */
    void calculationBlockEnergy();

    /**
     * @brief
     *
     * @param lightTransmistance
     * @param blindExistence
     * @param season
     */
    void calculationBlockLightEnergy(vector<double> &lightTransmistance, bool blindExistence, string season);
    /**
     * @brief
     *
     * @param solarFactor
     * @param blindExistence
     * @param season
     */
    void calculationBlockSolarEnergy(vector<double> &solarFactor, bool blindExistence, string season);

    /**
     * @brief
     *
     * @param double
     * @param double
     * @param double
     * @return double
     */
    inline double rollerSolarFactor(double, double, double);
    /**
     * @brief
     *
     * @param bool
     * @param double
     * @param double
     * @param double
     * @param double
     * @return double
     */
    inline double opaqueSolarFactor(bool, double, double, double, double);

private:
    double _por; /**< TODO: describe */
    boost::mutex _locker; /**< TODO: describe */

    map<string, ClimateConditions::Climate *> _climatic; /**< TODO: describe */

    GlazingWall *_glazingWall; /**< TODO: describe */
    GlazingXP50 *_glazingXP50; /**< TODO: describe */
    Frame *_frame; /**< TODO: describe */
    MobileProtection *_mobileProtection; /**< TODO: describe */
    OpaqueWall *_opaqueWall; /**< TODO: describe */
    Roller *_roller; /**< TODO: describe */

    vector<double> _uValue; /**< TODO: describe */

    map<std::string, vector<double> > _solarFactor; /**< TODO: describe */
    map<std::string, vector<double> > _lightTransmittance; /**< TODO: describe */

    map<std::string, vector<double> > _solarFactor_backup; /**< TODO: describe */
    map<std::string, vector<double> > _lightTransmittance_backup; /**< TODO: describe */

    vector<double> _components; /**< TODO: describe */
    double _sg; /**< TODO: describe */
    double _sf; /**< TODO: describe */
    double _sfs; /**< TODO: describe */
    double _sp; /**< TODO: describe */
    double _sc; /**< TODO: describe */

    std::map<int, vector<vector<double> > > _venetianCharacteristics; /**< TODO: describe */
};

}
}

#endif // SOLARFACTORXPP50_H
