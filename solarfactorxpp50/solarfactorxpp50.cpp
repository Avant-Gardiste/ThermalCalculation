#include "solarfactorxpp50.h"

#include "venetiancalculationxpp50.h"

using namespace std;

namespace VD6 {
namespace Calculation {

SolarFactorXPP50::SolarFactorXPP50()
{
    threadPor.reset(new double(0));
    _frame           = NULL;
    _glazingWall     = NULL;
    _glazingXP50     = NULL;
    _mobileProtection = NULL;
    _opaqueWall      = NULL;
    _roller          = NULL;
    _sg              = 0.0f;
    _sf              = 0.0f;
    _sfs             = 0.0f;
    _sp              = 0.0f;
    _sc              = 0.0f;
}

SolarFactorXPP50::~SolarFactorXPP50()
{
    for (map<string, ClimateConditions::Climate *>::iterator it = _climatic.begin(); it != _climatic.end(); it++) {
        delete (*it).second;
    }

    delete _glazingWall;
    delete _glazingXP50;

    delete _frame;

    delete _mobileProtection;
    delete _opaqueWall;

    delete _roller;
}

void SolarFactorXPP50::execute()
{
    //Declare variable
    //input
    int typeBlind = 0;                     //Type Of protection

    bool trackingModeEnable = false;                  //Equivalent characteristics for a given angle enable
    bool blindExistence = false;                  //Mobile protection exitance
    bool rollerExistence = false;                    //Roller Enable

    double inclineGlazing = 0;                    //Incline Glazing Wall

    double inclineLame = 0;                         // index listbox orientations blades
    double profileAngle = 0;                        // index listbox Actual profile Angle

    _uValue.clear();

    _solarFactor.clear();
    _lightTransmittance.clear();
    _solarFactor_backup.clear();
    _lightTransmittance_backup.clear();

    _components.clear();

    //Initialization
    blindExistence = this->_glazingWall->enableMobileProtection();
    rollerExistence = this->_glazingWall->rollerExistence();
    inclineGlazing = this->_glazingWall->incline();

    if (blindExistence) {
        trackingModeEnable = this->_mobileProtection->getEnableSolarTracking();
        typeBlind = this->_mobileProtection->getBlinds()[0]->typeIndex();

        inclineLame = this->_mobileProtection->getOrientationBlade();
        profileAngle = this->_mobileProtection->getActualAngle();
    } else {
        trackingModeEnable = false;
    }

    //Calculation
    if (!trackingModeEnable) {
        std::map<int, vector<vector<double> >> TRR{};

        if (typeBlind == 1) {
            VenetianCalculationXPP50 *calculator = new VenetianCalculationXPP50();

            TRR = calculator->calculate(inclineGlazing, _mobileProtection->getDistanceBlindGlazing(), _mobileProtection->getWidthBlade(), _mobileProtection->getDistacneAxises(),
                                                        _mobileProtection->getCharacteristicsBlindVenetian()[0], _mobileProtection->getCharacteristicsBlindVenetian()[1], _mobileProtection->getCharacteristicsBlindVenetian()[2],
                                                        _mobileProtection->getCharacteristicsBlindVenetian()[3], _mobileProtection->getCharacteristicsBlindVenetian()[4],
                                                        _mobileProtection->getCharacteristicsBlindVenetian()[5], _mobileProtection->getCharacteristicsBlindVenetian()[6],
                                                        _mobileProtection->getCharacteristicsBlindVenetian()[7], inclineLame, profileAngle);
        }

        calculationBaySolarFactor(TRR[Object::ModuleEnergy::Solar]);
        calculationUValue();
        calculationBaySolarFactorLight(TRR[Object::ModuleEnergy::Light]);

    } else {
        vector<int> angle = {0, 15, 30, 45, 60, 75, 90};

        for (int i = 6 ; i >= 0; i--) {
            boost::thread_group process;
            for (int j = 0; j < 7; j++) {
                int cl = 90 - angle[i];
                if (cl < 5) cl = 5;
                double por = 0.00005 * std::pow(cl, 3) - 0.0118 * std::pow(cl, 2) + 0.9302 * cl - 1.4372;
                por = round(por) / 100;

                if (blindExistence) {
                    process.add_thread(new boost::thread(boost::bind( &SolarFactorXPP50::workInThread, this, i, j, por)));
                }
            }
            process.join_all();

        }
        calculationUValue();
    }

    _components.push_back(_sg);
    _components.push_back(_sf);
    _components.push_back(_sfs);
    _components.push_back(_sp);

    if (rollerExistence) {
        _lightTransmittance_backup = _lightTransmittance;
        _solarFactor_backup = _solarFactor;
        calculationBlockEnergy();
        _components.push_back(_sc);
    }
    else{
        _components.push_back(0.0f);
    }
}

vector<double> SolarFactorXPP50::solarFactorWithProtection(int i, string key, map<string, Object::ComponentsFlux> solarFactor,
                                                           double text, double rext,
                                                           double &coefSwGlobalAvecSto,
                                                           double &coefSw1Dir, double &coefSw1Dif, double &coefSw1Ref,
                                                           double &coefSws, double &coefSws1, double  &coefSws2, double &coefSws3,
                                                           double &coefSw1AlphaEta, double &coefSw2AlphaEta, double &coefSw3AlphaEta)
{
    bool opaque = this->_glazingWall->withOpaquePart();
    bool blindExistence = this->_glazingWall->enableMobileProtection();

    bool trackingMode = false;
    int typeBlind = -1;
    int k = 0;

    int numberGlass = 0, numberBlind = -1;
    int blindPosition = -1;
    double sigma = 0;

    double ufAverageFrame = _frame->ufAverage();
    double absFrame = _frame->coefEnergyAbsorption();

    double opaqueFS = 0, opaqueFSSeason = 0;
    double coefUpOpaque = 0, absOpaque = 0;
    double coefAg = 0, coefAf = 0, coefAp = 0;
    double sgs1Dir = 0, sgs1Dif = 0, sgs1Ref = 0;
    double sgs1 = 0, sgs2 = 0, sgs3 = 0;

    //Initialization
    double fluxFs = this->_climatic[key]->getFi();
    double heFs = this->_climatic[key]->getHe();

    double coefFS = solarFactor[key + "_Blind"]._factorSolar;
    double fluxCLO = solarFactor[key + "_Blind"]._fluxCLO;
    double fluxCONV = solarFactor[key + "_Blind"]._fluxCONV;
    double fluxGLO = solarFactor[key + "_Blind"]._fluxGLO;
    double fluxAir = solarFactor[key + "_Blind"]._fluxAir;

    double coefFsBlind = coefFS; // <-coefFS_XP
    double coefFsRoller = rollerSolarFactor(heFs, ufAverageFrame, absFrame);
    double coefFsOpaque = opaqueSolarFactor(true, ufAverageFrame, coefFsRoller, text, rext);

    if (blindExistence) {
        typeBlind = this->_mobileProtection->getBlinds()[0]->typeIndex();
        blindPosition = this->_mobileProtection->getPositionBlind();

        numberBlind = blindExistence;
        numberGlass = this->_glazingXP50->getNumberPane();
        trackingMode = this->_mobileProtection->getEnableSolarTracking();
    }

    if (blindExistence && typeBlind == 1) {
        k = 4;                          // store avec lame;
    } else {
        k = 1;                          // store sans lame;
    }

    if (opaque) {
        coefUpOpaque = this->_opaqueWall->coefUp();
        absOpaque = this->_opaqueWall->coefEnergyAbsorption();
    }

    coefAg = this->_glazingWall->surfaceGlazingAg();
    coefAf = this->_glazingWall->surfaceGlazingAf();
    coefAp = this->_glazingWall->surfaceOpaqueWallAp();

    sigma = coefAg / (coefAg + coefAf);

    if (opaque) {
        opaqueFS = rollerSolarFactor(heFs, coefUpOpaque, absOpaque);
        opaqueFSSeason = opaqueSolarFactor(true, coefUpOpaque, opaqueFS, text, rext);

        if (i == 0) {
            sgs1Dir = (fluxCLO / fluxFs);
            coefSw1Dir = sgs1Dir * coefAg / (coefAg + coefAf + coefAp);

            if (k == 1) {         //store sans lame;
                sgs1 = (fluxCLO / fluxFs);
                sgs2 = (fluxCONV + fluxGLO) / fluxFs;
                sgs3 = (fluxAir / fluxFs);

                coefSws = (coefAp * opaqueFSSeason + coefAf * coefFsOpaque + coefAg * coefFsBlind) / (coefAg + coefAf + coefAp);
                coefSws1 = sgs1 * coefAg / (coefAg + coefAf + coefAp);
                coefSws2 = (coefAp * opaqueFSSeason + coefAf * coefFsOpaque + coefAg * sgs2) / (coefAg + coefAf + coefAp);

                if (blindPosition = numberGlass + numberBlind - 1) { //ssi store intérieur;
                    coefSws3 = sgs3 * coefAg / (coefAg + coefAf + coefAp);
                } else {
                    coefSws3 = 0;
                }

                _sg = sgs2;
                _sfs = coefFsOpaque;
                _sp = opaqueFSSeason;

            }
        } else if (i == 1) {
            sgs1Dif = (fluxCLO / fluxFs);
            coefSw1Dif = sgs1Dif * coefAg / (coefAg + coefAf + coefAp);

        } else if (i == 2) {
            sgs1Ref = (fluxCLO / fluxFs);
            coefSw1Ref = sgs1Ref * coefAg / (coefAg + coefAf + coefAp);

        } else if (i == 3) {
            sgs1 = (fluxCLO / fluxFs);
            coefSw1AlphaEta = sgs1 * coefAg / (coefAg + coefAf + coefAp);
            coefSwGlobalAvecSto = (coefFsBlind * coefAg + coefFsOpaque * coefAf + opaqueFSSeason * coefAp) / (coefAf + coefAp + coefAg);

            sgs2 = (fluxCONV + fluxGLO) / fluxFs;
            coefSw2AlphaEta = (coefAp * opaqueFSSeason + coefAf * coefFsOpaque + coefAg * sgs2) / (coefAg + coefAf + coefAp);

            sgs3 = (fluxAir / fluxFs);

            if (blindPosition = numberGlass + numberBlind - 1) {          //ssi store intérieur;
                coefSw3AlphaEta = (coefAg * sgs3) / (coefAg + coefAf + coefAp);
            } else {
                coefSw3AlphaEta = 0;
            }

            _sg = sgs2;
            _sfs = coefFsOpaque;
            _sp = opaqueFSSeason;

        }
    } else {
        sigma = coefAg / (coefAg + coefAf);

        if (i == 0) {
            sgs1Dir = (fluxCLO / fluxFs);
            coefSw1Dir = sigma * sgs1Dir;

            if (k == 1) { //store sans lame;
                sgs1 = (fluxCLO / fluxFs);
                sgs2 = (fluxCONV + fluxGLO) / fluxFs;
                sgs3 = (fluxAir / fluxFs);

                coefSws = sigma * coefFsBlind + (1 - sigma) * coefFsOpaque;
                coefSws1 = sigma * sgs1;
                coefSws2 = sigma * sgs2 + (1 - sigma) * coefFsOpaque;

                if (blindPosition == numberGlass + numberBlind - 1) { //ssi store intérieur;
                    coefSws3 = sigma * sgs3;
                } else {
                    coefSws3 = 0;
                }

                _sg = sgs2;
                _sfs = coefFsOpaque;
                _sp = 0.0f;

            }
        } else if (i == 1) {
            sgs1Dif = (fluxCLO / fluxFs);
            coefSw1Dif = sigma * sgs1Dif;

        } else if (i == 2) {
            sgs1Ref = (fluxCLO / fluxFs);
            coefSw1Ref = sigma * sgs1Ref;

        } else if (i == 3) {
            sgs1 = (fluxCLO / fluxFs);
            coefSw1AlphaEta = sigma * sgs1;
            coefSwGlobalAvecSto = coefFsBlind * sigma + (1 - sigma) * coefFsOpaque;

            sgs2 = (fluxCONV + fluxGLO) / fluxFs;
            coefSw2AlphaEta = sigma * sgs2 + (1 - sigma) * coefFsOpaque;

            sgs3 = (fluxAir / fluxFs);

            if (blindPosition == numberGlass + numberBlind - 1) { //ssi store intérieur; Warning!
                coefSw3AlphaEta = sigma * sgs3;
            } else {
                coefSw3AlphaEta = 0;
            }

            _sg = sgs2;
            _sfs = coefFsOpaque;
            _sp = 0.0f;

        }
    }

    if (4 == k) {
        if (trackingMode) {
            return vector<double> { coefSw1Dir, coefSw1Dif, coefSw1Ref, coefSw2AlphaEta, coefSw3AlphaEta};
        } else {
            return vector<double> { coefSwGlobalAvecSto, coefSw1Dir, coefSw1Dif, coefSw1Ref, coefSw1AlphaEta, coefSw2AlphaEta, coefSw3AlphaEta};
        }
    } else {
        return vector<double> { coefSws, coefSws1, coefSws2, coefSws3};
    }
}

vector<double> SolarFactorXPP50::solarFactorWithoutProtection(string key, double rext, double text,
                                                              map<string, Object::ComponentsFlux> solarFactor,
                                                              double &coefSw, double &coefSw1, double &coefSw2, double &coefSw3)
{
    bool opaque = this->_glazingWall->withOpaquePart();
    bool blindExistence = this->_glazingWall->enableMobileProtection();

    int numberGlass = 0, numberBlind = -1;
    int blindPosition = -1;
    double sigma = 0;

    double ufAverageFrame = _frame->ufAverage();
    double coefAbsFrame = _frame->coefEnergyAbsorption();

    double opaqueFS = 0, opaqueFS_Season = 0;
    double coefUpOpaque = 0, opaqueAbs = 0;
    double coefAg = 0, coefAf = 0, coefAp = 0;

    //Initialization
    if (blindExistence) {
        blindPosition = this->_mobileProtection->getPositionBlind();
        numberBlind = blindExistence;
        numberGlass = this->_glazingXP50->getNumberPane();
    }

    if (opaque) {
        coefUpOpaque = this->_opaqueWall->coefUp();
        opaqueAbs = this->_opaqueWall->coefEnergyAbsorption();
    }

    coefAg = this->_glazingWall->surfaceGlazingAg();
    coefAf = this->_glazingWall->surfaceGlazingAf();
    coefAp = this->_glazingWall->surfaceOpaqueWallAp();

    sigma = coefAg / (coefAg + coefAf);

    //Initialization
    double fluxFS = this->_climatic[key]->getFi();
    double heFS = this->_climatic[key]->getHe();

    double coefFS = solarFactor[key + "_Glass"]._factorSolar;
    double fluxCLO = solarFactor[key + "_Glass"]._fluxCLO;
    double fluxCONV = solarFactor[key + "_Glass"]._fluxCONV;
    double fluxGLO = solarFactor[key + "_Glass"]._fluxGLO;

    double coefFSWithoutBlind = coefFS;
    double coefFSRollerWithoutBlind = rollerSolarFactor(heFS, ufAverageFrame, coefAbsFrame);
    double coefFSFrameWithoutBlind = coefFSRollerWithoutBlind;

    //------------------- FS ete sans Store XP 50-----------------------
    if (opaque) {
        opaqueFS = rollerSolarFactor(heFS, coefUpOpaque, opaqueAbs);
        opaqueFS_Season = opaqueSolarFactor(false, coefUpOpaque, opaqueFS, text, rext);

        coefSw = (coefFSWithoutBlind * coefAg + coefFSFrameWithoutBlind * coefAf + opaqueFS_Season * coefAp) / (coefAf + coefAp + coefAg);
        coefSw1 = (fluxCLO / fluxFS) * coefAg / (coefAf + coefAp + coefAg);
        coefSw2 = ((((fluxCONV + fluxGLO) / fluxFS) * coefAg) +
                   (coefAf * coefFSFrameWithoutBlind) + (coefAp * opaqueFS_Season)) / (coefAf + coefAp + coefAg);

        coefSw3 = 0;

        _sg = (fluxCONV + fluxGLO) / fluxFS;
        _sf = coefFSFrameWithoutBlind;
        _sp = opaqueFS_Season;

    } else {
        coefSw = coefFSWithoutBlind * sigma + coefFSFrameWithoutBlind * (1 - sigma);
        coefSw1 = (fluxCLO / fluxFS) * sigma;
        coefSw2 = (((fluxCONV + fluxGLO) / fluxFS) * sigma) +
                ((1 - sigma) * coefFSFrameWithoutBlind);

        coefSw3 = 0;

        _sg = coefFS; //(fluxCONV + fluxGLO) / fluxFS; Dec09 04012022
        _sf = coefFSFrameWithoutBlind;
        _sp = 0.0f;

    }

    return vector<double> {coefSw, coefSw1, coefSw2, coefSw3};
}

vector<double> SolarFactorXPP50::lightTransmitanceWithProtection(int i, string key,
                                                                 map<string, Object::ComponentsFlux> solarFactor,
                                                                 double &coefTLws, double &coefTLwDir, double &coefTLwDif, double &coefTLwRef,
                                                                 double &coefTLwDirDif, double &coefTLwRefDir)
{
    bool opaque = this->_glazingWall->withOpaquePart();
    bool blindExistence = this->_glazingWall->enableMobileProtection();

    bool trackingMode = false;
    int typeBlind = -1;
    int numberGlass = 0, numberBlind = -1;

    int blindPosition = -1;
    int k = 0;
    double sigma = 0;

    double coefUpOpaque = 0, opaqueAbs = 0;
    double coefAg = 0, coefAf = 0, coefAp = 0;

    double fluxFS = this->_climatic[key]->getFi();
    double fluxCLO = solarFactor[key + "_Blind"]._fluxCLO;

    //Initialization
    if (blindExistence == true) {
        typeBlind = this->_mobileProtection->getBlinds()[0]->typeIndex();
        blindPosition = this->_mobileProtection->getPositionBlind();

        numberBlind = blindExistence;

        numberGlass = this->_glazingXP50->getNumberPane();
        trackingMode = this->_mobileProtection->getEnableSolarTracking();
    }

    if (blindExistence && typeBlind == 1) {
        k = 6;               // store avec lame; venetian
    } else {
        k = 1;               // store sans lame; toile
    }

    if (opaque) {
        coefUpOpaque = this->_opaqueWall->coefUp();
        opaqueAbs = this->_opaqueWall->coefEnergyAbsorption();
    }

    coefAg = this->_glazingWall->surfaceGlazingAg();
    coefAf = this->_glazingWall->surfaceGlazingAf();
    coefAp = this->_glazingWall->surfaceOpaqueWallAp();

    sigma = coefAg / (coefAg + coefAf);

    //-----------------------------Tinh FS_LUMINEUES theo XP P50-----------------------------

    if (opaque) {
        if (i == 0) {
            coefTLwDir = (fluxCLO / fluxFS) * coefAg / (coefAg + coefAf + coefAp);

            if (k == 1) {
                coefTLws = (fluxCLO / fluxFS) * coefAg / (coefAg + coefAf + coefAp);
            }

        } else if (i == 1) {
            coefTLwDirDif = (fluxCLO / fluxFS) * coefAg / (coefAg + coefAf + coefAp);

        } else if (i == 2) {
            coefTLwDif = (fluxCLO / fluxFS) * coefAg / (coefAg + coefAf + coefAp);

        } else if (i == 3) {
            coefTLwRef = (fluxCLO / fluxFS) * coefAg / (coefAg + coefAf + coefAp);

        } else if (i == 4) {
            coefTLwRefDir = (fluxCLO / fluxFS) * coefAg / (coefAg + coefAf + coefAp);

        } else if (i == 5) {
            coefTLws = (fluxCLO / fluxFS) * coefAg / (coefAg + coefAf + coefAp);
        }
    }

    if (!opaque) {
        if (i == 0) {
            coefTLwDir = sigma * (fluxCLO / fluxFS);

            if (k == 1) {
                coefTLws = sigma * (fluxCLO / fluxFS);
            }
        } else if (i == 1) {
            coefTLwDirDif = sigma * (fluxCLO / fluxFS);

        } else if (i == 2) {
            coefTLwDif = sigma * (fluxCLO / fluxFS);

        } else if (i == 3) {
            coefTLwRef = sigma * (fluxCLO / fluxFS);

        } else if (i == 4) {
            coefTLwRefDir = sigma * (fluxCLO / fluxFS);

        } else if (i == 5) {
            coefTLws = sigma * (fluxCLO / fluxFS);
        }
    }

    if (6 == k) {
        if (trackingMode) {
            return vector<double> {coefTLwDir, coefTLwDirDif, coefTLwDif, coefTLwRef, coefTLwRefDir};
        } else {
            return vector<double> {coefTLws, coefTLwDir, coefTLwDif, coefTLwRef};
        }
    } else {
        return vector<double> {coefTLws};
    }
}

double SolarFactorXPP50::lightTransmitanceWithoutProtection(string key, map<string, Object::ComponentsFlux> solarFactor, double &coefTLw)
{
    bool opaque = this->_glazingWall->withOpaquePart();

    double coefAg = this->_glazingWall->surfaceGlazingAg();
    double coefAf = this->_glazingWall->surfaceGlazingAf();
    double coefAp = this->_glazingWall->surfaceOpaqueWallAp();

    double sigma = coefAg / (coefAg + coefAf);

    double fluxCLO = solarFactor[key + "_Glass"]._fluxCLO;
    double fluxFS = this->_climatic[key]->getFi();

    if (opaque) {
        coefTLw = (fluxCLO / fluxFS) * coefAg / (coefAg + coefAf + coefAp);
    } else {
        coefTLw = (fluxCLO / fluxFS) * sigma;
    }

    return coefTLw;
}

void SolarFactorXPP50::calculationBaySolarFactor(vector<vector<double> > TRR, string key)
{
    //Declare
    int typeBlind = -1;
    int blindPosition = -1;

    int numberGlass = 0;
    int numberBlind = 0;

    bool blindExistence = false;
    bool opaque = false;

    double incline = 0;

    double coefAg = 0;
    double coefAf = 0;
    double coefAp = 0;

    double coefUpOpaque = 0;
    double opaqueAbs = 0;
    double ufAverageFrame = 0;
    double coefAbsFrame = 0;

    //input from func
    double text = 0, rext = 0;                                       // total = 0;
    int lumineues = 0;

    //temp
    int k = 0;
    double inclineCal = 0;
    double sigma = 0;
    double blindTr  = 0, blindRe1 = 0, blindRe2 = 0;

    //Result function


    double sw1Dir = 0;
    double sws = 0, sws1 = 0, sws2 = 0, sws3 = 0;
    double sw1Dif = 0, sw1Ref = 0;
    double sw3AnphaEta = 0, sw2AnphaEta = 0, swGlobalAvecSto = 0, sw1AnphaEta = 0;
    double sw = 0, sw1 = 0, sw2 = 0, sw3 = 0;

    //Initialization
    blindExistence = this->_glazingWall->enableMobileProtection();
    opaque = this->_glazingWall->withOpaquePart();

    numberGlass = this->_glazingXP50->getNumberPane();

    incline = this->_glazingWall->incline();

    coefAg = this->_glazingWall->surfaceGlazingAg();
    coefAf = this->_glazingWall->surfaceGlazingAf();
    coefAp = this->_glazingWall->surfaceOpaqueWallAp();

    if (blindExistence) {
        typeBlind = this->_mobileProtection->getBlinds()[0]->typeIndex();
        blindPosition = this->_mobileProtection->getPositionBlind();
        numberBlind = 1;
    }

    if (opaque) {
        coefUpOpaque = this->_opaqueWall->coefUp();
        opaqueAbs = this->_opaqueWall->coefEnergyAbsorption();
    }

    ufAverageFrame = _frame->ufAverage();
    coefAbsFrame = _frame->coefEnergyAbsorption();

    inclineCal = incline;
    sigma = coefAg / (coefAg + coefAf);

    //*************************** Calcul en été *************************************
    bool trackingMode = false;

    if (this->_mobileProtection != NULL) {
        trackingMode = this->_mobileProtection->getEnableSolarTracking();
    }

    if (blindExistence && typeBlind == 1) {
        k = 4;               // store avec lame;
        rext = TRR[3][1];
        text = TRR[3][0];
    } else {
        k = 1;               // store sans lame;
        rext = 0;
        text = 0;
    }

    std::vector<string> keys{"summer", "winter"};
    vector<double> sfSummer, sfWinter;
    vector<std::map<string, Object::ComponentsFlux>> solarFactorData;
    // Summer
    for (int i = 0; i < k; i++) {
        std::map<string, Object::ComponentsFlux> solarFactor;

        if (k == 4) {
            blindTr =  TRR[i][0] * 100;
            blindRe1 = TRR[i][1] * 100;
            blindRe2 = TRR[i][2] * 100;
        }

        if (this->_glazingXP50->gasGapsVentilationExistence()) {
            solarFactor = solarFactorXPVentilation(lumineues, blindTr, blindRe1, blindRe2);
        } else {
            solarFactor = solarFactorXPNormal(lumineues, blindTr, blindRe1, blindRe2);
        }

        solarFactorData.push_back(solarFactor);
    }

    for (int i = 0; i < k; i++) {
        sfSummer = solarFactorWithProtection(i, keys[0], solarFactorData[i],
                text, rext,
                swGlobalAvecSto,
                sw1Dir, sw1Dif, sw1Ref,
                sws, sws1, sws2, sws3,
                sw1AnphaEta, sw2AnphaEta, sw3AnphaEta);

        //_solarFactor["summer_Blind" + key] = std::move(sfSummer);
        _locker.lock();
        _solarFactor["00" + key] = std::move(sfSummer);
        //if (!trackingMode) {
        _solarFactor["01"] = std::move(solarFactorWithoutProtection(keys[0], rext, text, solarFactorData[i], sw, sw1, sw2, sw3));
        _locker.unlock();
        //}
    }

    //Winter
    for (int i = 0; i < k; i++) {
        sfWinter = solarFactorWithProtection(i, keys[1], solarFactorData[i],
                text, rext,
                swGlobalAvecSto,
                sw1Dir, sw1Dif, sw1Ref,
                sws, sws1, sws2, sws3,
                sw1AnphaEta, sw2AnphaEta, sw3AnphaEta);

        _locker.lock();
        _solarFactor["10" + key] = std::move(sfWinter);
        _solarFactor["11"] = std::move(solarFactorWithoutProtection(keys[1], rext, text, solarFactorData[i], sw, sw1, sw2, sw3));
        _locker.unlock();
    }
}

void SolarFactorXPP50::calculationBaySolarFactorLight(vector<vector<double> > TRR, string key)
{
    bool blindExistence = false;
    bool opaque = false;
    int typeBlind = -1;

    int k = 0;

    double coefAg = 0, coefAf = 0, coefAp = 0, sigma = 0, inclineGlazing = 0;

    double inclinaisonCalc = 0;

    double coefTLwDir = 0,  coefTLws = 0, coefTLwDirDif = 0, coefTLw = 0;
    double coefTLwDif = 0, coefTLwRef = 0, coefTLwRefDir = 0;
    double coefTLStoLame = 0, coefRL1StoLame = 0, coefRL2StoLame = 0;

    bool trackingMode = false;

    //Initialization
    inclineGlazing = this->_glazingWall->incline();

    coefAg = this->_glazingWall->surfaceGlazingAg();
    coefAf = this->_glazingWall->surfaceGlazingAf();
    coefAp = this->_glazingWall->surfaceOpaqueWallAp();

    sigma = coefAg / (coefAg + coefAf);

    opaque = this->_glazingWall->withOpaquePart();
    blindExistence = this->_glazingWall->enableMobileProtection();

    if (blindExistence) {
        typeBlind = this->_mobileProtection->getBlinds()[0]->typeIndex();
        trackingMode = this->_mobileProtection->getEnableSolarTracking();
    }

    inclinaisonCalc = inclineGlazing;
    sigma = coefAg / (coefAg + coefAf);

    std::map<string, Object::ComponentsFlux> solarFactor ;

    if (blindExistence && typeBlind == 1) {
        k = 6; // store avec lame
    } else {
        k = 1; // store sans lame
    }

    vector<double> lumiSummer;
    std::vector<string> keys{"summer", "winter"};

    for (int i = 0; i < k; i++) {
        if (k == 6) {
            coefTLStoLame = TRR[i][0]  * 100;
            coefRL1StoLame = TRR[i][1] * 100;
            coefRL2StoLame = TRR[i][2] * 100;
        }

        if (_glazingXP50->gasGapsVentilationExistence()) {
            solarFactor = solarFactorXPVentilation(Object::ModuleEnergy::Light, coefTLStoLame, coefRL1StoLame, coefRL2StoLame);
        } else {
            solarFactor = solarFactorXPNormal(Object::ModuleEnergy::Light, coefTLStoLame, coefRL1StoLame, coefRL2StoLame);
        }

        std::vector<string> keys{"summer", "winter"};

        lumiSummer = lightTransmitanceWithProtection(i, keys[0], solarFactor,
                coefTLws, coefTLwDir, coefTLwDif, coefTLwRef,
                coefTLwDirDif, coefTLwRefDir);
    }

    _locker.lock();
    _lightTransmittance["00" + key] = std::move(lumiSummer);
    _lightTransmittance["01"] = vector<double> { lightTransmitanceWithoutProtection(keys[0], solarFactor, coefTLw)};
    _locker.unlock();
}

std::map<string, Object::ComponentsFlux> SolarFactorXPP50::solarFactorXPNormal(bool isLight , double Tr, double Re1, double Re2)
{
    bool blindExistence = _glazingWall->enableMobileProtection();
    int typeBlind = -1;

    double coefAg = this->_glazingWall->surfaceGlazingAg();
    double coefAf = this->_glazingWall->surfaceGlazingAf();

    if (blindExistence) {
        typeBlind = this->_mobileProtection->getBlinds()[0]->typeIndex();
    }

    //calculation
    BaySolarFactorXPP50 *solarFactorXP = new BaySolarFactorXPP50();
    Object::ObjectBaySolarFactor *data = new Object::ObjectBaySolarFactor();

    vector<vector<double> > characteristisEnergy = calculationCharacteristicsEnergy(isLight, Tr, Re1, Re2);

    data->_incline = this->_glazingWall->incline();
    data->_width = this->_glazingWall->width() * 1000;
    data->_height = this->_glazingWall->height() * 1000;

    data->_glass = _glazingXP50;

    data->_spectralIndex = false; // unknow
    data->_spectralIndexBlind = false;
    data->_climates = this->_climatic;

    data->_absorptionEffectiveGlass = characteristisEnergy[0];

    if (blindExistence) {
        data->_blind = _mobileProtection->clone();
        data->_absorptionEffectiveGlobal = characteristisEnergy[1];

        if (typeBlind == 1) {
            if (isLight) {
                Object::ModuleEnergy::Light;
                data->_blind->getBlinds()[0]->setTl(Tr);
                data->_blind->getBlinds()[0]->setRl1(Re1);
                data->_blind->getBlinds()[0]->setRl2(Re2);
            } else {
                Object::ModuleEnergy::Solar;
                data->_blind->getBlinds()[0]->setTe1(Tr);
                data->_blind->getBlinds()[0]->setTe2(Tr);
                data->_blind->getBlinds()[0]->setRe1(Re1);
                data->_blind->getBlinds()[0]->setRe2(Re2);
            }

            data->_blind->getBlinds()[0]->setOpennessFactor(*threadPor.get());
        }
    } else {
        data->_blind = NULL;
    }

    data->_sigma = coefAg / (coefAg + coefAf);
    data->_bayUfFrame = _frame->ufAverage();
    data->_bayAbsFrame = _frame->coefEnergyAbsorption();
    data->_glazingBareInterior; // unknow

    solarFactorXP->setData(data);
    solarFactorXP->calculationSolarFactor();

    return solarFactorXP->getSolarFactor();
}

std::map<string, Object::ComponentsFlux> SolarFactorXPP50::solarFactorXPVentilation(bool isLight, double Tr, double Re1, double Re2)
{
    std::map<string, Object::ComponentsFlux> componentsFlux{};

    bool blindExistence = _glazingWall->enableMobileProtection();
    int typeBlind = -1;

    double coefAg = this->_glazingWall->surfaceGlazingAg();
    double coefAf = this->_glazingWall->surfaceGlazingAf();

    if (blindExistence) {
        typeBlind = this->_mobileProtection->getBlinds()[0]->typeIndex();
    }

    //calculation
    BaySolarFactorVentilationXPP50 *solarFactorXP = new BaySolarFactorVentilationXPP50();
    Object::ObjectBaySolarFactor *data = new Object::ObjectBaySolarFactor();

    vector<vector<double> > characteristisEnergy = calculationCharacteristicsEnergy(isLight, Tr, Re1, Re2);

    data->_incline = this->_glazingWall->incline();

    data->_width = this->_glazingWall->width() * 1000;
    data->_height = this->_glazingWall->height() * 1000;

    data->_glass = _glazingXP50;

    data->_spectralIndex = false; // unknow
    data->_spectralIndexBlind = false;

    data->_climates = this->_climatic;
    data->_absorptionEffectiveGlass = characteristisEnergy[0];

    if (blindExistence) {
        data->_blind = _mobileProtection->clone();
        data->_absorptionEffectiveGlobal = characteristisEnergy[1];

        if (typeBlind == 1) {
            if (isLight) {
                Object::ModuleEnergy::Light;

                data->_blind->getBlinds()[0]->setTl(Tr);
                data->_blind->getBlinds()[0]->setRl1(Re1);
                data->_blind->getBlinds()[0]->setRl2(Re2);
            } else {
                Object::ModuleEnergy::Solar;

                data->_blind->getBlinds()[0]->setTe1(Tr);
                data->_blind->getBlinds()[0]->setTe2(Tr);
                data->_blind->getBlinds()[0]->setRe1(Re1);
                data->_blind->getBlinds()[0]->setRe2(Re2);
            }

            //data->_blind->getBlinds()[0]->setOpennessFactor(_por);
        }
    } else {
        data->_blind = NULL;
    }

    if (data->_blind && data->_blind->getBlinds().size() > 0) {
        data->_blind->getBlinds()[0]->setOpennessFactor(data->_blind->getBlinds()[0]->getOpennessFactor() * 100);
    }

    data->_sigma = coefAg / (coefAg + coefAf);
    data->_bayUfFrame = _frame->ufAverage();
    data->_bayAbsFrame = _frame->coefEnergyAbsorption();
    data->_glazingBareInterior = false; // unknow

    solarFactorXP->setData(data);
    solarFactorXP->solarFactorVentilation();

    componentsFlux = solarFactorXP->getSolarFactor();

    return componentsFlux;
}

vector<vector<double> > SolarFactorXPP50::calculationCharacteristicsEnergy(bool isLight , double Tr, double Re1, double Re2)
{
    //Data
    int numGlass = 0;
    int positionBlind = -1;
    int typeBlind = -1;

    bool blindExistence = false;
    bool obstacleExistence = false;

    GlassVD *glass1Data = NULL;
    GlassVD *glass2Data = NULL;
    GlassVD *glass3Data = NULL;
    GlassVD *glass4Data = NULL;

    BlindVD *blindData  = NULL;

    vector<ObstacleVD *> dataObstacles{};
    vector<bool> obstaclesExistence{};
    Object::ModuleEnergy mode = Object::ModuleEnergy::Solar;

    //Initialization
    numGlass = this->_glazingXP50->getNumberPane();
    blindExistence = _glazingWall->enableMobileProtection();

    if (!isLight) {
        mode = Object::ModuleEnergy::Solar;
    } else {
        mode = Object::ModuleEnergy::Light;
    }

    if (blindExistence) {
        typeBlind = this->_mobileProtection->getBlinds()[0]->typeIndex();

        positionBlind = _mobileProtection->getPositionBlind();
        blindData = new BlindVD(_mobileProtection->getBlinds()[0]);

        if (typeBlind == 1) {
            if (isLight) {
                blindData->setTl(Tr / 100);
                blindData->setRl1(Re1 / 100);
                blindData->setRl2(Re2 / 100);
            } else {
                blindData->setTe1(Tr / 100);
                blindData->setTe2(Tr / 100);
                blindData->setRe1(Re1 / 100);
                blindData->setRe2(Re2 / 100);
            }
        }
    } else {
        positionBlind = -1;
        blindData = NULL;
    }

    if (numGlass >= 1) {
        glass1Data = _glazingXP50->getGlasses()[0];
    }

    if (numGlass >= 2) {
        glass2Data = _glazingXP50->getGlasses()[1];
    }

    if (numGlass >= 3) {
        glass3Data = _glazingXP50->getGlasses()[2];
    }

    if (numGlass >= 4) {
        glass4Data = _glazingXP50->getGlasses()[3];
    }

    //Calculation
    SolarCharacteristics *calculator = new SolarCharacteristics();

    return calculator->execute(numGlass, glass1Data, glass2Data, glass3Data, glass4Data,
                               blindExistence, positionBlind, blindData, obstacleExistence, obstaclesExistence, dataObstacles, mode);
}

void SolarFactorXPP50::calculationBlockEnergy()
{
    auto funcSolar = [ = ](auto & it) {
        std::string keyword;
        bool blindExistence;

        string season = "";
        keyword = it.first;

        if (keyword.substr(0, 1) == "0") {
            season = "summer";
        } else if (keyword.substr(0, 1) == "1") {
            season = "winter";
        }

        if (keyword.substr(1, 1) == "0" && _glazingWall->enableMobileProtection()) {
            blindExistence = true;
        } else {
            blindExistence = false;
        }

        calculationBlockSolarEnergy(it.second, blindExistence, season);
    };

    auto funcLight = [ = ](auto & it) {
        std::string keyword;
        bool blindExistence;
        string season = "";

        keyword = it.first;

        if (keyword.substr(0, 1) == "0") {
            season = "summer";
        } else if (keyword.substr(0, 1) == "1") {
            season = "winter";
        }

        if (keyword.substr(1, 1) == "0" && _glazingWall->enableMobileProtection()) {
            blindExistence = true;
        } else {
            blindExistence = false;
        }

        calculationBlockLightEnergy(it.second, blindExistence, season);
    };

    std::for_each(_solarFactor.begin(), _solarFactor.end(), funcSolar);
    std::for_each(_lightTransmittance.begin(), _lightTransmittance.end(), funcLight);
}

void SolarFactorXPP50::calculationBlockSolarEnergy(vector<double> &solarFactor, bool blindExistence, string season)
{
    int typeBlind = -1;

    double coefUc = 0, coefAc = 0, coefAw = 0, absCoffre = 0;
    double heightGlazing = 0, widthGlazing = 0;
    double heFS = 0;
    double fsCoffre = 0;

    //input
    double swFlobalAvecSto = 0;
    double sw1AlphaEta = 0, sw2AlphaEta = 0, sw3AlphaEta = 0;
    double sw1Dir = 0, sw1Dif = 0, sw1Ref = 0;
    double sws = 0, sws1 = 0, sws2 = 0, sws3 = 0;
    double sw = 0, sw1 = 0, sw2 = 0, sw3 = 0;

    //Initialization
    coefAc = this->_glazingWall->surfaceRollingShutterAc();

    heightGlazing = this->_glazingWall->height();
    widthGlazing  = this->_glazingWall->width();

    coefAw = widthGlazing/1000 * heightGlazing/1000; // b1206 L10
    coefUc = _roller->coefUc();
    absCoffre = _roller->coefEnergyAbsorption();

    if (this->_mobileProtection != NULL) {
        typeBlind = this->_mobileProtection->getBlinds()[0]->typeIndex();
    }

    heFS = this->_climatic[season]->getHe();
//    fsCoffre = rollerSolarFactor(heFS, coefUc, absCoffre / 100); b102023 p4.4
    fsCoffre = rollerSolarFactor(heFS, coefUc, absCoffre);

    _sc = fsCoffre; // Sc

    if (blindExistence) {
        if (typeBlind == 1) {
            bool trackingMode = this->_mobileProtection->getEnableSolarTracking();

            if (trackingMode) {
                sw1Dir = solarFactor[0];
                sw1Dif = solarFactor[1];
                sw1Ref = solarFactor[2];
                sw2AlphaEta = solarFactor[3];
                sw3AlphaEta = solarFactor[4];
            } else {
                swFlobalAvecSto = solarFactor[0];
                sw1Dir = solarFactor[1];
                sw1Dif = solarFactor[2];
                sw1Ref = solarFactor[3];
                sw1AlphaEta = solarFactor[4];
                sw2AlphaEta = solarFactor[5];
                sw3AlphaEta = solarFactor[6];
            }
        } else {
            sws = solarFactor[0];
            sws1 = solarFactor[1];
            sws2 = solarFactor[2];
            sws3 = solarFactor[3];
        }
    } else {
        sw =  solarFactor[0];
        sw1 = solarFactor[1];
        sw2 = solarFactor[2];
        sw3 = solarFactor[3];
    }

    if (blindExistence) {
        if (typeBlind == 1) {
            sw1Dir = sw1Dir * (coefAw / (coefAw + coefAc));
            sw1Dif = sw1Dif * (coefAw / (coefAw + coefAc));
            sw1Ref = sw1Ref * (coefAw / (coefAw + coefAc));
            sw2AlphaEta = (coefAc * fsCoffre + coefAw * sw2AlphaEta) / (coefAc + coefAw);
            sw3AlphaEta = sw3AlphaEta * (coefAw / (coefAw + coefAc));
            sw1AlphaEta = sw1AlphaEta * (coefAw / (coefAw + coefAc));
            swFlobalAvecSto = (coefAc * fsCoffre + swFlobalAvecSto * coefAw) / (coefAw + coefAc);
        } else {
            sws = (coefAc * fsCoffre + coefAw * sws) / (coefAc + coefAw);
            sws1 = (coefAw / (coefAc + coefAw)) * sws1;
            sws2 = (coefAc * fsCoffre + coefAw * sws2) / (coefAc + coefAw);
            sws3 = (coefAw / (coefAc + coefAw)) * sws3;
        }
    }

    sw = (coefAc * fsCoffre + coefAw * sw) / (coefAc + coefAw);
    sw1 = (coefAw / (coefAc + coefAw)) * sw1;
    sw2 = (coefAc * fsCoffre + coefAw * sw2) / (coefAc + coefAw);
    sw3 = (coefAw / (coefAc + coefAw)) * sw3;

    if (blindExistence) {
        if (typeBlind == 1) {
            bool solarTrackingMode = _mobileProtection->getEnableSolarTracking();

            if (solarTrackingMode) {
                solarFactor =  vector<double> {sw1Dir, sw1Dif, sw1Ref, sw2AlphaEta, sw3AlphaEta};
            } else {
                solarFactor =  vector<double> { swFlobalAvecSto, sw1Dir, sw1Dif, sw1Ref, sw1AlphaEta, sw2AlphaEta, sw3AlphaEta};
            }
        } else {
            solarFactor =  vector<double> { sws, sws1, sws2, sws3};
        }
    } else {
        solarFactor = vector<double> {sw, sw1, sw2, sw3};
    }
}

void  SolarFactorXPP50::calculationBlockLightEnergy(vector<double> &lightTransmistance, bool blindExistence, string season)
{
    double widthGlazing = 0, heightGlazing = 0;
    double coefAw = 0, coefAc = 0;
    double coefTLw = 0, coefTLws = 0, coefTLwDir = 0, coefTLwDif = 0, coefTLwRef = 0, coefTLwRefDir = 0, coefTLwDirDif = 0;

    heightGlazing = this->_glazingWall->height();
    widthGlazing  = this->_glazingWall->width();

    coefAw = widthGlazing/1000 * heightGlazing/1000; // b1206 L10
    coefAc = this->_glazingWall->surfaceRollingShutterAc();

    if (blindExistence) {
        int typeBlind = _mobileProtection->getBlinds()[0]->typeIndex();

        if (blindExistence && typeBlind == 1) {
            bool trackingMode = _mobileProtection->getEnableSolarTracking();

            if (trackingMode) {
                coefTLwDir = lightTransmistance[0];
                coefTLwDirDif = lightTransmistance[1];
                coefTLwDif = lightTransmistance[2];
                coefTLwRef = lightTransmistance[3];
                coefTLwRefDir = lightTransmistance[4];
            } else {
                coefTLws = lightTransmistance[0];
                coefTLwDir = lightTransmistance[1];
                coefTLwDif = lightTransmistance[2];
                coefTLwRef = lightTransmistance[3];
            }
        } else {
            coefTLws = lightTransmistance[0];
        }
    } else {
        coefTLw = lightTransmistance[0];
    }

    coefTLw = coefTLw * (coefAw / (coefAc + coefAw));
    coefTLws = coefTLws * (coefAw / (coefAc + coefAw));
    coefTLwDir = coefTLwDir * (coefAw / (coefAc + coefAw));
    coefTLwDif = coefTLwDif * (coefAw / (coefAc + coefAw));
    coefTLwRef = coefTLwRef * (coefAw / (coefAc + coefAw));
    coefTLwRefDir = coefTLwRefDir * (coefAw / (coefAc + coefAw));

    if (blindExistence) {
        int typeBlind = _mobileProtection->getBlinds()[0]->typeIndex();
        bool trackingMode = _mobileProtection->getEnableSolarTracking();

        if (blindExistence && typeBlind == 1) {
            if (trackingMode) {
                lightTransmistance =  vector<double> {coefTLwDir, coefTLwDirDif, coefTLwDif, coefTLwRef, coefTLwRefDir};
            } else {
                lightTransmistance =  vector<double> {coefTLws, coefTLwDir, coefTLwDif, coefTLwRef};
            }
        } else {
            lightTransmistance =  vector<double> {coefTLws};
        }
    } else {
        lightTransmistance =  vector<double> {coefTLw};
    }
}


inline double SolarFactorXPP50::rollerSolarFactor(double Coeff_h_ext, double U_menuiserie, double Abs_menuiserie)
{
    return Abs_menuiserie * U_menuiserie / Coeff_h_ext;
}

inline double SolarFactorXPP50::opaqueSolarFactor(bool Cal_store, double U_menuiserie, double Sfnue, double Text, double Rext)
{
    int typeBlind = 0;
    int blindPosition = 0;
    double  blindTe = 0, blindAbs1 = 0, blindRe1 = 0;
    double coefFSOpaque = 0;

    bool blindExistence = this->_glazingWall->enableMobileProtection();

    if (blindExistence) {
        typeBlind = _mobileProtection->getBlinds()[0]->typeIndex();
        blindPosition = _mobileProtection->getPositionBlind();
        blindTe = _mobileProtection->getBlinds()[0]->getTe1() / 100;
        blindRe1 = _mobileProtection->getBlinds()[0]->getRe1() / 100;
        blindAbs1 = 1 - blindTe - blindRe1;
    }

    if (blindExistence && blindPosition == 0 && Cal_store) {
        if (typeBlind == 1) {
            coefFSOpaque = Text * Sfnue + (Rext / (10 * ((1 / U_menuiserie) + 0.3))) + (Text * (1 - Sfnue) / (5 * ((1 / U_menuiserie) + 0.3)));
        } else {
            coefFSOpaque = blindTe * Sfnue + (blindAbs1 / (10 * ((1 / U_menuiserie) + 0.3))) + (blindTe * (1 - Sfnue) / (5 * ((1 / U_menuiserie) + 0.3)));
        }
    } else {
        coefFSOpaque = Sfnue;
    }

    return coefFSOpaque;
}

void SolarFactorXPP50::calculationUValue()
{
    double coefUw = 0, coefUc = 0, coefUws = 0;
    double coefLp = 0, coefPsiP = 0;
    double coefUpOpaque = 0, deltaRCoffre = 0, deltaR = 0;

    //Initialization
    bool isOpaqueExistence = _glazingWall->withOpaquePart();
    bool isRollerExistence = _glazingWall->rollerExistence();
    bool isBlindExistence = _glazingWall->enableMobileProtection();

    double glassSurface = _glazingWall->surfaceGlazingAg();
    double frameSurface = _glazingWall->surfaceGlazingAf();
    double opaqueSurface = _glazingWall->surfaceOpaqueWallAp();
    double rollerSurface = _glazingWall->surfaceRollingShutterAc();

    if (isRollerExistence) {
        coefUc = _roller->coefUc();
    }

    double coefUg = _glazingXP50->coefUgAverage();

    double glassHeight = _glazingWall->height()*0.001;  //bug1205 p16
    double glassWidth  = _glazingWall->width()*0.001;

    double windowSurface = glassWidth * glassHeight;

    double glassPerimeter = _glazingXP50->totalPerimetersLg();

    double coefPhiG = _frame->coefBinding();
    double ufAverageFrame = _frame->ufAverage();

    if (isBlindExistence) {
        deltaR = _mobileProtection->deltalR();
    }

    if (isOpaqueExistence) {
        coefLp = _opaqueWall->lpPerimeter();
        coefPsiP = _opaqueWall->coefBinding();
        coefUpOpaque = this->_opaqueWall->coefUp();
    }

    if (isOpaqueExistence && isRollerExistence) {
        coefUw = (glassSurface * coefUg + frameSurface * ufAverageFrame + opaqueSurface * coefUpOpaque + rollerSurface * coefUc + glassPerimeter * coefPhiG + coefLp * coefPsiP) / (windowSurface + rollerSurface);
    } else if (isRollerExistence) {
        coefUw = (glassSurface * coefUg + frameSurface * ufAverageFrame + rollerSurface * coefUc + glassPerimeter * coefPhiG) / (windowSurface + rollerSurface);
    } else if (isOpaqueExistence) {
        coefUw = (glassSurface * coefUg + frameSurface * ufAverageFrame + opaqueSurface * coefUpOpaque + glassPerimeter * coefPhiG + coefLp * coefPsiP) / (windowSurface);
    } else {
        coefUw = (glassSurface * coefUg + frameSurface * ufAverageFrame + glassPerimeter * coefPhiG) / windowSurface;
    }

    if (isRollerExistence && !isBlindExistence) {
        coefUw = 1 / ((1 / coefUw) + deltaRCoffre);
    }

    if (isBlindExistence && isRollerExistence) {
        coefUws = 1 / ((1 / coefUw) + (deltaR + deltaRCoffre));
    } else if (isBlindExistence) {
        coefUws = 1 / ((1 / coefUw) + deltaR);
    }

    _uValue.clear();
    _uValue.push_back(coefUw);
    _uValue.push_back(coefUws);
}

void SolarFactorXPP50::setFrame(Frame *frame)
{
    _frame = frame;
}

void SolarFactorXPP50::setGlazingWall(GlazingWall *glazingWall)
{
    _glazingWall = glazingWall;
}

void SolarFactorXPP50::setGlazingXP50(GlazingXP50 *glazingXP50)
{
    _glazingXP50 = glazingXP50;
}

void SolarFactorXPP50::setMobileProtection(MobileProtection *mobileProtection)
{
    _mobileProtection = mobileProtection;
}

void SolarFactorXPP50::setOpaqueWall(OpaqueWall *opaqueWall)
{
    _opaqueWall = opaqueWall;
}

void SolarFactorXPP50::setRoller(Roller *roller)
{
    _roller = roller;
}

void SolarFactorXPP50::setClimatic(const map<string, ClimateConditions::Climate *> &climatic)
{
    _climatic = climatic;
}

map<std::string, vector<double> > SolarFactorXPP50::solarFactor() const
{
    return _solarFactor;
}

map<std::string, vector<double> > SolarFactorXPP50::lightTransmittance() const
{
    return _lightTransmittance;
}

map<std::string, vector<double> > SolarFactorXPP50::solarFactorBackUp() const
{
    return _solarFactor_backup;
}

map<std::string, vector<double> > SolarFactorXPP50::lightTransmittanceBackUp() const
{
    return _lightTransmittance_backup;
}

vector<double> SolarFactorXPP50::component() const
{
    return _components;
}

vector<double> SolarFactorXPP50::uValue() const
{
    return _uValue;
}

void SolarFactorXPP50::workInThread(int angle1, int angle2, double por)
{
    std::map<int, vector<vector<double> >> TRR{};
    vector<int> angle = {0, 15, 30, 45, 60, 75, 90};

    double inclineGlazing = this->_glazingWall->incline();

    threadPor.reset(new double(por));

    VenetianCalculationXPP50 *calculator = new VenetianCalculationXPP50();

    TRR = calculator->calculate(inclineGlazing, _mobileProtection->getDistanceBlindGlazing(), _mobileProtection->getWidthBlade(), _mobileProtection->getDistacneAxises(),
                                _mobileProtection->getCharacteristicsBlindVenetian()[0], _mobileProtection->getCharacteristicsBlindVenetian()[1], _mobileProtection->getCharacteristicsBlindVenetian()[2],
            _mobileProtection->getCharacteristicsBlindVenetian()[3], _mobileProtection->getCharacteristicsBlindVenetian()[4], _mobileProtection->getCharacteristicsBlindVenetian()[5],
            _mobileProtection->getCharacteristicsBlindVenetian()[6], _mobileProtection->getCharacteristicsBlindVenetian()[7],
            angle[angle1], angle[angle2]);

    string key = std::to_string(angle1) + std::to_string(angle2);

    calculationBaySolarFactor(TRR[Object::ModuleEnergy::Solar], key);
    calculationBaySolarFactorLight(TRR[Object::ModuleEnergy::Light], key);
}

}
}
