#include "solarcharacteristics.h"

using namespace VD6::Calculation;

vector<VD6::Common::Object::EnergyCharacteristics> SolarCharacteristics::calculationTRAEMValues(vector<VD6::Common::Object::EnergyCharacteristics> glass,
                                                                                          VD6::Common::Object::EnergyCharacteristics object,
                                                                                          unsigned int posObj)
{
    VD6::Common::Object::EnergyCharacteristics result;
    vector <VD6::Common::Object::EnergyCharacteristics> traem;

    unsigned int numberGlass = glass.size();
    unsigned int numberObject = 1;
    unsigned int total = numberObject + numberGlass;

    unsigned int ii = 0;

    if (posObj < 0) {
        posObj = 0 /*- 1*/;
    }

    if (numberObject > 0) {
        for (unsigned int i = 0; i < total; i++) {
            if (i == posObj) {
                for (unsigned int j = 0; j < 2; j++) {
                    result.transmission[j] = object.transmission[j];             //warning at(index)
                    result.reflection[j] = object.reflection[j];
                    result.absorption[j] = object.absorption[j];
                    result.emissivity[j] = object.emissivity[j];
                }

                traem.push_back(result);
            } else {
                if (i > posObj) {
                    ii = i - 1;
                } else {
                    ii = i;
                }

                for (unsigned int j = 0; j < 2; j++) {
                    result.transmission[j] = glass.at(ii).transmission[j];              //warning at(index)
                    result.reflection[j] = glass.at(ii).reflection[j];
                    result.absorption[j] = glass.at(ii).absorption[j];
                    result.emissivity[j] = glass.at(ii).emissivity[j];
                }

                traem.push_back(result);
            }
        }

        return traem;
    } else {
        return glass;
    }
}

/* Description: The function is constructed from solver Gaussian,
 * Parameter input: matrix is established from characteristics energy of glass and blind or obstacle.
 * Output: Parameter using for calculation energy global.
*/
vector<double> SolarCharacteristics::resolutionSystem(vector<vector<double> > &matrixCX)
{
    int n = matrixCX.size();

    for (int i = 0; i < n; i++) {
        // Search for maximum in this column
        double maxEl = fabs(matrixCX[i][i]);
        int maxRow = i;

        for (int k = i + 1; k < n; k++) {
            if (fabs(matrixCX[k][i]) > maxEl) {
                maxEl = fabs(matrixCX[k][i]);
                maxRow = k;
            }
        }

        // Swap maximum row with current row (column by column)
        for (int k = i; k < n + 1; k++) {
            double tmp = matrixCX[maxRow][k];
            matrixCX[maxRow][k] = matrixCX[i][k];
            matrixCX[i][k] = tmp;
        }

        // Make all rows below this one 0 in current column
        for (int k = i + 1; k < n; k++) {
            double c = -matrixCX[k][i] / matrixCX[i][i];

            for (int j = i; j < n + 1; j++) {
                if (i == j) {
                    matrixCX[k][j] = 0;
                } else {
                    matrixCX[k][j] += c * matrixCX[i][j];
                }
            }
        }
    }

    // Solve equation Cy=X for an upper triangular matrix A
    vector<double> y(n);

    for (int i = n - 1; i >= 0; i--) {
        y[i] = matrixCX[i][n] / matrixCX[i][i];

        for (int k = i - 1; k >= 0; k--) {
            matrixCX[k][n] -= matrixCX[k][i] * y[i];
        }
    }

    return y;
}

int SolarCharacteristics::getPositionBlindOrObs() const
{
    return _positionBlindOrObs;
}

void SolarCharacteristics::setPositionBlindOrObs(int value)
{
    _positionBlindOrObs = value;
}

vector<Object::EnergyCharacteristics> SolarCharacteristics::getListGlass() const
{
    return _listGlass;
}

void SolarCharacteristics::setListGlass(const vector<Object::EnergyCharacteristics> &value)
{
    _listGlass = value;
}

/* Description: Calculate characterictics energy base on matrix is established (TRA)
 * Parameter input:
 *                         - type: the parameters allow chooses project calculate. it's can
 *                               + Only list glass (typeProject = 0)
 *                               + List glass and blind (typeProject = 1)
 *                               + List glass and Object (typeProject = 2)
 *                         - TRA : maxtrix is constructed from parameters characteristic energy glass, obstacle and blind.
 * Output: farme data with format: Transmission<<Reflection<<Absorption<<EffectiveAbsorption[index posision in list]
*/
vector<double> SolarCharacteristics::characteristicsEnergy(vector<VD6::Common::Object::EnergyCharacteristics> TRA, Object::ProjectType type)
{
    unsigned int level;
    unsigned int total;   //number glass with object

    double tmpTransmission;
    double tmpReflection;
    double tmpAbsorption;
    vector<double> resultData;
    vector<double> tmpEffectiveAbsorption;
    vector<double> tmpEffectiveReflection;
    vector<double> globalCharacteristicEnergy;

    double vitrageAbsorption = 0;
    double obstacleReflection = 0;
    double obstacleTransmission = 0;
    double swapTmp = 0;

    total = TRA.size();
    level = total * 3;

    tmpTransmission = 0;
    tmpReflection = 0;
    tmpAbsorption = 0;

    tmpEffectiveAbsorption.clear();
    globalCharacteristicEnergy.clear();
    tmpEffectiveReflection.clear();

    vector<vector<double> > matrixCX = establishMatrix(TRA);
    globalCharacteristicEnergy = resolutionSystem(matrixCX);

    //output
    switch (type) {
    case 0:  //only glass
        tmpTransmission = globalCharacteristicEnergy[level - 1];

        for (unsigned int at = 0; at < total ; at++) {
            tmpAbsorption = tmpAbsorption + globalCharacteristicEnergy[at * 3 + 1];
            tmpEffectiveAbsorption.push_back(globalCharacteristicEnergy[3 * at + 1]);
        }

        tmpReflection = 1 - tmpAbsorption - tmpTransmission;
        break;

    case 1: //with Blind
        tmpTransmission = globalCharacteristicEnergy[level - 1];

        for (unsigned int at = 0; at < total ; at++) {
            tmpAbsorption = tmpAbsorption + globalCharacteristicEnergy[at * 3 + 1];
            tmpEffectiveAbsorption.push_back(globalCharacteristicEnergy[3 * at + 1]);
        }

        tmpReflection = 1 - tmpAbsorption - tmpTransmission;

        break;

    case 2: //with Obstacle


        for (unsigned int at = 0; at < total ; at++) {
            if (at < _listGlass.size()) {
                vitrageAbsorption = vitrageAbsorption + globalCharacteristicEnergy[at * 3 + 1];
            }

            tmpEffectiveAbsorption.push_back(globalCharacteristicEnergy[3 * at + 1]);
            tmpEffectiveReflection.push_back(globalCharacteristicEnergy[3 * at]);
        }

        obstacleTransmission = globalCharacteristicEnergy[level - 1];

        // swap tranmission with last of effective absorption

//        if (_isOpaque){
//            swapTmp = obstacleTransmission;
//            obstacleTransmission = tmpEffectiveAbsorption[total - 1];
//            tmpEffectiveAbsorption[total - 1] = swapTmp;
//        }


        obstacleReflection = 1 - obstacleTransmission - vitrageAbsorption - tmpEffectiveAbsorption[total - 1];

        tmpTransmission = obstacleTransmission;
        tmpAbsorption = vitrageAbsorption + tmpEffectiveAbsorption[total - 1];
        tmpReflection = obstacleReflection;

        break;

    default:
        break;
    }

    this->_globalTransmission = tmpTransmission;
    this->_globalAbsorption = tmpAbsorption;
    this->_globalReflection =  tmpReflection;
    this->_effectiveAbsorption = tmpEffectiveAbsorption;

    resultData.push_back(tmpTransmission);
    resultData.push_back(tmpReflection);
    resultData.push_back(tmpAbsorption);

    std::vector<double>::iterator it;

    for (it = tmpEffectiveAbsorption.begin(); it < tmpEffectiveAbsorption.end(); it++) {
        resultData.push_back(*it);
    }

    double qi = 0;
    double qe = 0;

    if (type == 0) // only glass
    {
        calculateQiQe(qi, qe, resultData, _listGas, _listGlassVD);
        resultData.push_back(qi);
        resultData.push_back(qe);
    }

    return resultData;
}

void SolarCharacteristics::calculateQiQe(double &qi, double &qe, vector<double> result, vector<GasGap *> listGas, vector<GlassVD *> listGlass)
{
    double he = 23;
    double hi = 3.6 + ((4.4 * 0.837)/0.837);
    double coefGlass  = 1;

    vector<double> hs(2);
    vector<double> listAlphaE;
    for (int i = 3; i < result.size() ; i++)
    {
        listAlphaE.push_back(result.at(i));
    }

    if (listGlass.size() == 1) // simple vitrage
    {
        qi = listAlphaE.at(0)*(hi/(hi+he));
        qe = listAlphaE.at(0) - qi;
    }
    else if (listGlass.size() == 2) // double vitrage
    {
        hs = calculateHs(listGas,listGlass); //stadard EN 673
        double glass1Thickness = listGlass.at(0)->getThicknessTotal();
        //double gasThickness = listGas.at(0)->getThickness();
        double glass2Thickness = listGlass.at(1)->getThicknessTotal();
        double coefLamda;
        double R;
        double Lamda; // conductance
        if (listGas.at(0)->getType() == 0) // air
        {
            coefLamda = 0.025; // (W/m.K)
        }
        else { // mixed ( argon 90%)
            coefLamda = 0.017;
        }
        R = (glass1Thickness/1000)/coefGlass + 1/hs[0] + (glass2Thickness/1000)/coefGlass;
        Lamda = 1/R;

        qi = ((listAlphaE.at(0) + listAlphaE.at(1))/he + listAlphaE.at(1)/Lamda)/(1/hi + 1/he + 1/Lamda);
        qe = (listAlphaE.at(0) + listAlphaE.at(1)) - qi;

    }
    else if (listGlass.size() == 3) // triple vitrage
    {
        hs = calculateHs(listGas,listGlass); //stadard EN 673
        double glass1Thickness = listGlass.at(0)->getThicknessTotal();
        //double gas1Thickness = listGas.at(0)->getThickness();
        double glass2Thickness = listGlass.at(1)->getThicknessTotal();
        //double gas2Thickness = listGas.at(1)->getThickness();
        double glass3Thickness = listGlass.at(2)->getThicknessTotal();

//        double coefLamda1 = (listGas.at(0)->getType() == 0 ? 0.025 : 0.017852);
//        double coefLamda2 = (listGas.at(1)->getType() == 0 ? 0.025 : 0.017852);
        //double R12 = (glass1Thickness/1000)/1 + (gas1Thickness/1000)/coefLamda1 + (glass2Thickness/1000)/1;
        //double R23 = (glass2Thickness/1000)/1 + (gas2Thickness/1000)/coefLamda2 + (glass3Thickness/1000)/1;
        double R12 = (glass1Thickness/1000)/coefGlass   + 1/hs[0] + (glass2Thickness/2/1000)/coefGlass;
        double R23 = (glass2Thickness/2/1000)/coefGlass + 1/hs[1] + (glass3Thickness/1000)/coefGlass;

        double Lamda12 =1/R12;
        double Lamda23 = 1/R23;

        qi = (listAlphaE.at(2)/Lamda23 +(listAlphaE.at(2) + listAlphaE.at(1))/Lamda12 + (listAlphaE.at(0) + listAlphaE.at(1) + listAlphaE.at(2))/he)
                / (1/hi + 1/he + 1/Lamda12 + 1/Lamda23);

        qe = (listAlphaE.at(0) + listAlphaE.at(1) + listAlphaE.at(2)) - qi;
    }

}

vector<double> SolarCharacteristics::calculateHs(vector<GasGap *> listGas, vector<GlassVD *> listGlass)
{
    //b1206 EN673
    vector<double> hg(2); // Conductance convective du gaz
    vector<double> hr(2); // Conductance radiative du gaz
    vector<double> hs(2,0); // Conductance thermique totale
    vector<double> Gr(2); // Nombre de Grashof
    vector<double> Nu(2); // Nombre de Nusselt Nu
    vector<double> delT(2), viscosity(2),density(2), Pr(2), lambda(2), cp(2);
    vector<double> emis(4,0); // Emissivité corrigée d'après EN 12898
    double concentrationAir, concentrationArg , concentrationKr, concentrationXe;
    double dtT0   = 0, dtT1 = 0;
    double Ttemp  = 15;
    double Tm     = 283;
    double epsi   = 0.001;
    double g      = 9.81;
    double incl   = _incline;
    double sigma  = 5.67*pow(10,-8);

    hg[0]   = 0;
    hg[1]   = 0;

    double constA = (incl <= 45) ? ((0.06*incl/-45)+0.16) : ((0.065*incl/-45)+0.165);
    double constn = (incl <= 45) ? ((0.03*incl/45)+0.28) : ((0.07*incl/45)+0.24);
    // viscosity
    double nuyAir = 1.761*pow(10,-5);
    double nuyArg = 2.164*pow(10,-5);
    double nuyKry = 2.4*pow(10,-5);
    double nuyXe  = 2.226*pow(10,-5);

    //density
    double rhoAir = 1.232;
    double rhoArg = 1.699;
    double rhoKry = 3.56;
    double rhoXe  = 5.689;

    // conductivity
    double lamdaAir = 2.496*pow(10,-2);
    double lamdaArg = 1.684*pow(10,-2);
    double lamdaKry = 0.9*pow(10,-2);
    double lamdAXe  = 0.529*pow(10,-2);

     // specific heat capacity
    double cpAir    = 1008;
    double cpArg    = 519;
    double cpKry    = 245;
    double cpXe     = 161;

    //hr
    vector<double> emn(4,0);
    emn[0] = listGlass.at(0)->getEmn2() / 100;
    emn[1] = listGlass.at(1)->getEmn1() / 100;
    if (listGas.size() == 2) {
        emn[2] = listGlass.at(1)->getEmn2() / 100;
        emn[3] = listGlass.at(2)->getEmn1() / 100;
    }
    for (int j = 0; j < 4; j++) {
        emis[j] = 1.1887*emn[j] - 0.4967*pow(emn[j],2) + 0.245*pow(emn[j],3);
    }
    hr[0] = 4*sigma * pow((1/emis[0] + 1/emis[1] - 1),-1) * pow(Tm,3);
    hr[1] = 4*sigma * pow((1/emis[2] + 1/emis[3] - 1),-1) * pow(Tm,3);

    //Calcul_concentration des gaz
    if (listGas.size() > 0 ) {
        if (listGas.size() == 1) {
            delT[0] = Ttemp ;
            delT[1] = 0;
        } else if (listGas.size() == 2) {
            delT[0] = Ttemp / 2;
            delT[1] = Ttemp / 2;
        }

        for (int i = 0; i < listGas.size() ; i++) {
            concentrationArg = listGas.at(0)->getArgon()   / 100.0;
            concentrationKr  = listGas.at(0)->getKrypton() / 100.0;
            concentrationXe  = listGas.at(0)->getXenon()   / 100.0;
            concentrationAir = 1.0 - concentrationArg - concentrationKr - concentrationXe;
            viscosity[i]    = concentrationArg * nuyArg   + concentrationKr * nuyKry   + concentrationXe * nuyXe   + concentrationAir * nuyAir;
            density[i]      = concentrationArg * rhoArg   + concentrationKr * rhoKry   + concentrationXe * rhoXe   + concentrationAir * rhoAir;
            lambda[i]       = concentrationArg * lamdaArg + concentrationKr * lamdaKry + concentrationXe * lamdAXe + concentrationAir * lamdaAir;
            cp[i]           = concentrationArg * cpArg    + concentrationKr * cpKry    + concentrationXe * cpXe    + concentrationAir * cpAir;
            Pr[i]           = viscosity[i] * cp[i] / lambda[i];
            Gr[i]           = g * pow((listGas.at(i)->getThickness()/1000),3) * delT[i] * pow(density[i],2) / (Tm * pow(viscosity[i],2));
            Nu[i]           = constA * pow((Gr[i] * Pr[i]),constn);
            (Nu[i] < 1) ? Nu[i] = 1 : Nu[i];
            hg[i]           = Nu[i] * lambda[i] / (listGas.at(i)->getThickness()/1000);
            hs[i]           = hg[i] + hr[i];
        }
        bool Flag = false;
        int count = 0;
        if (listGas.size() == 2) {
            while ( !Flag && count < 200) {
                dtT0    = delT[0];
                dtT1    = delT[1];
                delT[0] = 15*hs[1] / (hs[0] + hs[1]);
                delT[1] = 15*hs[0] / (hs[0] + hs[1]);
                for (int i = 0; i < listGas.size(); i++) {
                    Gr[i]           = g * pow((listGas.at(i)->getThickness()/1000),3) * delT[i] * pow(density[i],2) / (Tm * pow(viscosity[i],2));
                    Nu[i]           = constA * pow((Gr[i] * Pr[i]),constn);
                    (Nu[i] < 1) ? Nu[i] = 1 : Nu[i];
                    hg[i]           = Nu[i] * lambda[i] / (listGas.at(i)->getThickness()/1000);
                    hs[i]           = hg[i] + hr[i];
                }
                count++;
                if (fabs(delT[0] - dtT0) < epsi || fabs(delT[1] - dtT1) < epsi ) {
                    Flag = true;
                }
            }
       }
    }

    return hs;
}

vector<double> SolarCharacteristics::getEnergyGlobal()
{
    vector<double>resultData;

    resultData.push_back(_globalTransmission);
    resultData.push_back(_globalReflection);
    resultData.push_back(_globalAbsorption);

    return resultData;
}

/*
 * Description: input data characterictics energy spectral (transmission, reflection and Absorption) for module
 * calculation.
 * Input Parameter: type: select object put data ( 0: glass; 1: blind and 2: obstacle)
 * Output: none
*/

void SolarCharacteristics::setPostisionObject(int &pos)
{
    this->_positionBlindOrObs = pos;
}

void SolarCharacteristics::setCharacteristicsObject(vector<Object::EnergyCharacteristics> characteristic, Object::ProjectType type)
{
    switch (type) {
    case 0:
        this->_listGlass = characteristic;
        break;

    case 1:
        this->_listBlind = characteristic[0];
        break;

    case 2:
        this->_listObstacle = characteristic[0];
        break;

    default:
        break;
    }
}

SolarCharacteristics::SolarCharacteristics()
{
    _globalAbsorption = 0;
    _positionBlindOrObs = - 1;
}

SolarCharacteristics::~SolarCharacteristics()
{
}

void SolarCharacteristics::setGasAndGlassThickness(GlassVD *glass1Data, GlassVD *glass2Data, GlassVD *glass3Data, GlassVD *glass4Data,
                             GasGap *gas1, GasGap *gas2, GasGap *gas3, int numGlass, Object::ModuleEnergy mode)
{
    vector<GasGap *> listGas;
    vector<GlassVD *> listGlassVD;
    if (mode == Object::ModuleEnergy::Solar) {
        if (numGlass >= 1)
        {
            listGlassVD.push_back(glass1Data);
        }
        if (numGlass >= 2)
        {
            listGlassVD.push_back(glass2Data);
            listGas.push_back(gas1);
        }
        if (numGlass >= 3)
        {
            listGlassVD.push_back(glass3Data);
            listGas.push_back(gas2);
        }
        if (numGlass >= 4)
        {
            listGlassVD.push_back(glass4Data);
            listGas.push_back(gas3);
        }
    }
    _listGas = listGas;
    _listGlassVD = listGlassVD;
}

vector<vector<double> > SolarCharacteristics::execute(int numGlass,
                                                      GlassVD *glass1Data, GlassVD *glass2Data, GlassVD *glass3Data, GlassVD *glass4Data,
                                                      bool blindExistence, int positionBlind, BlindVD *blindData,
                                                      bool obstacleExistence, vector<bool> obstaclesExistence, vector<ObstacleVD *> dataObstacles,
                                                      Object::ModuleEnergy mode, bool slidingSashEnable)
{


    if(obstaclesExistence.size() != 0 ){
        _isOpaque = obstaclesExistence[0];
    }
    vector<Object::EnergyCharacteristics> glasses;
    vector<vector<double> > result;

    if (mode == Object::ModuleEnergy::Solar) {
        if (numGlass >= 1 ) {
            glasses.push_back(Object::EnergyCharacteristics(glass1Data->getTe(), glass1Data->getRe1(), glass1Data->getRe2()));
        }

        if (numGlass >= 2 ) {
            glasses.push_back(Object::EnergyCharacteristics(glass2Data->getTe(), glass2Data->getRe1(), glass2Data->getRe2()));
        }

        if (numGlass >= 3 ) {
            glasses.push_back(Object::EnergyCharacteristics(glass3Data->getTe(), glass3Data->getRe1(), glass3Data->getRe2()));
        }

        if (numGlass >= 4 ) {
            glasses.push_back(Object::EnergyCharacteristics(glass4Data->getTe(), glass4Data->getRe1(), glass4Data->getRe2()));
        }
    } else {
        if (numGlass >= 1 ) {
            glasses.push_back(Object::EnergyCharacteristics(glass1Data->getTl(), glass1Data->getRl1(), glass1Data->getRl2()));
        }

        if (numGlass >= 2 ) {
            glasses.push_back(Object::EnergyCharacteristics(glass2Data->getTl(), glass2Data->getRl1(), glass2Data->getRl2()));
        }

        if (numGlass >= 3 ) {
            glasses.push_back(Object::EnergyCharacteristics(glass3Data->getTl(), glass3Data->getRl1(), glass3Data->getRl2()));
        }

        if (numGlass >= 4 ) {
            glasses.push_back(Object::EnergyCharacteristics(glass4Data->getTl(), glass4Data->getRl1(), glass4Data->getRl2()));
        }
    }

    _listGlass = glasses;

    result.push_back(calculationEnergy(Object::ProjectType::OnlyGlass));

    if (blindExistence || obstacleExistence) {
        if (blindExistence && !obstacleExistence) {
            if (!slidingSashEnable) {
                _positionBlindOrObs = positionBlind;
            } else {
                _positionBlindOrObs = positionBlind * _listGlass.size();
            }

            if (mode == Object::ModuleEnergy::Solar) {
                _listBlind = (Object::EnergyCharacteristics(blindData->getTe1(), blindData->getRe1(), blindData->getTe2(), blindData->getRe2()));
            } else {
                _listBlind = (Object::EnergyCharacteristics(blindData->getTl(), blindData->getRl1(), blindData->getTl(), blindData->getRl2()));
            }

            result.push_back(calculationEnergy(Object::ProjectType::WithBlind));
        } else if (!blindExistence && obstacleExistence) {
            _positionBlindOrObs = numGlass;

            for (int indexObs = 0; indexObs < obstaclesExistence.size(); indexObs++) {
                if (obstaclesExistence[indexObs]){
                    _listObstacle = (Object::EnergyCharacteristics(dataObstacles[indexObs]->te(), dataObstacles[indexObs]->re1(), dataObstacles[indexObs]->re2()));

                    result.push_back(calculationEnergy(Object::ProjectType::WithObstacle));
                }
            }
        } else {
            _positionBlindOrObs = positionBlind;

            if (mode == Object::ModuleEnergy::Solar) {
                _listBlind = (Object::EnergyCharacteristics(blindData->getTe1(), blindData->getRe1(), blindData->getTe2(), blindData->getRe2()));
            } else {
                _listBlind = (Object::EnergyCharacteristics(blindData->getTl(), blindData->getRl1(), blindData->getTl(), blindData->getRl2()));
            }

            for (int indexObs = 0; indexObs < obstaclesExistence.size(); indexObs++) {
                if (obstaclesExistence[indexObs]){
                    _listGlass.push_back(Object::EnergyCharacteristics(dataObstacles[indexObs]->te(), dataObstacles[indexObs]->re1(), dataObstacles[indexObs]->re2()));

                    result.push_back(calculationEnergy(Object::ProjectType::WithBlind));

                    _listGlass.pop_back();
                }
            }
        }
    }

    return result;
}

/* Description: Passing parameters in module through class ObjectSolarCharacterictics (reference Class ObjectSolarCharacteristics)
 * Parameters:
 *                  type - Input data passing is characterictics Light or characterictics Solar.
 *                  data - Include glass, blind, obstacle is defined in  class  ObjectSolarCharacterictics and position object.
 *
 */
void SolarCharacteristics::setDataObject(Object::ObjectSolarCharacteristics *data, Object::ModuleEnergy type)
{

//    for (unsigned int i = 0; i < data->_listGlass.size(); i++) {
//        GlassVD *glass = data->_listGlass.at(i);

//        if (type == 0) {
//            Object::EnergyCharacteristics  characterictics = Object::EnergyCharacteristics(glass->getTe(), glass->getRe1(), glass->getRe2());
//            _listGlass.push_back(characterictics);
//        } else {
//            Object::EnergyCharacteristics  characterictics = Object::EnergyCharacteristics(glass->getTl(), glass->getRl1(), glass->getRl2());
//            _listGlass.push_back(characterictics);
//        }
//    }

//    if (type == 0) {
//        if (data->_blind != NULL) {
//            _listBlind = (Object::EnergyCharacteristics(data->_blind->getTe1(), data->_blind->getRe1(), data->_blind->getTe2(), data->_blind->getRe2()));
//        }

//        if (data->_obstacle != NULL) {
//            _listObstacle = (Object::EnergyCharacteristics(data->_obstacle->te(), data->_obstacle->re1(), data->_obstacle->re2()));
//        }
//    } else {
//        if (data->_blind != NULL) {
//            _listBlind = (Object::EnergyCharacteristics(data->_blind->getTl(), data->_blind->getRl1(), data->_blind->getRl2()));
//        }
//    }

//    _positionBlindOrObs = data->_positionBlindOrObs;

    _listGlass = vector<Object::EnergyCharacteristics> {};
    for (unsigned int i = 0; i < data->_listGlass.size(); i++) {
           GlassVD *glass = data->_listGlass.at(i);

           if (type == 0) {
               Object::EnergyCharacteristics  characterictics = Object::EnergyCharacteristics(glass->getTe(), glass->getRe1(), glass->getTe(), glass->getRe2());
               _listGlass.push_back(characterictics);
           } else {
               Object::EnergyCharacteristics  characterictics = Object::EnergyCharacteristics(glass->getTl(), glass->getRl1(), glass->getTl(), glass->getRl2());
               _listGlass.push_back(characterictics);
           }
       }

       if (type == 0) {
           if (data->_blind != NULL) {
               _listBlind = (Object::EnergyCharacteristics(data->_blind->getTe1(), data->_blind->getRe1(),data->_blind->getTe2(), data->_blind->getRe2()));
           }

           if (data->_obstacle != NULL) {
               _listObstacle = (Object::EnergyCharacteristics(data->_obstacle->te(), data->_obstacle->re1(), data->_obstacle->te(), data->_obstacle->re2()));
           }
       } else {
           if (data->_blind != NULL) {
               _listBlind = (Object::EnergyCharacteristics(data->_blind->getTl(), data->_blind->getRl1(), data->_blind->getTl(), data->_blind->getRl2()));
           }
       }

       _positionBlindOrObs = data->_positionBlindOrObs;
}

/* Description: this is main function of module, has mission calculate characterictics energy with parameters passing module
 * The result return characteristics energy of each object (glass, blind or obtacle) and characteristics enegy global of all them.
 * Parameters input:
 *                  - type: the parameters allow chooses project calculate. it's can
 *                               + Only list glass (typeProject = 0)
 *                               + List glass and blind (typeProject = 1)
 *                               + List glass and Object (typeProject = 2)
 * Output: farme data with format: Transmission<<Reflection<<Absorption<<EffectiveAbsorption[index posision in list]
 */
vector<double> SolarCharacteristics::calculationEnergy(Object::ProjectType type)
{
    vector<VD6::Common::Object::EnergyCharacteristics> TRA;

    switch (type) {
    case 0: //Object::Project::onlyGlass:                                                                             //only glass
        TRA = _listGlass;
        break;

    case 1: { //Object::Project::withBlind:
        //With Store
        TRA = calculationTRAEMValues(_listGlass, _listBlind, _positionBlindOrObs);
        break;
    }

    case 2: { //Object::Project::withObstacle:
        unsigned int outside = _listGlass.size();                              //warning pos
        TRA = calculationTRAEMValues(_listGlass, _listObstacle, outside);
        break;
    }
    case 3: {
        //both Store and Obstacle
        _listGlass.push_back(_listObstacle);
        TRA = calculationTRAEMValues(_listGlass, _listBlind, _positionBlindOrObs);
        type = Object::ProjectType::WithBlind;
        break;
    }

    default:
        break;
    }

    return characteristicsEnergy(TRA, type);
}

vector<double> SolarCharacteristics::getEffectiveAbsorption()
{
    return this->_effectiveAbsorption;
}

VD6::Common::Object::Energy SolarCharacteristics::getGlobalEnergy()
{
    VD6::Common::Object::Energy global(_globalTransmission, _globalReflection, _globalAbsorption);
    return  global;
}

/* Description: Construction matrix for calculation light (solar) characteristics energy through solver Gaussian.
 *  Parameter input: list object ( glass , blind or obstacle) is calculated parameters energy.
 * Output: The matrix of calculation gaussian
*/

vector<vector<double> > SolarCharacteristics::establishMatrix(vector<VD6::Common::Object::EnergyCharacteristics> tra)
{
    int col;
    int row;

    int numGB = tra.size();
    int level = 3 * numGB;

    vector<double> line(level + 1, 0);
    vector< vector<double> > matrixCX(level, line);
    vector<double> result(level);

    //vector C
    for (row = 0; row < level ; row++) {
        matrixCX[row][level] = 0;
        for (col = 0 ; col < level ; col++) {
            if (row == col) {
                matrixCX[row][col] = 1;
            } else {
                matrixCX[row][col] = 0;
            }
        }

        switch (row % 3) {
        case 0:
            if (row / 3 < numGB - 1) {
                matrixCX[row][row + 3] = - tra.at(row / 3).transmission[1];
            }
            if (row / 3 > 0) {
                matrixCX[row][row - 1] = - tra.at(row / 3).reflection[0];
            }
            break;

        case 1:
            if (row / 3 < numGB - 1) {
                matrixCX[row][row + 2] = - tra.at(row / 3).absorption[1];
            }
            if (row / 3 > 0) {
                matrixCX[row][row - 2] = - tra.at(row / 3).absorption[0];
            }
            break;

        case 2:
            if (row / 3 < numGB - 1) {
                matrixCX[row][row + 1] = - tra.at(row / 3).reflection[1];
            }
            if (row / 3 > 0) {
                matrixCX[row][row - 3] = - tra.at(row / 3).transmission[0];
            }
            break;

        default:
            break;
        }
    }

    //vector X
    matrixCX[0][level] = tra.at(0).reflection[0];
    matrixCX[1][level] = tra.at(0).absorption[0];
    matrixCX[2][level] = tra.at(0).transmission[0];

    //return C|X
    return matrixCX;
}

void SolarCharacteristics::setIncline(double incline)
{
    _incline = incline;
}

double SolarCharacteristics::getincline() const
{
    return _incline;
}
