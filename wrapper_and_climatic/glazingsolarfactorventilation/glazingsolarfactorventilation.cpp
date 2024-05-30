#include "glazingsolarfactorventilation.h"
using namespace VD6::Calculation;

GlazingSolarFactorVentilation::GlazingSolarFactorVentilation()
{
    _data = NULL;
    _solarFactor = 0;
    _gth = 0;
    _gc = 0;
    _gv = 0;
    _hc.clear();
    _hr.clear();
    _hcn = 0;
}

GlazingSolarFactorVentilation::~GlazingSolarFactorVentilation()
{
    delete _data;
}

vector<double> GlazingSolarFactorVentilation::calculationGlazingSolarFactorVentilation()
{
    vector<double> result;
    if (_data->_climate) {

        ClimateConditions::Climate *condition;
        condition = new ClimateConditions::Climate(_data->_climate);

        Object::ProjectType project = Object::ProjectType::OnlyGlass;

        int numGlass = (int)_data->_glass->getNumberPane();
        int numGasGaps = (int)_data->_glass->getNumberGasgap();
        int posBlind = -1;

        bool numberBlind = (_data->_blind != NULL);

        if (numberBlind) {
            project = Object::ProjectType::WithBlind;
            numGlass++;
            posBlind = _data->_blind->getPositionBlind();
            initModuleCalculation(project, condition);
        }

        double qth_0 = _StefanBoltzmann*pow(condition->getTe()+273,4.0f);
        double qqth_n = _StefanBoltzmann*pow(condition->getTi()+273,4.0f);

        double coefTI = (*climateConditions.get()).getTi();
        double coefHI = (*climateConditions.get()).getHi();
        double coefFI = (*climateConditions.get()).getFi();

        vector<double> resultQth;

        double tth[10];
        double tmpEM1[10];
        double tmpEM2[10];
        unsigned glassCounter = 0;

        for (unsigned j = 0; j <numGlass ; j++)
        {
            if( j < _data->_blind->getPositionBlind())
            {
                tth[j] = 0.0f;
                tmpEM1[j] = emc((_data->_glass->getGlasses()[glassCounter]->getEmn1()) / 100);
                tmpEM2[j] = emc((_data->_glass->getGlasses()[glassCounter]->getEmn2()) / 100);
                glassCounter++;
            }
            else if (j == _data->_blind->getPositionBlind())
            {
                if(_data->_blind->getBlinds().at(0)->getType() == "Venetian")
                {
                    tth[j] = _data->_blind->getTth()/100;
                }
                else{
                    tth[j] = _data->_blind->getTth()/100;
                }

                tmpEM1[j] = emc((_data->_blind->getBlinds().at(0)->getEmn1()) / 100);
                tmpEM2[j] = emc((_data->_blind->getBlinds().at(0)->getEmn2()) / 100);
            }

            else {
                tth[j] = 0.0f;
                tmpEM1[j] = emc((_data->_glass->getGlasses()[glassCounter]->getEmn1()) / 100);
                tmpEM2[j] = emc((_data->_glass->getGlasses()[glassCounter]->getEmn2()) / 100);
                glassCounter++;
            }

        }

        vector<double> temperatorGlassesAndGases;

        double v = 0;
        for (unsigned k = 0; k < numGasGaps ; k++) {
            if (_data->_glass->getGasGaps()[k]->getType() == 2) {
                v = getVentilation()->getAirFlow() / (_data->_width * _data->_glass->getGasGaps()[k]->getThickness()) / 0.0036f;
            }
        }

    /*-------With flux-------*/
        initModuleCalculation(project, condition);

        temperatorGlassesAndGases = calculationEnergy();

        double qth_i , qc_i, qv_k;

        vector<vector<double> > matrixCV = conditionMatrixFluxNetThermique(tth, tmpEM1, tmpEM2,
                                                                  numGlass, qth_0, qqth_n, temperatorGlassesAndGases);
        resultQth = resolutionSystem(matrixCV);

        qth_i = resultQth.back() - qqth_n;
        // calculate convection net flux
        qc_i = coefHI * (-coefTI + temperatorGlassesAndGases[numGlass-1]); //bug1206 p7.1

        // calculate ventilation net flux //bug1206 p2
//        double hc = 2*_hc[getPositionVentilation()] + 4 * v;
//        double hc = _hc[numGlass-2] + 4 * v;

        double qcaj = _hcn * (temperatorGlassesAndGases[2*numGlass-2] -
                temperatorGlassesAndGases[numGlass-2]);
        double qcaj1 = _hcn * (temperatorGlassesAndGases[2*numGlass-2] -
                temperatorGlassesAndGases[numGlass-1]);

        qv_k = qcaj + qcaj1;

    /*-------Without flux-------*/
        condition->setFi(0);
        initModuleCalculation(project, condition);

        temperatorGlassesAndGases = calculationEnergy();

        double qth_i_0 , qc_i_0, qv_k_0;

        vector<vector<double> > matrixCV_0 = conditionMatrixFluxNetThermique(tth, tmpEM1, tmpEM2,
                                                                  numGlass, qth_0, qqth_n,temperatorGlassesAndGases);
        resultQth = resolutionSystem(matrixCV_0);

        qth_i_0 = resultQth.back() - qqth_n;
        // calculate convection net flux //bug1206 p2
        qc_i_0 = coefHI * (-coefTI + temperatorGlassesAndGases[numGlass-1]); //bug1206 p7.1


        // calculate ventilation net flux
//        double hc_0 = 2*_hc[getPositionVentilation()] + 4 * v;
//        double hc_0 = _hc[numGlass-2] + 4 * v;

        double qcaj_0 = _hcn * ( temperatorGlassesAndGases[2*numGlass-2] -
                temperatorGlassesAndGases[numGlass-2]);
        double qcaj1_0 = _hcn * (temperatorGlassesAndGases[2*numGlass-2] -
                temperatorGlassesAndGases[numGlass-1]);

        qv_k_0 = qcaj_0 + qcaj1_0;

        _gth = fabs(qth_i - qth_i_0)/coefFI;
        _gc = fabs(qc_i - qc_i_0)/coefFI;
        if (posBlind == numGlass - 1) {
            _gv = fabs(qv_k - qv_k_0)/coefFI;
        } else {
            _gv = 0.0;
        }


    /* Calculate gtot */
        double transmissionGlobal = 0;

        if (*flagBlind.get()) {
            transmissionGlobal = _data->_absorptionEffectiveGlobal[0];
        } else {
            transmissionGlobal = _data->_absorptionEffectiveGlass[0];
        }

        _solarFactor = transmissionGlobal + _gth + _gc + _gv;

        result.push_back(_gth);
        result.push_back(_gc);
        result.push_back(_gv);
        result.push_back(_solarFactor);
    }

    return result;
}

vector<vector<double >> GlazingSolarFactorVentilation::conditionMatrixFluxNetThermique(double tth[], double tmpEM1[], double tmpEM2[],
                                                                double numGlass, double qth0, double qqthn, vector<double> glassTemperator)
{
    int levelV = (numGlass)*2-1;
//    int levelV = (numGlass)*2;
    int levelC = pow(levelV, 2);

    vector<double > matrixV(levelV);                             // Fourre-tout qui renvoie températures
    vector<double> matrixC(levelC);

    // Heat Transfer Matrix
    vector<vector<double> > matrixCV(levelV, vector<double> (levelV + 1));                    // Matrix for calculation

    //' HXI initial pour ventilation naturelle entre store et vitrage
    for (unsigned int i = 0 ; i < levelC ; i++) {
        matrixC[i] = 0;
    }

    for (unsigned int i = 0; i < levelV; i++) {
        matrixV[i] = 0;
    }

    for (unsigned int i = 0 ; i < levelV; i++) {
        for (unsigned int j = 0 ; j < levelV; j++) {
            unsigned int id = (levelV) * (i) + j;
            if(i == j)
            {
                matrixC[id] = 1;
            }
        }
    }

    if ( numGlass == 1)
    {
        matrixV[0] = (1 - tmpEM1[0] - tth[0])*qth0 + tth[0]*qqthn + tmpEM1[0]*_StefanBoltzmann*pow(glassTemperator[0]+273,4.0f);
        matrixV[1] = tth[0]*qth0 + (1-tmpEM2[0]-tth[0])*qqthn + tmpEM2[0]*_StefanBoltzmann*pow(glassTemperator[0]+273,4.0f);
    }
    else if (numGlass == 2)
    {
        double t0,t1;
        if (fabs(glassTemperator[0] - glassTemperator[1]) > 1) {
            t0 = 302;
            t1 = 304;
        } else {
            t0 = 25+273;
            t1 = 25+273;
        }

        double a = tth[0]*qth0;
        double b = (1 - tmpEM2[0] - tth[0]);
        double c = tmpEM2[0]*_StefanBoltzmann*pow(glassTemperator[0]+273.15,4.0f);

        double d = (1 - tmpEM1[1] - tth[1]);
        double e = tth[1];
        double f = tmpEM1[1]*_StefanBoltzmann*pow(glassTemperator[1]+273.15,4.0f);

        double g = (1 - tmpEM2[1] - tth[1]);
        double h = tmpEM2[1]*_StefanBoltzmann*pow(glassTemperator[1]+273.15,4.0f);

        matrixC[1] = -b;
        matrixC[3] = -d;
        matrixC[6] = -e;

        matrixV[0] = c + a;
        matrixV[1] = f + e*qqthn;
        matrixV[2] = h + g*qqthn;
    }

    else if (numGlass == 3)
    {
        double a = tth[0]*qth0;
        double b = 1 - tmpEM2[0] - tth[0];
        double c = tmpEM2[0]*_StefanBoltzmann*pow(glassTemperator[0]+273.15,4.0f);


        double d = 1 - tmpEM1[1] - tth[1];
        double e = tth[1];
        double f = tmpEM1[1]*_StefanBoltzmann*pow(glassTemperator[1]+273.15,4.0f);

        double g = 1 - tmpEM2[1] - tth[1];
        double h = tmpEM2[1]*_StefanBoltzmann*pow(glassTemperator[1]+273.15,4.0f);

        double i = 1 - tmpEM1[2] - tth[2];
        double j = tth[2];
        double k = tmpEM1[2]*_StefanBoltzmann*pow(glassTemperator[2]+273.15,4.0f);

        double l = 1 - tmpEM2[2] - tth[2];
        double m = tmpEM2[2]*_StefanBoltzmann*pow(glassTemperator[2]+273.15,4.0f);

        matrixC[1] = -b;
        matrixC[5] = -d;
        matrixC[8] = -e;
        matrixC[10] = -e;
        matrixC[13] = -g;
        matrixC[17] = -i;
        matrixC[22] = -j;

        matrixV[0] = a + c;
        matrixV[1] = f;
        matrixV[2] = h;
        matrixV[3] = k + j*qqthn;
        matrixV[4] = m + l*qqthn;
    }

    else if (numGlass == 4)
    {
        double a = tth[0]*qth0;
        double b = 1 - tmpEM2[0] - tth[0];
        double c = tmpEM2[0]*_StefanBoltzmann*pow(glassTemperator[0]+273.15,4.0f);


        double d = 1 - tmpEM1[1] - tth[1];
        double e = tth[1];
        double f = tmpEM1[1]*_StefanBoltzmann*pow(glassTemperator[1]+273.15,4.0f);

        double g = 1 - tmpEM2[1] - tth[1];
        double h = tmpEM2[1]*_StefanBoltzmann*pow(glassTemperator[1]+273.15,4.0f);

        double i = 1 - tmpEM1[2] - tth[2];
        double j = tth[2];
        double k = tmpEM1[2]*_StefanBoltzmann*pow(glassTemperator[2]+273.15,4.0f);

        double l = 1 - tmpEM2[2] - tth[2];
        double m = tmpEM2[2]*_StefanBoltzmann*pow(glassTemperator[2]+273.15,4.0f);


        double n = 1 - tmpEM1[3] - tth[3];
        double o = tth[3];
        double p = tmpEM1[3]*_StefanBoltzmann*pow(glassTemperator[3]+273.15,4.0f);

        double q = 1 - tmpEM2[3] - tth[3];
        double r = tmpEM2[3]*_StefanBoltzmann*pow(glassTemperator[3]+273.15,4.0f);

        matrixC[1] = -b;
        matrixC[7] = -d;
        matrixC[10] = -e;
        matrixC[14] = -e;
        matrixC[17] = -g;
        matrixC[23] = -i;
        matrixC[26] = -j;
        matrixC[30] = -j;
        matrixC[33] = -l;
        matrixC[39] = -n;
        matrixC[46] = -o;

        matrixV[0] = a + c;
        matrixV[1] = f;
        matrixV[2] = h;
        matrixV[3] = k ;
        matrixV[4] = m ;
        matrixV[5] = p + o*qqthn;
        matrixV[6] = r + q*qqthn;
    }

    else if (numGlass == 5)
    {
        double a = tth[0]*qth0;
        double b = 1 - tmpEM2[0] - tth[0];
        double c = tmpEM2[0]*_StefanBoltzmann*pow(glassTemperator[0]+273.15,4.0f);


        double d = 1 - tmpEM1[1] - tth[1];
        double e = tth[1];
        double f = tmpEM1[1]*_StefanBoltzmann*pow(glassTemperator[1]+273.15,4.0f);

        double g = 1 - tmpEM2[1] - tth[1];
        double h = tmpEM2[1]*_StefanBoltzmann*pow(glassTemperator[1]+273.15,4.0f);

        double i = 1 - tmpEM1[2] - tth[2];
        double j = tth[2];
        double k = tmpEM1[2]*_StefanBoltzmann*pow(glassTemperator[2]+273.15,4.0f);

        double l = 1 - tmpEM2[2] - tth[2];
        double m = tmpEM2[2]*_StefanBoltzmann*pow(glassTemperator[2]+273.15,4.0f);


        double n = 1 - tmpEM1[3] - tth[3];
        double o = tth[3];
        double p = tmpEM1[3]*_StefanBoltzmann*pow(glassTemperator[3]+273.15,4.0f);

        double q = 1 - tmpEM2[3] - tth[3];
        double r = tmpEM2[3]*_StefanBoltzmann*pow(glassTemperator[3]+273.15,4.0f);

        double s = 1 - tmpEM1[4] - tth[4];
        double t = tth[4];
        double u = tmpEM1[4]*_StefanBoltzmann*pow(glassTemperator[4]+273.15,4.0f);

        double v = 1 - tmpEM2[4] - tth[4];
        double x = tmpEM2[4]*_StefanBoltzmann*pow(glassTemperator[4]+273.15,4.0f);

        matrixC[1] = -b;
        matrixC[9] = -d;
        matrixC[12] = -e;
        matrixC[18] = -e;
        matrixC[21] = -g;
        matrixC[29] = -i;
        matrixC[32] = -j;
        matrixC[38] = -j;
        matrixC[41] = -l;
        matrixC[49] = -n;
        matrixC[52] = -o;
        matrixC[58] = -o;
        matrixC[61] = -q;
        matrixC[69] = -s;
        matrixC[78] = -t;

        matrixV[0] = a + c;
        matrixV[1] = f;
        matrixV[2] = h;
        matrixV[3] = k ;
        matrixV[4] = m ;
        matrixV[5] = p ;
        matrixV[6] = r;
        matrixV[7] = u + t*qqthn;
        matrixV[8] = x + v*qqthn;
    }

    for (unsigned int row = 0; row < levelV; row++) {
        for (unsigned int col = 0; col < levelV + 1; col++) {
            if (col != levelV) {
                matrixCV[row][col] = matrixC[row * levelV + col];
            } else {
                matrixCV[row][col] = matrixV[row];
            }
        }
    }

    return matrixCV;
}

void GlazingSolarFactorVentilation::execute(Object::ProjectType project)
{
    ClimateConditions::Climate *condition;

    condition = new ClimateConditions::Climate(_data->_climate);
    initModuleCalculation(project, condition);
    vector<double > solarFactorWithFlux = calculationEnergy();

    condition->setFi(0);
    initModuleCalculation(project, condition);
    vector<double >  solarFactorNonFlux = calculationEnergy();

    initModuleCalculation(project, _data->_climate);
    _solarFactor = solarFactor(solarFactorWithFlux ,solarFactorNonFlux);
}

void GlazingSolarFactorVentilation::initModuleCalculation(Object::ProjectType project, ClimateConditions::Climate *condition)
{
    ClimateConditions::Climate *climate = new ClimateConditions::Climate();
    *climate = ClimateConditions::Climate(condition->getFi(),
                                          condition->getHe(),
                                          condition->getHi(),
                                          condition->getTe(),
                                          condition->getTi());

    climateConditions.reset(climate);

    if (project == Object::ProjectType::WithBlind){
        flagBlind.reset(new bool(true));
    } else if (project == Object::ProjectType::OnlyGlass){
        flagBlind.reset(new bool(false));
    }
}

double GlazingSolarFactorVentilation:: solarFactor(vector<double> resultFluxNonNull,vector<double> resultFluxNull)
{
    double beta = 0;
    int positionBlind = -1;
    int numGlasBlind = (int)_data->_glass->getNumberPane();
    int numGasGaps = (int)_data->_glass->getNumberGasgap();

    if (*flagBlind.get() == true){
        beta = _data->_blind->getBlinds().at(0)->getOpennessFactor();
        positionBlind = (int)_data->_blind->getPositionBlind();
        numGlasBlind ++;
    }

    double temperatureInteriorWithSunLight = resultFluxNonNull[numGlasBlind - 1] ;
    double temperatureLastGlassWithSunLight = resultFluxNonNull[numGlasBlind - 2];
    double temperatureInteriorWithoutSunLight = resultFluxNull[numGlasBlind - 1];
    double temperatureLastGlassWithoutSunLight = resultFluxNull[numGlasBlind - 2];
    double fluxWithSunLight;
    double transmissionGlobale;

    if (*flagBlind.get() == true){
        transmissionGlobale = _data->_absorptionEffectiveGlobal[0];
    } else {
        transmissionGlobale = _data->_absorptionEffectiveGlass[0];
    }

    double temperatureLastLameAirWithSunLight = resultFluxNonNull[numGlasBlind + numGasGaps - 1];
    double fluxWithoutSunLight;
    double temperatureLastLameAirWithoutSunLight= resultFluxNull [numGlasBlind + numGasGaps - 1];
    double solarFactor;

    double coefHXAAvecSoleil = resultFluxNonNull.back();
    double coefHXASansSoleil = resultFluxNull.back();

    double coefTI = (*climateConditions.get()).getTi();
    double coefHI = (*climateConditions.get()).getHi();
    double coefFI = (*climateConditions.get()).getFi();

    double coefHrSS1 = 4.0 * 0.9  * _StefanBoltzmann * pow((273.15 + (0.5 * (temperatureInteriorWithSunLight + coefTI))) , 3);
    double coefHrVS1  = 4.0 * 0.84 * _StefanBoltzmann * pow((273.15 + (0.5 * (temperatureLastGlassWithSunLight + coefTI))) , 3);
    double coefHrSS2  = 4.0 * 0.9  * _StefanBoltzmann * pow((273.15 + (0.5 * (temperatureInteriorWithoutSunLight + coefTI))) , 3);
    double coefHrVS2  = 4.0 * 0.84 * _StefanBoltzmann * pow((273.15 + (0.5 * (temperatureLastGlassWithoutSunLight + coefTI))) , 3);

    if (positionBlind == numGlasBlind - 1){
        temperatureLastLameAirWithoutSunLight = resultFluxNull[numGlasBlind + numGasGaps];
        temperatureLastLameAirWithSunLight = resultFluxNonNull[numGlasBlind + numGasGaps];

        fluxWithSunLight = transmissionGlobale * coefFI +
                (coefHI -  coefHrSS1) * (temperatureInteriorWithSunLight - coefTI) +
                (1 - (beta / 100)) *  coefHrSS1 * (temperatureInteriorWithSunLight - coefTI) +
                coefHXAAvecSoleil * (temperatureLastLameAirWithSunLight - coefTI) +
                beta / 100 * coefHrVS1 * (temperatureLastGlassWithSunLight - coefTI);

        fluxWithoutSunLight = (coefHI - coefHrSS2) * (temperatureInteriorWithoutSunLight - coefTI) +
                (1 - (beta / 100)) * coefHrSS2 * (temperatureInteriorWithoutSunLight - coefTI) +
                coefHXASansSoleil * (temperatureLastLameAirWithoutSunLight - coefTI) +
                beta / 100 * coefHrVS2 * (temperatureLastGlassWithoutSunLight - coefTI);

    } else {
        fluxWithSunLight = transmissionGlobale * coefFI +
                coefHI * (temperatureInteriorWithSunLight - coefTI);
        fluxWithoutSunLight = coefHI * (temperatureInteriorWithoutSunLight - coefTI);
    }

    solarFactor = (fluxWithSunLight - fluxWithoutSunLight) / coefFI;

    return solarFactor;

}

vector<double> GlazingSolarFactorVentilation::calculationEnergy()
{

    vector<double> coefficientHR(4);                     // Coefficient d'échange radiatif
    double hrv = 0;                              // Coefficient d'échange radiatif pour comparaison
    vector<double > coefficientHC(4);                    // Coefficient d'échange convectif
    vector<double > epsi(4);                  // Facteur d'échange radiative
    double tam = 0 , dTam = 0;                   // Température et ecart d'ambiance pour calcul  coefficientHC
    double bbb = 0;                              // Surfaces de ventilation
    double coefficientHXA = 0;
    int numberBlind = 0;
    int positionBlind = -1;
    double debit = 0;

    double varHXVI = 0, varHXVA = 0, varHXVB = 0, varQ = 0, varQQ = 0;
    double h0h = 0;
    double coeffHXI = 0;
    _hr.clear();
    _hc.clear();

    int numberGlassBlind = (int)_data->_glass->getGlasses().size();

    if (*flagBlind.get() == true){
        positionBlind = _data->_blind->getPositionBlind();
        numberBlind = 1;
        numberGlassBlind ++;
    }

    /* CALCUL DE  varHXI, HXVI,  coefficientHC,  coefficientHR, Débit, Q */

    coeffHXI = numberBlind * calculationHXI();
    varHXVI = calculationHXI(getVentilation());
    coefficientHXA = coeffHXI;

    if (getVentilation()->getTypeVentilation() == Object::VentilationType::Forced) {
        debit = getVentilation()->getAirFlow();
        varQ = 0.34 *  debit/ _data->_width / _data->_height * 10000 * 100;
        varHXVA = varQ;
        varQQ = varQ;
    } else {
        varHXVA = varHXVI;
        varQ = varHXVA;
        varHXVB = varHXVA;
        varQQ = 0;
    }


    h0h = varQQ / 2.0f / 4.0f;
    (h0h < 0.000001f) ? (h0h = 0.000001f) : false;

//    coefficientHXA =  0;
    bbb = (bbb / _data->_height * 100.0f);
    tam = 283.0f;
    dTam = 15.0f;

    radialExchangeCoefficients(epsi,coefficientHR,hrv);

    for (int at = 0; at < (int)(numberGlassBlind - 1); at++){
        coefficientHC[at] = coefficientConvectiveExchange(tam,dTam,getGasByIndex(at));
    }

    bool stop = false;
    int count = 0;
    vector<double> result;

    while (stop == false && count < 200){
        count++;
//        vector<vector<double> > matrixCV = establishMatrixTemperatures(coefficientHC,coefficientHR,hrv,coefficientHXA);  //return C||V matrix, for C*X=V
        vector<vector<double> > matrixCV = conditionMatrixTemperatures(coefficientHC, coefficientHR, hrv, coefficientHXA, h0h, getVentilation()->getAirTemperature(), varQQ, varHXVA);
        result = resolutionSystem(matrixCV);
        stop = resultIsAccepted(result, coefficientHR, coeffHXI, coefficientHXA, coefficientHC, epsi, dTam, tam, h0h, varHXVA, varQQ, varHXVI);
    }
    if ( *flagBlind.get()) {

        bilan(result, numberGlassBlind);

    }
    _hr = coefficientHR;
    _hc = coefficientHC;
    result.push_back(coefficientHXA);
    return result;

}

void GlazingSolarFactorVentilation::bilan(vector<double> &matrixV, int numGlassBlind)
{
    double tth[5];
    double EM1[10];
    double EM2[10];
    unsigned glassCounter = 0;

    double qth0  = _StefanBoltzmann*pow(climateConditions.get()->getTe() + 273.15,4.0f);
    double qqthn = _StefanBoltzmann*pow(climateConditions.get()->getTi() + 273.15,4.0f);

    double Tgn, T2j,Tm, T2n;

    double coefTI = climateConditions.get()->getTi();
    double coefTE = climateConditions.get()->getTe();
    double coefHI = climateConditions.get()->getHi();
    double coefHE = climateConditions.get()->getHe();
    double ES     = climateConditions.get()->getFi();

    double height = _data->_height / 1000;
    double  Htp;

    double bilan;
    vector<double> resultQth;
    bool stop = false;

    double qthA[5], qthB[5], qcC[5], qcD[5], biE[5], rqth[5], rqc[5], bilanj[5];
    double coefhg[4] = {0},coefhc[4] = {0};

    double dT[4], tempT[4], Tj[5] = {0} ;
    double eae[5];

    int count = 0;
    int positionBlind = _data->_blind->getPositionBlind();
    double vel = 0;

// emn
    for (unsigned j = 0; j <numGlassBlind ; j++)
    {
        if( j < _data->_blind->getPositionBlind())
        {
            tth[j] = 0.0f;
            EM1[j] = emc((_data->_glass->getGlasses()[glassCounter]->getEmn1()) / 100);
            EM2[j] = emc((_data->_glass->getGlasses()[glassCounter]->getEmn2()) / 100);

            glassCounter++;
        }
        else if (j == _data->_blind->getPositionBlind())
        {
            if(_data->_blind->getBlinds().at(0)->getType() == "Venetian")
            {
                tth[j] = _data->_blind->getTth()/100;
            }
            else{
                tth[j] = _data->_blind->getTth()/100;
            }

            EM1[j] = emc((_data->_blind->getBlinds().at(0)->getEmn1()) / 100);
            EM2[j] = emc((_data->_blind->getBlinds().at(0)->getEmn2()) / 100);

        }
        else {
            tth[j] = 0.0f;
            EM1[j] = emc((_data->_glass->getGlasses()[glassCounter]->getEmn1()) / 100);
            EM2[j] = emc((_data->_glass->getGlasses()[glassCounter]->getEmn2()) / 100);
            glassCounter++;
        }
    }

// eae
    for (int i = 0; i < numGlassBlind; i++) {
        eae[i] = _data->_absorptionEffectiveGlobal[i + 3];
        biE[i] = eae[i]*ES; //E,J
        qthB[i] =(EM1[i] + EM2[i])*_StefanBoltzmann; //B,G
        }
// init hg
    for (int i = 0; i < numGlassBlind -1; i++) {
        dT[i]     = 15;
        tempT[i]  = 283; //273

        coefhg[i] = coefficientHg(tempT[i],dT[i],getGasByIndex(i));
        coefhc[i] = coefhg[i]; //init
    }

    while (!stop && count < 200) {
        stop = true;
        count ++;

        vector<vector<double> > matrixQth = conditionMatrixFluxNetThermique(tth, EM1, EM2, numGlassBlind, qth0, qqthn, matrixV);
        resultQth = resolutionSystem(matrixQth);

        qthA[0] = EM1[0]*qth0 + EM2[0]*resultQth[1]; //A

        if (numGlassBlind == 2) {
            qcC[0]  = coefHE*(coefTE + 273.15)  + coefhc[0] *(matrixV[2] + 273.15); //C
            qcC[1] = coefhc[0]*(matrixV[2] + 273.15)  + coefHI*(coefTI + 273.15); //H
            qcD[0]  = coefHE + coefhc[0]; //D
            qcD[1] = coefhc[0] + coefHI; //I
            qthA[1] = EM1[1]*resultQth[0] + EM2[1]*qqthn; //F
        } else if (numGlassBlind == 3) {
            qcC[0] = coefHE*(coefTE + 273.15)        + coefhc[0]*(matrixV[3] + 273.15); //C
            qcC[1] = coefhc[0]*(matrixV[3] + 273.15) + coefhc[1]*(matrixV[4] + 273.15);
            qcC[2] = coefhc[1]*(matrixV[4] + 273.15) + coefHI*(coefTI + 273.15);
            qcD[0]  = coefHE + coefhc[0]; //D
            qcD[1] = coefhc[0] + coefhc[1];
            qcD[2] = coefhc[1] + coefHI;
            qthA[1] = EM1[1]*resultQth[0] + EM2[1]*resultQth[3];
            qthA[2] = EM1[2]*resultQth[2] + EM2[2]*qqthn;
        } else if (numGlassBlind == 4) {
            //q0
            if (positionBlind == 0) {
                qcC[0] = coefHE*(coefTE + 273.15)            + coefhc[0]*(matrixV[4] + 273.15);
            } else {
                if (getGasByIndex(0)->getType() == 2) {
                    qcC[0] = coefHE*(coefTE + 273.15)        + coefhc[0]*(matrixV[4] + 273.15);
                } else {
                    qcC[0] = coefHE*(coefTE + 273.15)        + coefhg[0]*(matrixV[1] + 273.15);
                }
            }
            //q1
            if (positionBlind == 0) {
                if (getGasByIndex(1)->getType() == 2) {
                    qcC[1] = coefhc[0]*(matrixV[4] + 273.15) + coefhc[1]*(matrixV[5] + 273.15);
                } else {
                    qcC[1] = coefhc[0]*(matrixV[4] + 273.15) + coefhg[1]*(matrixV[2] + 273.15);
                }
            } else {
                if (getGasByIndex(0)->getType() == 2) {
                    if (getGasByIndex(1)->getType() == 2) {
                        qcC[1] = coefhc[0]*(matrixV[4] + 273.15) + coefhc[1]*(matrixV[5] + 273.15);
                    } else {
                        qcC[1] = coefhc[0]*(matrixV[4] + 273.15) + coefhg[1]*(matrixV[2] + 273.15);
                    }
                } else {
                    if (getGasByIndex(1)->getType() == 2){
                        qcC[1] = coefhg[0]*(matrixV[0] + 273.15) + coefhc[1]*(matrixV[5] + 273.15);
                    } else {
                        qcC[1] = coefhg[0]*(matrixV[0] + 273.15) + coefhg[1]*(matrixV[2] + 273.15);
                    }
                }
            }
            //q2
            if (getGasByIndex(1)->getType() == 2) {
                if (getGasByIndex(2)->getType() == 2) {
                    qcC[2] = coefhc[1]*(matrixV[5] + 273.15) + coefhc[2]*(matrixV[6] + 273.15);
                } else {
                    if (positionBlind == numGlassBlind -1) {
                        qcC[2] = coefhc[1]*(matrixV[5] + 273.15) + coefhc[2]*(matrixV[6] + 273.15);
                    } else {
                        qcC[2] = coefhc[1]*(matrixV[5] + 273.15) + coefhg[2]*(matrixV[3] + 273.15);
                    }
                }
            }else {
                if (getGasByIndex(2)->getType() == 2) {
                    qcC[2] = coefhg[1]*(matrixV[1] + 273.15) + coefhc[2]*(matrixV[6] + 273.15);
                } else {
                    if (positionBlind == numGlassBlind -1) {
                        qcC[2] = coefhg[1]*(matrixV[1] + 273.15) + coefhc[2]*(matrixV[6] + 273.15);
                    } else {
                        qcC[2] = coefhg[1]*(matrixV[1] + 273.15) + coefhg[2]*(matrixV[3] + 273.15);
                    }
                }
            }
             //q3
            if (positionBlind == numGlassBlind -1){
                qcC[3] = coefhc[2]*(matrixV[6] + 273.15) + coefHI*(coefTI + 273.15);
            } else {
                if (getGasByIndex(2)->getType() == 2) {
                    qcC[3] = coefhc[2]*(matrixV[6] + 273.15) + coefHI*(coefTI + 273.15);
                } else {
                    qcC[3] = coefhg[2]*(matrixV[2] + 273.15) + coefHI*(coefTI + 273.15);
                }
            }
            qcD[0] = coefHE    + coefhc[0];
            qcD[1] = coefhc[0] + coefhc[1];
            qcD[2] = coefhc[1] + coefhc[2];
            qcD[3] = coefhc[2] + coefHI;
            qthA[1] = EM1[1]*resultQth[0] + EM2[1]*resultQth[3];
            qthA[2] = EM1[2]*resultQth[2] + EM2[2]*resultQth[5];
            qthA[3] = EM1[3]*resultQth[4] + EM2[3]*qqthn;
        } else if (numGlassBlind == 5) {
            //q0
            if (positionBlind == 0) {
                qcC[0] = coefHE*(coefTE + 273.15)            + coefhc[0]*(matrixV[5] + 273.15);
            } else {
                if (getGasByIndex(0)->getType() == 2) {
                    qcC[0] = coefHE*(coefTE + 273.15)        + coefhc[0]*(matrixV[5] + 273.15);
                } else {
                    qcC[0] = coefHE*(coefTE + 273.15)        + coefhg[0]*(matrixV[1] + 273.15);
                }
            }
            //q1
            if (positionBlind == 0) {
                if (getGasByIndex(1)->getType() == 2) {
                    qcC[1] = coefhc[0]*(matrixV[5] + 273.15) + coefhc[1]*(matrixV[6] + 273.15);
                } else {
                    qcC[1] = coefhc[0]*(matrixV[5] + 273.15) + coefhg[1]*(matrixV[2] + 273.15);
                }
            } else {
                if (getGasByIndex(0)->getType() == 2) {
                    if (getGasByIndex(1)->getType() == 2) {
                        qcC[1] = coefhc[0]*(matrixV[5] + 273.15) + coefhc[1]*(matrixV[6] + 273.15);
                    } else {
                        qcC[1] = coefhc[0]*(matrixV[5] + 273.15) + coefhg[1]*(matrixV[2] + 273.15);
                    }
                } else {
                    if (getGasByIndex(1)->getType() == 2){
                        qcC[1] = coefhg[0]*(matrixV[0] + 273.15) + coefhc[1]*(matrixV[6] + 273.15);
                    } else {
                        qcC[1] = coefhg[0]*(matrixV[0] + 273.15) + coefhg[1]*(matrixV[2] + 273.15);
                    }
                }
            }
            //q2
                if (getGasByIndex(1)->getType() == 2) {
                    if (getGasByIndex(2)->getType() == 2) {
                        qcC[2] = coefhc[1]*(matrixV[6] + 273.15) + coefhc[2]*(matrixV[7] + 273.15);
                    } else {
                        qcC[2] = coefhc[1]*(matrixV[6] + 273.15) + coefhg[2]*(matrixV[3] + 273.15);
                    }
                }else {
                    if (getGasByIndex(2)->getType() == 2) {
                        qcC[2] = coefhg[1]*(matrixV[1] + 273.15) + coefhc[2]*(matrixV[7] + 273.15);
                    } else {
                        qcC[2] = coefhg[1]*(matrixV[1] + 273.15) + coefhg[2]*(matrixV[3] + 273.15);
                    }
                }
            // q3
                if (getGasByIndex(2)->getType() == 2) {
                    if (getGasByIndex(3)->getType() == 2) {
                        qcC[3] = coefhc[2]*(matrixV[7] + 273.15) + coefhc[3]*(matrixV[8] + 273.15);
                    } else {
                        if (positionBlind == numGlassBlind -1) {
                            qcC[3] = coefhc[2]*(matrixV[7] + 273.15) + coefhc[3]*(matrixV[8] + 273.15);
                        } else {
                            qcC[3] = coefhc[2]*(matrixV[7] + 273.15) + coefhg[3]*(matrixV[4] + 273.15);
                        }
                    }

                }else {
                    if (getGasByIndex(3)->getType() == 2) {
                        qcC[3] = coefhg[2]*(matrixV[2] + 273.15) + coefhc[3]*(matrixV[8] + 273.15);
                    } else {
                        if (positionBlind == numGlassBlind-1) {
                            qcC[3] = coefhg[2]*(matrixV[2] + 273.15) + coefhc[3]*(matrixV[8] + 273.15);
                        } else {
                            qcC[3] = coefhg[2]*(matrixV[2] + 273.15) + coefhg[3]*(matrixV[4] + 273.15);
                        }
                    }
                }
           //q4
                if (positionBlind == numGlassBlind -1){
                    qcC[4] = coefhc[3]*(matrixV[8] + 273.15) + coefHI*(coefTI + 273.15);
                } else {
                    if (getGasByIndex(3)->getType() == 2) {
                        qcC[4] = coefhc[3]*(matrixV[8] + 273.15) + coefHI*(coefTI + 273.15);
                    } else {
                        qcC[4] = coefhg[3]*(matrixV[3] + 273.15) + coefHI*(coefTI + 273.15);
                    }
                }
            qthA[1] = EM1[1]*resultQth[0] + EM2[1]*resultQth[3];
            qthA[2] = EM1[2]*resultQth[2] + EM2[2]*resultQth[5];
            qthA[3] = EM1[3]*resultQth[4] + EM2[3]*resultQth[7];
            qthA[4] = EM1[4]*resultQth[6] + EM2[4]*qqthn;
            qcD[0] = coefHE    + coefhc[0];
            qcD[1] = coefhc[0] + coefhc[1];
            qcD[2] = coefhc[1] + coefhc[2];
            qcD[3] = coefhc[2] + coefhc[3];
            qcD[4] = coefhc[3] + coefHI;
        }

        for (int i = 0; i < numGlassBlind; i++) {
            rqth[i]   = qthA[i] - qthB[i]*pow(matrixV[i]+273.15,4.0);
            rqc[i]    = qcC[i]  - (matrixV[i]+273.15)*qcD[i];
            bilanj[i] = fabs(biE[i] + rqth[i] + rqc[i]);
        }
        bilan  = fmax(bilanj[0], bilanj[1]);
        if (numGlassBlind > 2) {
            bilan  = fmax(bilan, bilanj[2]);
        }
        if (numGlassBlind > 3) {
            bilan  = fmax(bilan, bilanj[3]);
        }
        if (numGlassBlind > 4) {
            bilan  = fmax(bilan, bilanj[4]);
        }

        if (fabs(bilan) > 0.001) {
            stop = false;
            for (int j = 0; j < numGlassBlind; j++) {
                Tj[j] = resolTemperature(qthB[j], qcD[j], -(biE[j] + qcC[j] + qthA[j]))-273.15;
            }
        } else {
            for (int j = 0; j < numGlassBlind; j++) {
                Tj[j] = matrixV[j];
            }
        }

        if (Tj[0] > 0 && Tj[1] > 0) {
            if (fabs(T2n - Tgn) > 0.001) {
                stop = false;
            }
            for (int i = 0; i < numGlassBlind; i ++ ) {
                matrixV[i] = Tj[i];
            }
        }

// update Tg
        int iter = 0;
        double Tgo, eps = 0.1, Tg2 = 0;
        double vk = 0;

        if (positionBlind == numGlassBlind -1) {
            Tgn = matrixV[numGlassBlind - 1];
            T2n = matrixV[2*numGlassBlind - 2];
            dT[numGlassBlind - 2]     = fabs(Tj[numGlassBlind -2] - Tj[numGlassBlind -1]);
            Tm  = 0.5*(Tj[numGlassBlind - 2] + Tj[numGlassBlind -1]);
            coefhg[numGlassBlind - 2] = coefficientHg(Tm+ 273.15,dT[numGlassBlind - 2],getGasByIndex(numGlassBlind - 2));
            while (iter < 1000 && eps > 0.001) {
                iter ++;
                Tgo = Tgn;
                Htp = calVelHtp(coefhg[numGlassBlind - 2],Tgn,coefTI,tth[numGlassBlind - 1],numGlassBlind-2);

                T2j = Tm - (Tm-coefTI)*exp(-height/Htp);
                Tgn = Tm - (Htp/height) * (T2j- coefTI);
                eps = fabs(Tgn - Tgo);
            }
        } else if (positionBlind == 0) {
            if (getGasByIndex(1)->getType() == 2) {
                vk = getVentilation()->getAirFlow()/3600/_data->_width/(getGasByIndex(1)->getThickness()/1000);
            } else {
                vk = 0;
            }
            Tgn = matrixV[1];
            T2n = matrixV[numGlassBlind ];
            dT[0]     = fabs(Tj[0] - Tj[1]);
            Tm  = 0.5*(Tj[0] + Tj[1]);
            coefhg[0] = coefficientHg(Tm+ 273.15,dT[0],getGasByIndex(0));
            while (iter < 1000 && eps > 0.001) {
                iter ++;
                Tgo = Tgn;
                Htp = calVelHtp(coefhg[0],Tgn,coefTE,tth[0],0);
                T2j = Tm - (Tm-coefTE)*exp(-height/Htp);
                Tgn = Tm - (Htp/height) * (T2j- coefTE);
                eps = fabs(Tgn - Tgo);
            }
        }

        if (fabs(T2n - Tgn) > 0.001) {
            stop = false;
        }
        if (positionBlind == numGlassBlind -1) {
            matrixV[2*numGlassBlind - 2] = Tgn;
        } else if (positionBlind == 0) {
            matrixV[numGlassBlind] = Tgn;
        }


        for (int t = 0; t < numGlassBlind -1; t++) {
            if (getGasByIndex(t)->getType() == 2) {
                Tgn = matrixV[t+1];
                T2n = matrixV[numGlassBlind +t];
                dT[t]     = fabs(Tj[t] - Tj[t+1]);
                Tm  = 0.5*(Tj[t] + Tj[t+1]);
                coefhg[t] = coefficientHg(Tm+ 273.15,dT[t],getGasByIndex(t));
                iter = 0;
                while (iter < 1000 && eps > 0.001) {
                    iter ++;
                    Tgo = Tgn;
                    if (t == numGlassBlind-2) {
                        Htp = calVelHtp(coefhg[t],Tgn,coefTI,tth[t+1],t);
                        T2j = Tm - (Tm-coefTI)*exp(-height/Htp);
                        Tgn = Tm - (Htp/height) * (T2j- coefTI);
                    } else {
                        Htp = calVelHtp(coefhg[t],Tgn,matrixV[numGlassBlind +t +1],tth[t+1],t);
                        T2j = Tm - (Tm-matrixV[numGlassBlind +t +1])*exp(-height/Htp);
                        Tgn = Tm - (Htp/height) * (T2j- matrixV[numGlassBlind +t +1]);
                    }
                    eps = fabs(Tgn - Tgo);
                }
                if (fabs(T2n - Tgn) > 0.001) {
                    stop = false;
                }
                matrixV[numGlassBlind +t ] = Tgn;
            }
        }

// update hg, hc
        for (int i = 0; i < numGlassBlind -1; i++) {
            dT[i]     = fabs(matrixV[i+1] - matrixV[i]);
            tempT[i]  = 0.5*(matrixV[i] + matrixV[i+1]) + 273.15; //273
            coefhg[i] = coefficientHg(tempT[i],dT[i],getGasByIndex(i));
            if (positionBlind == numGlassBlind -1) {
                if (i == numGlassBlind-2) {
                    vel = calVel(matrixV[i+numGlassBlind],coefTI,tth[numGlassBlind-1],i);
                    coefhc[i] = 2* coefhg[i] + 4*vel;
                } else {
                    if (getGasByIndex(i)->getType() ==2) {
                        vel = calVel(matrixV[i+numGlassBlind],matrixV[i+1+numGlassBlind],tth[i],i);
                        coefhc[i] = 2* coefhg[i] + 4*vel;
                    } else {
                        coefhc[i] = coefhg[i];
                    }
                }
            } else if (positionBlind == 0){
                if (i == 0) {
                    if (numGlassBlind == 2) {
                        vel = calVel(coefTE,matrixV[2],tth[0],0);
                        coefhc[0] = 2*coefhg[0] + 4*vel;
                    } else { //ho
                        if (getGasByIndex(1)->getType() ==2) {
                            vel = calVel(matrixV[numGlassBlind],matrixV[numGlassBlind+1],tth[1],0);
                            coefhc[i] = 2*coefhg[i] + 4*vel;
                        } else { //kin
                            vel = calVel(matrixV[numGlassBlind],matrixV[numGlassBlind+1],tth[1],0);
                            coefhc[i] = 2*coefhg[i] + 4*vel;
                        }
                    }
                } else {
                    if (getGasByIndex(i)->getType() ==2) {
                        if (i == numGlassBlind -2) {
                            vel = calVel(matrixV[i+numGlassBlind],coefTI,tth[i],i);
                        } else {
                            vel = calVel(matrixV[i+numGlassBlind],matrixV[i+1+numGlassBlind],tth[i],i);
                        }
                        coefhc[i] = 2* coefhg[i] + 4*vel;
                    } else {
                        coefhc[i] = coefhg[i];
                    }
                }
            } else {
                if (getGasByIndex(i)->getType() ==2) {
                    if (i == numGlassBlind -2) {
                        vel = calVel(matrixV[i+numGlassBlind],coefTI,tth[i],i);
                    } else {
                        vel = calVel(matrixV[i+numGlassBlind],matrixV[i+1+numGlassBlind],tth[i],i);
                    }
                    coefhc[i] = 2* coefhg[i] + 4*vel;
                } else {
                    coefhc[i] = coefhg[i];
                }
            }
        }

    }
    if (positionBlind == numGlassBlind -1) {
        vel = calVel(matrixV[2*numGlassBlind-2],coefTI,tth[numGlassBlind-1],numGlassBlind-2);
        _hcn = 2* coefhg[numGlassBlind-2] + 4*vel;
    } else {
        _hcn = 0;
    }
}

vector<vector<double> > GlazingSolarFactorVentilation::conditionMatrixTemperatures(vector<double> varHC, vector<double> varHR, double hrv, double varHXA, double hoh, double temperature, double varQQ, double varHXVA)
{
    double betaX = 0;
    double fra = 0;
    double rex = 0;
    double rapq = 0;
    double numGlassBlind = _data->_glass->getNumberPane();
    double numGasGap = _data->_glass->getNumberGasgap();
    int positionBlind = -1;

    if (*flagBlind.get() == true){
        betaX = _data->_blind->getBlinds().at(0)->getOpennessFactor() / 100.0;
        numGlassBlind++;
        numGasGap++;

        positionBlind = _data->_blind->getPositionBlind();
    }

    double  numberThermalElements = 2 * numGlassBlind - 1 ; //Nombre_éléments_thermiques = 2 * Nombre_vitrages_et_store - 1

    int levelV = numGlassBlind + numGasGap;
    int levelC = pow(levelV,2);

    vector<double > matrixV(levelV);                             // Fourre-tout qui renvoie températures
    vector<double> matrixC(levelC);

    // Heat Transfer Matrix
    vector<vector<double> > matrixCV (levelV,vector<double> (levelV + 1));                    // Matrix for calculation

    //' HXI initial pour ventilation naturelle entre store et vitrage
    for (int i = 0 ; i < levelC ; i++){
        matrixC[i] = 0;
    }

    for (int i = 0; i < levelV; i++){
        matrixV[i] = 0;
    }
    matrixV[0] = (climateConditions.get()->getHe()) * (climateConditions.get()->getTe());

    matrixV[numGlassBlind - 1] = matrixV[numGlassBlind - 1] + climateConditions.get()->getHi() * climateConditions.get()->getTi();

    for (int i = 0 ; i < numGlassBlind; i++){
        if ( ! *flagBlind.get()){
            matrixV[i] = matrixV[i] + _data->_absorptionEffectiveGlass[i + 3] * climateConditions.get()->getFi();
        } else {
            matrixV[i] = matrixV[i] + _data->_absorptionEffectiveGlobal[i + 3] * climateConditions.get()->getFi();
        }
    }

    for( unsigned int i = 0 ; i < numGlassBlind; i++){
        for(unsigned int j = 0 ; j < numGlassBlind; j++){
            unsigned int id = 0;                            //check ID
            id = numberThermalElements * (i) + j;
            if (i == j){
                /*break;*/        //go to FVV , increase j , need check
            } else {

                if ( positionBlind  != i && positionBlind != j ){
                    (j == i + 1) ? (matrixC[id] = -varHR[i]) : (matrixC[id]);
                    (j == i - 1) ? (matrixC[id] = -varHR[j]) : (matrixC[id]);

                    if (j == i + 2){
                        (positionBlind == (i + 1)) ? (matrixC[id] = (-hrv) * betaX) : (matrixC[id]);
                        //C(id) = -varHR(i) * betaX avant changement
                    }
                    if (j == i - 2 && i > 0){
                        (positionBlind == (i - 1)) ? (matrixC[id] = (-hrv) * betaX) : (matrixC[id]);
                        //C(id) = -varHR(j) * betaX avant changement
                    }
                    //go to FVV , increase j , need check
                } else {
                    if (positionBlind == i){
                        (j == i + 1) ? (matrixC[id] = -varHR[i] * (1.0 - betaX)): (matrixC[id]);
                        (j == i - 1) ? (matrixC[id] = -varHR[j] * (1.0 - betaX)): (matrixC[id]);
                    } else if (positionBlind == j) {
                        (i == j + 1) ? (matrixC[id] = -varHR[j] * (1.0 - betaX)) : (matrixC[id]);
                        (i == j - 1) ? (matrixC[id] = -varHR[i] * (1.0 - betaX)) : (matrixC[id]);
                    } else {
                        //notthing
                    }
                }
            }
        }

    }//pass2
    int i1 = numberThermalElements;

    for(unsigned int i = 0 ; i < numGlassBlind; i++){
        for (unsigned int j = numGlassBlind ; j < i1; j++){ //check code vd5: For j = Nombre_vitrages_et_store + 1 To i1
            unsigned int  id = 0;
            unsigned int  jd = 0;
            id = numberThermalElements * (i) + j ;
            jd = numberThermalElements * (j) + i ;
            if (j == numGlassBlind + i){
                matrixC[id] = -varHC[i];
                matrixC[jd] = matrixC[id];
            }
            if (j == numGlassBlind + i - 1){
                matrixC[id] = -varHC[i - 1];
                matrixC[jd] = matrixC[id];
            }
        }//Next j
    }//pass2

    for (unsigned int i = 0;  i < numGlassBlind - 1; i++){
        for(unsigned int j = 0 ; j < numGlassBlind - 1; j++){
            unsigned int id = 0;
            id = numberThermalElements * (i + 1 + numGlassBlind - 1) + j + numGlassBlind; //check
            (j == i + 1 && positionBlind == j) ? matrixC[id] = -varHXA : matrixC[id];
            (j == i - 1 && positionBlind == i) ? matrixC[id] = -varHXA : matrixC[id];
        }
    }

    for(unsigned int i = 0 ; i < numberThermalElements; i++){
        i1 = numberThermalElements * (i) + i;
        for (unsigned int j = 0 ; j < numberThermalElements; j++){
            unsigned int ij = 0;
            if (j != i){
                ij = numberThermalElements * (i) + j;
                matrixC[i1] = matrixC[i1] - matrixC[ij];
            }
        }

        (i == 0) ? (matrixC[i1] = matrixC[i1] + climateConditions.get()->getHe()) : (matrixC[i1]) ;
        (i == numGlassBlind - 1) ? (matrixC[i1] = matrixC[i1] + climateConditions.get()->getHi()) : (matrixC[i1]);

        if (i == numGlassBlind && positionBlind == 0) {

            matrixC[i1] = matrixC[i1] + varHXA;
            matrixV[i] = matrixV[i] + varHXA * climateConditions.get()->getTe();
        }
        if (i == 1 && positionBlind == 0){
            matrixC[i1] = matrixC[i1] + varHR[0] * betaX;
            matrixV[i] = matrixV[i] + varHR[0] * betaX * climateConditions.get()->getTe();
        }

        if (i == numberThermalElements - 1 && positionBlind == numGlassBlind - 1){ //check
            matrixC[i1] = matrixC[i1] + varHXA;
            matrixV[i] = matrixV[i] + varHXA * climateConditions.get()->getTi();
        }

        if (i == numGlassBlind - 2 && positionBlind == numGlassBlind - 1){
            matrixC[i1] = matrixC[i1] + varHR[i] * betaX;
            matrixV[i] = matrixV[i] + varHR[i] * betaX * climateConditions.get()->getTi();
            fra = varHR[i] * betaX;
        }

        //if(i == getPositionVentilation() + numGlassBlind){
        if(i == getPositionVentilation() + numGlassBlind -1){ //b1206 p2
            if (getVentilation()->getTypeVentilation() == Object::VentilationType::Forced){
                rex = 1.0 - exp(-1.0 / hoh);
                rapq = rex / (1.0 - hoh * rex);
                matrixC[i1] = matrixC[i1] + varQQ * rapq;
                matrixV[i] = matrixV[i] + varQQ * temperature * rapq;
            } else {
                matrixC[i1] = matrixC[i1] + varHXVA;
                if (getVentilation()->getVentilationFrom()){ //Ventilation is exterior
                    matrixV[i] = matrixV[i] + varHXVA * climateConditions.get()->getTe();
                } else {
                    matrixV[i] = matrixV[i] + varHXVA * climateConditions.get()->getTi();
                }
            }
        }
    }

    for(unsigned int row = 0; row < levelV; row++){
        for(unsigned int col = 0; col < levelV + 1; col++){
            if (col != levelV){
                matrixCV[row][col] = matrixC[row*levelV + col];
            }else{
                matrixCV[row][col] = matrixV[row];
            }
        }
    }
    return matrixCV;
}

double GlazingSolarFactorVentilation::calculationHXI()
{
    double lateral = 0;
    double top = 0;
    double low = 0;
    double beta = 0;
    double betaxx = 0;   //is porosity of store, is global

    double bbb = 0;
    double aaa = 0;
    double ccc = 0;

    double neutralAxis = 0;
    double neutrefabsAxis = 0;

    double coefHXI = 0;
    double coefHXA =0;
    double width = _data->_width;
    double height = _data->_height;

    if ( *flagBlind.get() == true){
        lateral = _data->_blind->getLateralSpace();
        top = _data->_blind->getTopSpace();
        low =_data->_blind->getBottomSpace();
        beta = _data->_blind->getBlinds().at(0)->getOpennessFactor();
        betaxx = round(beta) / 100.0;
        bbb = (2.0/3.0) * height * (2 * lateral + betaxx * width);
        aaa = low * _data->_width;
        ccc = top * _data->_width;
    }

    neutralAxis = calculationCALZX(aaa, bbb, ccc);
    neutrefabsAxis = neutralAxis * _data->_height / 100;
    bbb = bbb / _data->_height  * 100;

    coefHXI =(1200.0f * 0.85f * 0.1975f * 0.96f * (aaa * pow(neutrefabsAxis, 0.5f) + bbb * pow(neutrefabsAxis , 1.5f)) / _data->_width / _data->_height); //check
    coefHXI = coefHXI / (double)sqrt(10);
    coefHXA = coefHXI;

    return coefHXI;
}
double GlazingSolarFactorVentilation::calculationCALZX(double aaa, double bbb, double ccc)
{
    double neutralAxis = 0.5f;
    double f1,f0 ,x0 , x1;

    if (fabs(ff(aaa,bbb,ccc,neutralAxis)) < 0.001f ){
        return double(neutralAxis);
    }

    neutralAxis = 0;
    f0 = ff(aaa, bbb, ccc, neutralAxis);
    x0 = neutralAxis;

    neutralAxis = 1;
    f1 = ff(aaa,bbb,ccc, neutralAxis);
    x1 = neutralAxis;

    unsigned int count = 0;

    while (count < 1000) {
        neutralAxis = x0 - f0 * (x1 - x0) / (f1 - f0);

        if (fabs(ff(aaa, bbb, ccc, neutralAxis)) < 0.001f)
        {
            return (double)neutralAxis;
        }
        if ( ff( aaa, bbb, ccc, neutralAxis) < 0){
            x0 = neutralAxis;
            f0 = ff(aaa, bbb, ccc, neutralAxis);
        }

        if ( ff( aaa, bbb, ccc, neutralAxis) > 0){
            x1 = neutralAxis;
            f1 = ff(aaa, bbb, ccc, neutralAxis);
        }

        count++;
    }

    return neutralAxis;

}
double GlazingSolarFactorVentilation::ff(double aaa, double bbb, double ccc, double neutralAxis) //check
{

    return aaa * pow(neutralAxis, 0.5f)
            + bbb * pow(neutralAxis , 1.5f)
            - ccc * pow((1.0f - neutralAxis) , 0.5f)
            - bbb * pow((1.0f - neutralAxis) ,1.5f);

}
double GlazingSolarFactorVentilation::coefficientConvectiveExchange(double temperature, double dTemperature, GasGap* gasgap)
{
    double distanceFacetoFace;
    double fabsoluteTemperature;

    int ipos;
    double tam = temperature;
    double dTam = dTemperature;

    double concentrationAir,concentrationArg ,concentrationKr, concentrationXe;
    double densityGasGaps, densityAir, densityArg,densityKr,densityXe; //Density of the various gases air, argon, krypton, xenon at temperature T
    double conductivityAir, conductivityArg, conductivityKr, conductivityXe;
    double viscosityAir, viscosityArg, viscosityKr, viscosityXe;
    double heatOfAir, heatOfArg, heatOfKr, heatOfXe;

    double conductivityGasGaps;
    double viscosityGasGaps;
    double heatOfGasGaps;

    double numberGrashof = 0;
    double numberPandl = 0;
    double numberNusselt = 0;

    distanceFacetoFace = (double)gasgap->getThickness() / 1000.0;
    fabsoluteTemperature = temperature - 273;
    ipos = 1;
    (_data->_incline < 60)? ipos = 2 : ipos ;
    (_data->_incline < 30)? ipos = 3 : ipos ;

    //Calcul_concentration des gaz
    concentrationArg = gasgap->getArgon() / 100.0;
    concentrationKr = gasgap->getKrypton() / 100.0;
    concentrationXe = gasgap->getXenon() / 100.0;
    concentrationAir = 1.0 - concentrationArg - concentrationKr - concentrationXe;

    //Calcul pour l'air:
    densityAir = 1.277 - 0.0045 * fabsoluteTemperature;
    conductivityAir = 0.02416 + 0.000080124 * fabsoluteTemperature;
    viscosityAir = 0.00001 * (1.711 + 0.005 * fabsoluteTemperature);
    heatOfAir = 1008.0;

    //Calcul Argon
    densityArg = 1.762 - 0.0063 * fabsoluteTemperature;
    conductivityArg = 0.01634 + 0.00005 * fabsoluteTemperature;
    viscosityArg = 0.00001 * (2.101 + 0.0063 * fabsoluteTemperature);
    heatOfArg = 519.0;

    //Calcul pour Krypton
    densityKr = 3.69 - 0.013 * fabsoluteTemperature;
    conductivityKr = 0.0087 + 0.000028 * fabsoluteTemperature;
    viscosityKr = 0.00001 * (2.33 + 0.007 * fabsoluteTemperature);
    heatOfKr = 245.0;

    //Calcul Xénon
    densityXe = 5.866 - 0.0207 * fabsoluteTemperature;
    conductivityXe = 0.0056 + 0.00002 * fabsoluteTemperature;
    viscosityXe = 0.00001 * (2.218 + 0.0015 * fabsoluteTemperature);
    heatOfXe = 0 /*159.0f*/;

    //Calcul pour Mélange des 3 gaz:
    densityGasGaps = densityAir * concentrationAir + densityArg * concentrationArg + densityKr * concentrationKr + densityXe * concentrationXe;
    conductivityGasGaps = concentrationAir * conductivityAir + concentrationArg * conductivityArg + concentrationKr * conductivityKr + concentrationXe * conductivityXe;
    viscosityGasGaps = concentrationAir * viscosityAir + concentrationArg * viscosityArg + concentrationKr * viscosityKr + concentrationXe * viscosityXe;
    heatOfGasGaps = concentrationAir * heatOfAir + concentrationArg * heatOfArg + concentrationKr * heatOfKr + concentrationXe * heatOfXe;

    //Calcul Grashof et Prandtl
    numberGrashof = 9.81 * pow(distanceFacetoFace , 3) * fabs(dTam) * pow(densityGasGaps , 2) / tam / pow(viscosityGasGaps , 2); //check TAM and DTAM
    numberPandl = heatOfGasGaps * viscosityGasGaps / conductivityGasGaps;

    //Calcul Nusselt selon Inclinaison
    (ipos == 1) ? numberNusselt = 0.035 * pow ((numberGrashof * numberPandl) , 0.38) : numberNusselt ;
    (ipos == 3) ? numberNusselt = 0.16 * pow ((numberGrashof * numberPandl) , 0.28) : numberNusselt;
    (ipos == 2) ? numberNusselt = 0.1 * pow ((numberGrashof * numberPandl) , 0.31) : numberNusselt;

    //Calcul du coefficient d'échange
    (numberNusselt < 1) ? (numberNusselt = 1) : (numberNusselt) ;

    return (2.0 * numberNusselt * conductivityGasGaps) / distanceFacetoFace; //check

}
void GlazingSolarFactorVentilation::radialExchangeCoefficients(vector<double> &EPSI, vector<double> &HR, double &hrv)
{
    double tmpEM1;
    double tmpEM2;
    double epsrv;

    double tam = 283.0f;
    int numGlassObject = _data->_glass->getGlasses().size();
    int posBlind = -1;

    if (*flagBlind.get()){
        numGlassObject++;
        posBlind = _data->_blind->getPositionBlind();
    }

    for(unsigned int at = 0 ; at < numGlassObject - 1; at ++){

        tmpEM1 = getEmissivityByIndex(at,1) ;
        tmpEM2 = getEmissivityByIndex(at + 1,0) ;

        EPSI[at] = 1.0f / (1.0f / tmpEM1 + 1.0f / tmpEM2 - 1);
        HR[at] = 4.0f * _StefanBoltzmann * EPSI[at] * pow(tam , 3.0f);
    }

    for ( int in = 1 ; in < (int)numGlassObject;in++){
        if (in == posBlind && in < (int)numGlassObject - 1){
            tmpEM1 = getEmissivityByIndex(in - 1,1);
            tmpEM2 = getEmissivityByIndex(in + 1,0);

            epsrv = (1.0f / (1.0f / tmpEM1 + 1.0 / tmpEM2 - 1.0f));
            hrv = (4.0f * _StefanBoltzmann * epsrv * pow(tam , 3.0f));
        }
    }
}

double GlazingSolarFactorVentilation::getEmissivityByIndex(int x, int y)
{
    int positionBlind = ((*flagBlind.get()) ? (_data->_blind->getPositionBlind()) : (-1));

    if( x == positionBlind){
        return (((y == 0) ? _data->_blind->getBlinds()[0]->getEmn1() : _data->_blind->getBlinds()[0]->getEmn2()) / 100.0f) ;
    } else {
        if ( x < positionBlind || positionBlind == -1){
            return emc(((y == 0) ? _data->_glass->getGlasses()[x]->getEmn1() : _data->_glass->getGlasses()[x]->getEmn2()) / 100.0f);
        } else {
            return emc(((y == 0) ? _data->_glass->getGlasses()[x - 1]->getEmn1() : _data->_glass->getGlasses()[x - 1]->getEmn2()) / 100.0f);
        }
    }
}

double GlazingSolarFactorVentilation::emc(double valEmn)
{
    // NF EN 12898 - MARS 2019
    double emcor = 1.1887f * valEmn - 0.4967f * valEmn * valEmn + 0.2452f * valEmn * valEmn * valEmn;
    (emcor < 0.837) ? (emcor = 0.837) : (emcor);
    return emcor;
}

vector<double> GlazingSolarFactorVentilation::resolutionSystem(vector< vector<double > > matrixCX)
{
    int n = matrixCX.size();

    for (int i = 0; i < n; i++) {
        // Search for maximum in this column
        double maxEl = ((double)fabs(matrixCX[i][i]));
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

Object::ObjectGlazingSolarFactor *GlazingSolarFactorVentilation::getData() const
{
    return _data;
}

void GlazingSolarFactorVentilation::setData(Object::ObjectGlazingSolarFactor *data)
{
    _data = data;
}
double GlazingSolarFactorVentilation::getSolarFactor() const
{
    return _solarFactor;
}

void GlazingSolarFactorVentilation::setSolarFactor(double solarFactor)
{
    _solarFactor = solarFactor;
}

double GlazingSolarFactorVentilation::getFactorRadiation() const
{
    return _gth;
}

void GlazingSolarFactorVentilation::setFactorRadiation(double radiationFactor)
{
    _gth = radiationFactor;
}

double GlazingSolarFactorVentilation::getFactorConvection() const
{
    return _gc;
}

void GlazingSolarFactorVentilation::setFactorConvection(double convectionFactor)
{
    _gc = convectionFactor;
}

double GlazingSolarFactorVentilation::getFactorVentilation() const
{
    return _gv;
}

void GlazingSolarFactorVentilation::setFactorVentilation(double ventilationFactor)
{
    _gv = ventilationFactor;
}

void GlazingSolarFactorVentilation::zeroingPeripheralSpaces(double &lateralVentilation, double &lowVentilation, double &highVentilation)
{
    int positionBlind       = -1;
    int numberGlassObject   = 0;
    int positionVentilation = -1;

    numberGlassObject = (int)_data->_glass->getGlasses().size();

    if ((*flagBlind.get())) {
        positionBlind = _data->_blind->getPositionBlind();
        numberGlassObject ++;
    }
    positionVentilation = getPositionVentilation();
    //Forced = 0, Natural= 1, Respiration = 2
    if ((positionBlind == numberGlassObject) &&
            (getVentilation()->getTypeVentilation() == 0) &&
            (positionVentilation == positionBlind - 1) ){
        lateralVentilation = 0;
        lowVentilation = 0;
        highVentilation = 0;
    }
}

int GlazingSolarFactorVentilation::getPositionVentilation()
{
    int indexVentilation = 0;
    int typeVentilation = 0;
    int positionVentilation = 0;
    int positionBlind = -1;
    int positionVentilationToBlind = -1;

//    for (int i = 0; i < (int)_data->_glass->getGasGaps().size(); i++){
//        if (_data->_glass->getGasGaps()[i]->getType() == 2){
//            indexVentilation = i;
//            typeVentilation = getVentilation()->getTypeVentilation();
//            if (*flagBlind.get()) {
//                positionBlind = _data->_blind->getPositionBlind();
//                positionVentilationToBlind = _data->_blind->getPositionVentilationToBlind();

//                if (positionBlind < indexVentilation + 1){
//                    positionVentilation = indexVentilation + 1;
//                } else if (positionBlind == indexVentilation + 1) {
//                    if(positionVentilationToBlind == 0){
//                        positionVentilation = positionBlind - 1;
//                    } else if (positionVentilationToBlind == 1){
//                        positionVentilation = positionBlind + 1;
//                    }
//                } if (positionBlind > indexVentilation + 1){
//                    positionVentilation = i;
//                }
//            } else {
//                positionVentilation = i;
//            }
//        }
//    }

    for (int i = 0; i < (int)_data->_glass->getGasGaps().size(); i++) {
        if (_data->_glass->getGasGaps()[i]->getType() == 2) {
            indexVentilation = i;
            typeVentilation = getVentilation()->getTypeVentilation();
        }
    }

    if (*flagBlind.get()) {
        positionBlind = _data->_blind->getPositionBlind();
        positionVentilationToBlind = _data->_blind->getPositionVentilationToBlind();

        if ((positionBlind + 1) < ((indexVentilation + 1) + 1)) {
            positionVentilation = (indexVentilation + 1) + 1;
        } else if ((positionBlind + 1) == ((indexVentilation + 1) + 1)) {
            if (positionVentilationToBlind == 0) {
                positionVentilation = (positionBlind + 1) - 1;
            } else if (positionVentilationToBlind == 1) {
                positionVentilation = (positionBlind + 1);
            } else {
                //notthing
            }
        } else { //positionBlind + 1 > ((indexVentilation + 1) + 1))
            positionVentilation = (indexVentilation + 1);
        }
    } else {
        positionVentilation = (indexVentilation + 1);
    }
    return positionVentilation;
}

GasGap *GlazingSolarFactorVentilation::getVentilation()
{
    vector<GasGap*> gasGaps = _data->_glass->getGasGaps();
    for (auto it = gasGaps.begin(); it != gasGaps.end(); it++){
        if ((*it)->getType() == 2){
            return *it;
        }
    }

    return NULL;
}

double GlazingSolarFactorVentilation::calculationHXI(GasGap *gas)
{
    double lateral = 0;
    double top = 0;
    double low = 0;

    double beta = 0;
    double betaxx = 0;

    double bbb = 0;
    double aaa = 0;
    double ccc = 0;

    double neutralAxis = 0;
    double neutrefabsAxis = 0;

    double coeffHXI = 0;
    double coeffHXA =0;
    double width = _data->_width;
    double height = _data->_height;

    if (gas->getType() == 2){
        lateral = gas->getLateral();
        top = gas->getHigh();
        low = gas->getLow();
    }

    zeroingPeripheralSpaces(lateral,low,height);

    beta = 0;
    betaxx = beta / 100.0f;
    bbb = (2.0f/3.0f) * height * (2.0f * lateral + betaxx * width);
    aaa = low * _data->_width;
    ccc = top * _data->_width;

    neutralAxis = calculationCALZX(aaa, bbb, ccc);
    neutrefabsAxis = neutralAxis * _data->_height / 100;
    bbb = bbb / _data->_height  * 100;

    coeffHXI =(1200.0f * 0.85f * 0.1975f * 0.96f
             * (aaa * pow(neutrefabsAxis, 0.5f) + bbb * pow(neutrefabsAxis , 1.5f))
             / _data->_width / _data->_height);
    coeffHXI = coeffHXI / (double)sqrt(10);
    coeffHXA = coeffHXI;

    return coeffHXI;
}

GasGap *GlazingSolarFactorVentilation::getGasByIndex(int index)
{
    int numberGlassBlind =  _data->_glass->getGlasses().size();
    int positionBlind = ((*flagBlind.get()) ? _data->_blind->getPositionBlind() : -1);

    if (*flagBlind.get() == true){
        numberGlassBlind = numberGlassBlind + 1;

        if ( _data->_blind->getPositionBlind() == 0 || positionBlind == numberGlassBlind - 1){
            if (index == _data->_blind->getPositionBlind() || index == _data->_blind->getPositionBlind()- 1){
                GasGap* tempGas = new GasGap();
                tempGas->setThickness(_data->_blind->getDistanceBlindGlazing());
                tempGas->setArgon(0);
                tempGas->setKrypton(0);
                tempGas->setXenon(0);
                return tempGas;
            } else {
                if (index < (_data->_blind->getPositionBlind() - 1)){
                    return _data->_glass->getGasGaps()[index];

                } else {
                    return _data->_glass->getGasGaps()[index - 1];
                }
            }
        } else {
            if ( index == _data->_blind->getPositionBlind() || index ==  _data->_blind->getPositionBlind() - 1){

                GasGap  *tmpGasGap = _data->_glass->getGasGaps()[_data->_blind->getPositionBlind() - 1];
                GasGap *gas = new GasGap();
                *gas = *tmpGasGap;
                gas->setThickness(gas->getThickness()/2.0);
                return gas;

            } else {
                if (index < _data->_blind->getPositionBlind()){
                    return _data->_glass->getGasGaps()[index];

                } else {
                    return _data->_glass->getGasGaps()[index - 1];

                }
            }
        }
    }else{
        GasGap* gasGap = _data->_glass->getGasGaps()[index];
        return gasGap;
    }
}

bool GlazingSolarFactorVentilation::resultIsAccepted(vector<double> matrixV, vector<double> &coefHR, double coefHXI, double &coefHXA, vector<double> &coefHC,vector<double> &coefEPSI, double &dTam, double &tam , double &hoh, double &coefHXVA, double coefQQ, double coefHXVI)

{
    double coefHRad = 0;
    double coefHXB = 0;
    double tmpTA1 = 0;
    double tmpTA2 = 0;
    double tmpVAIR = 0;
    double coefHXVB = 0;
    double tolerance = 0;
    double coefHConv = 0;
//    double oldHe = 0;
//    double oldHi = 0;

    unsigned int numGlassBlind = _data->_glass->getNumberPane();
    int posBlind = -1;

    if(*flagBlind.get() == true){
        numGlassBlind++;
        posBlind = _data->_blind->getPositionBlind();
    }

    bool stop = true;
//    double newHe = 15;
//    double newHi = 10;
    for(unsigned int i = 0 ; i < numGlassBlind - 1 ; i++){
        tam = 273.0f + (matrixV[i] + matrixV[i + 1]) / 2.0f;
        dTam = fabs(matrixV[i + 1] - matrixV[i]);

        coefHRad = 4.0f * coefEPSI[i] * _StefanBoltzmann * tam * tam * tam;
        coefHConv = coefHC[i];

        GasGap* tmpGas;
        if (*flagBlind.get() == true){
            int at = i;
            if (posBlind == 0 || posBlind == numGlassBlind - 1){
                if (at == posBlind || at == posBlind - 1){
                    tmpGas = new GasGap();
                    tmpGas->setThickness(_data->_blind->getDistanceBlindGlazing());
                    tmpGas->setArgon(0);
                    tmpGas->setKrypton(0);
                    tmpGas->setXenon(0);

                } else {
                    if (at < (posBlind - 1)){
                        tmpGas = _data->_glass->getGasGaps()[at];

                    } else {
                        tmpGas = _data->_glass->getGasGaps()[at - 1];
                    }
                }
            } else {
                if ( at == posBlind || at ==  posBlind - 1){
                    GasGap tmp = *_data->_glass->getGasGaps()[posBlind - 1];
                    tmp.setThickness( tmp.getThickness()/2.0);
                    tmpGas = &tmp;
                } else {
                    if (at < posBlind){
                        tmpGas = _data->_glass->getGasGaps()[at];

                    } else {
                        tmpGas = _data->_glass->getGasGaps()[at - 1];
                    }
                }
            }

        }else{
            int at = i;
            tmpGas = _data->_glass->getGasGaps()[at];
        }

        coefHConv = coefficientConvectiveExchange(tam,dTam,tmpGas);

        if( i == posBlind){
            tmpVAIR = (coefHXA / 1.2f / tmpGas->getThickness());
            coefHConv = (coefHConv + 4.1f * tmpVAIR);
        }

        if (i == getPositionVentilation()-1) {
           if (getVentilation()->getTypeVentilation() == Object::VentilationType::Forced) {
               tmpVAIR = getVentilation()->getAirFlow() / (_data->_width * tmpGas->getThickness()) / 0.0036f;
               coefHConv = coefHConv + 4.1f * tmpVAIR;
               hoh = coefQQ / 2.0f / coefHConv;
           } else {
               tmpVAIR = coefHXVA / 0.34f / tmpGas->getThickness() / 3.6f;
               coefHConv = coefHConv + 4.1f * tmpVAIR;
               hoh = coefHXVA / 2.0f / coefHConv;
           }
        } //Replacement du End if comme dans version 3.10 - 3.11

        if (hoh < 0.000001) hoh = 0.000001;
        //Ce qui est inscrit ci-dessous a été enlevé du test If i = position_ventilation Then pour être
        //cohérant vis �  vis de la version 3.10 et 3.11
        if (((posBlind - i) <= 1) && ((posBlind - i) >= 0) && (coefQQ < 0.000001)) {
           coefHConv = coefficientConvectiveExchange(tam,dTam,tmpGas);
           tmpVAIR = coefHXB / 1.2 / tmpGas->getThickness(); // Vair = Qe/b.e = H.HXB/Cro/e (m/s)
           coefHConv = coefHConv + 4.1 * tmpVAIR;
        }

        tolerance = (double)(fabs(coefHR[i] - coefHRad)); // Test si les coef ech rad ont changé
        if ( tolerance > 0.05){
            stop = false;
            coefHR[i] = coefHRad;
        }
        tolerance = (double)(fabs(coefHC[i] - coefHConv)); // Test si les coef ech conv ont changé
        if(tolerance > 0.05 ){
            stop = false;
            coefHC[i] = coefHConv;
        }
    }
    for(unsigned int i = 0 ; i < numGlassBlind; i++){
        if( posBlind == i ){
            if(i == 0){
                tmpTA1 =  (*climateConditions.get()).getTe();
            }else{
                tmpTA1 = matrixV[numGlassBlind + i - 1]; //check
            }
            if (i == numGlassBlind - 1){
                tmpTA2 = (*climateConditions.get()).getTi();
            }else{
                tmpTA2 = matrixV[numGlassBlind + i]; //check
            }
            coefHXB = (coefHXI * sqrt(fabs(tmpTA2 - tmpTA1)));
            if (fabs(coefHXB - coefHXA) > 0.1){  //adjust torolent HXA
                stop = false;
                coefHXA = coefHXB;
            }
        }
        if (!getVentilation()->getTypeVentilation() == Object::VentilationType::Forced) {
            if (getVentilation()->getVentilationFrom()) {
                tmpTA1 = (*climateConditions.get()).getTe();
            } else {
                tmpTA1 = (*climateConditions.get()).getTi();
            }
            tmpTA2 = matrixV[numGlassBlind + getPositionVentilation()-1];
            coefHXVB = coefHXVI * sqrt(fabs(tmpTA2 - tmpTA1));
            if (fabs(coefHXVB - coefHXVA) > 0.1) {
                stop = false;
                coefHXVA = coefHXVB;
            }
        }
    }

//    if (_data->_coefExternalTradeHE) {
//        oldHe = (*climateConditions.get()).getHe();
//        oldHi = (*climateConditions.get()).getHi();

//        calculateHeAndHi(newHe, newHi, matrixV);
//        if (fabs(newHe - oldHe) > 0.01) {
//            stop = false;
//        }
//        if (fabs(newHi - oldHi) > 0.01) {
//            stop = false;
//        }
//        climateConditions.reset(new ClimateConditions::Climate((*climateConditions.get()).getFi(),
//                                                              newHe,
//                                                              newHi,
//                                                              (*climateConditions.get()).getTe(),
//                                                              (*climateConditions.get()).getTi()));
////        HE = newHe;
////        HI = newHi;
//    }

    return stop;
}
double GlazingSolarFactorVentilation::equation(double a, double b, double c, double x)
{
    return a * pow(x,4) + b*x + c;
}
double GlazingSolarFactorVentilation::resolTemperature(double a, double b, double c)
{
    double x, f0, f1, f;
    double x0 = 0;
    double x1 = 400;
    int count = 0;
    do {
        count++;
        f0 = equation(a, b, c, x0);
        f1 = equation(a, b, c, x1);
        x  = (x0 + x1)/2;
        f  = equation(a, b, c, x);

        if (f0 * f < 0) {
            x1 = x;
        } else {
            x0 = x;
        }

    } while (fabs(equation(a, b, c, x)) > 0.001 && count < 200);
    if (count == 199){
        return 0;
    } else {
        return x;
    }

}
double GlazingSolarFactorVentilation::coefficientHg(double temperature, double dTemperature, GasGap *gasgap)
{
    double distanceFacetoFace;
    double fabsoluteTemperature;

    int ipos;

    double tam = temperature;
    double dTam = dTemperature;

    double concentrationAir, concentrationArg , concentrationKr, concentrationXe;
    double densityGasGaps, densityAir, densityArg, densityKr, densityXe; //Density of the various gases air, argon, krypton, xenon at temperature T

    double conductivityAir, conductivityArg, conductivityKr, conductivityXe;
    double viscosityAir, viscosityArg, viscosityKr, viscosityXe;
    double heatOfAir, heatOfArg, heatOfKr, heatOfXe;

    double conductivityGasGaps;
    double viscosityGasGaps;
    double heatOfGasGaps;

    double numberGrashof = 0;
    double numberPandl = 0;
    double numberNusselt = 0;

    distanceFacetoFace = (double)gasgap->getThickness() / 1000.0;
    fabsoluteTemperature = temperature - 273.15;

    ipos = 1;

    (_data->_incline < 60) ? ipos = 2 : ipos ;
    (_data->_incline < 30) ? ipos = 3 : ipos ;

    //Calcul_concentration des gaz
    concentrationArg = gasgap->getArgon() / 100.0;
    concentrationKr = gasgap->getKrypton() / 100.0;
    concentrationXe = gasgap->getXenon() / 100.0;
    concentrationAir = 1.0 - concentrationArg - concentrationKr - concentrationXe;

    //Calcul pour l'air:
    densityAir = 1.189 - 0.0044 * fabsoluteTemperature;
    conductivityAir = 0.02576 + 0.00008 * fabsoluteTemperature;
    viscosityAir = 0.00001811 +  0.00000005 * fabsoluteTemperature;
    heatOfAir = 1008.0;

    //Calcul Argon
    densityArg = 1.640 - 0.006 * fabsoluteTemperature;
    conductivityArg = 0.01734 + 0.00005 * fabsoluteTemperature;
    viscosityArg = 0.00002228 * 0.000000064 * fabsoluteTemperature;
    heatOfArg = 519.0;

    //Calcul pour Krypton
    densityKr = 3.43 - 0.013 * fabsoluteTemperature;
    conductivityKr = 0.00926 + 0.000026 * fabsoluteTemperature;
    viscosityKr = 0.0000247 * 0.00000007 * fabsoluteTemperature;
    heatOfKr = 245.0;

    //Calcul X�non
    densityXe = 5.495 - 0.0209 * fabsoluteTemperature;
    conductivityXe = 0.00546 + 0.000017 * fabsoluteTemperature;
    viscosityXe = 0.00002299 * 0.000000074 * fabsoluteTemperature;
    heatOfXe = 161 /*159.0f*/;

    //Calcul pour M�lange des 3 gaz:
    densityGasGaps = densityAir * concentrationAir + densityArg * concentrationArg + densityKr * concentrationKr + densityXe * concentrationXe;
    conductivityGasGaps = concentrationAir * conductivityAir + concentrationArg * conductivityArg + concentrationKr * conductivityKr + concentrationXe * conductivityXe;
    viscosityGasGaps = concentrationAir * viscosityAir + concentrationArg * viscosityArg + concentrationKr * viscosityKr + concentrationXe * viscosityXe;
    heatOfGasGaps = concentrationAir * heatOfAir + concentrationArg * heatOfArg + concentrationKr * heatOfKr + concentrationXe * heatOfXe;

    //Calcul Grashof et Prandtl
    numberGrashof = 9.81 * pow(distanceFacetoFace , 3) * fabs(dTam) * pow(densityGasGaps , 2) / tam / pow(viscosityGasGaps , 2); //check TAM and DTAM
    numberPandl = heatOfGasGaps * viscosityGasGaps / conductivityGasGaps;

    //Calcul Nusselt selon Inclinaison
    (ipos == 1) ? numberNusselt = 0.035 * pow((numberGrashof * numberPandl) , 0.38) : numberNusselt ;
    (ipos == 3) ? numberNusselt = 0.16 * pow((numberGrashof * numberPandl) , 0.28) : numberNusselt;
    (ipos == 2) ? numberNusselt = 0.1 * pow((numberGrashof * numberPandl) , 0.31) : numberNusselt;

    //Calcul du coefficient d'�change
    (numberNusselt < 1) ? (numberNusselt = 1) : (numberNusselt) ;

    return (numberNusselt * conductivityGasGaps) / distanceFacetoFace; //check
}

double GlazingSolarFactorVentilation::calVel( double T1, double T2, double tth, int gas)
{
    double rho, bot, top, lat, a1eq, a2eq, z1, z2, cA, cB, cC,cp, muy;
    double height = _data->_height / 1000;
    double width  = _data->_width / 1000;
    double si     = _data->_blind->getDistanceBlindGlazing()/1000;
    double thickness = getGasByIndex(gas)->getThickness()/1000;
    double as, at, ab, ai, ar, ah, arg1, arg2;
    double vel = 0;
    double vk = 0, sk = 1;
    if (gas == 0 && getGasByIndex(1)->getType() == 2) {
        sk = getGasByIndex(1)->getThickness()/1000;
        vk = getVentilation()->getAirFlow()/3600/width/sk;
    } else {
        sk = 1;
        vk = 0;
    }
    if (getGasByIndex(gas)->getType() == 2) {
        vel = getVentilation()->getAirFlow()/3600/width/thickness;
    } else {
        rho = 1.189f - 0.0044f*(T1-20);
        bot = _data->_blind->getBottomSpace() / 1000.0f;
        top = _data->_blind->getTopSpace() / 1000.0f;
        lat = _data->_blind->getLateralSpace() / 1000.0f;
        as  = width * si;
        at  = width * top;
        ab  = width * bot;
        ai  = height * lat;
        ar  = height * lat;
        ah  = tth * height *width;
        arg1 = ab + (ai + ar + ah)/4;
        arg2 = at + (ai + ar + ah)/4;
        a1eq = fmin(as,arg1);
        a2eq = fmin(as,arg2);
        (a1eq < 0.00001f) ? (a1eq = 0.00001f) : false;
        (a2eq < 0.00001f) ? (a2eq = 0.00001f) : false;
        z1  = pow(width*si/0.6f/a1eq-1,2.0f);
        z2  = pow(width*si/0.6f/a2eq-1,2.0f);

        muy = 0.00001811 + 0.00000005*(T1-20);

        cA  = 0.5*rho*(1+z1+z2);
        cB  = 12 * muy * height / pow(si,2);
        cC  = 1.189 * 293.15 *9.81 * height * (fabs(T2-T1)/((T2+273.15)*(T1+273.15)));
        cC  = cC - 12* muy*height*vk/(sk*sk) - 0.5*rho*vk*vk;

        cp  = 1008.0f;
        vel = (-cB+pow(cB*cB+4*cA*cC,0.5))/2/cA;
    }

    return vel;
    }
double GlazingSolarFactorVentilation::calVelHtp(double hg, double T1, double T2, double tth, int gas)
{
    double rho, bot, top, lat, a1eq, a2eq, z1, z2, cA, cB, cC,cp, muy, Htp, hc1, vel;
    double height = _data->_height / 1000;
    double width  = _data->_width / 1000;
    double si     = _data->_blind->getDistanceBlindGlazing()/1000;
    double thickness = getGasByIndex(gas)->getThickness()/1000;
    double as, at, ab, ai, ar, ah, arg1, arg2;
    double vk = 0, sk = 1;
    if (gas == 0 && getGasByIndex(1)->getType() == 2) {
        sk = getGasByIndex(1)->getThickness()/1000;
        vk = getVentilation()->getAirFlow()/3600/width/sk;
    } else {
        sk = 1;
        vk = 0;
    }
    if (getGasByIndex(gas)->getType() == 2) { //ventilation
        vel = getVentilation()->getAirFlow()/3600/width/thickness;
    } else { //gas
        rho = 1.189f - 0.0044f*(T1-20);
        bot = _data->_blind->getBottomSpace() / 1000.0f;
        top = _data->_blind->getTopSpace() / 1000.0f;
        lat = _data->_blind->getLateralSpace() / 1000.0f;
        as  = width * si;
        at  = width * top;
        ab  = width * bot;
        ai  = height * lat;
        ar  = height * lat;
        ah  = tth * height *width;
        arg1 = ab + (ai + ar + ah)/4;
        arg2 = at + (ai + ar + ah)/4;

        a1eq = fmin(as,arg1);
        a2eq = fmin(as,arg2);

        (a1eq < 0.00001f) ? (a1eq = 0.00001f) : false;
        (a2eq < 0.00001f) ? (a2eq = 0.00001f) : false;
        z1  = pow(width*si/0.6f/a1eq-1,2.0f);
        z2  = pow(width*si/0.6f/a2eq-1,2.0f);

        muy = 0.00001811 + 0.00000005*(T1-20);

        cA  = 0.5*rho*(1+z1+z2);
        cB  = 12 * muy * height / pow(si,2);
        cC  = 1.189 * 293.15 *9.81 * height * (fabs(T2-T1)/((T2+273.15)*(T1+273.15)));
        cC  = cC - 12* muy*height*vk/(sk*sk) - 0.5*rho*vk*vk;
        cp  = 1008.0f;

        vel = (-cB+pow(cB*cB+4*cA*cC,0.5))/2/cA;
    }

    hc1 = 2*hg + 4*vel;
    Htp = rho*cp*si*vel/2/hc1;
//    _hcn = hc1;
    return Htp;
    }
