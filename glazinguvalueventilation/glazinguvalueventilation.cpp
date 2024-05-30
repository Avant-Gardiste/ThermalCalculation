#include "GlazingUValueVentilation.h"

using namespace VD6::Calculation;

GlazingUValueVentilation::GlazingUValueVentilation()
{
    _data = NULL;
    _results = vector<double> {};
}

GlazingUValueVentilation::~GlazingUValueVentilation()
{
    delete _data;
}

void GlazingUValueVentilation::initiation(Object::ProjectType type)
{
    if (type == Object::ProjectType::WithBlind) {
        flagBlind.reset(new bool(true));
    } else {
        flagBlind.reset(new bool(false));
    }

    climateConditions.reset(new ClimateConditions::Climate(_data->_climate));
}

vector<double> GlazingUValueVentilation::execute()
{
    vector<double> energySysterm;
    initiation(Object::ProjectType::OnlyGlass);

    energySysterm = calculationEnergySysterm();

    calculateCoeffUValueVentilation(energySysterm);

    if (_data->_blind != NULL) {
        initiation(Object::ProjectType::WithBlind);

        energySysterm = calculationEnergySysterm();

        calculateCoeffUValueVentilation(energySysterm);
    }

    return _results;
}

vector<double> GlazingUValueVentilation::calculationEnergySysterm()
{
    double hxvi = 0, hxva = 0, hxvb = 0, Q = 0, qq = 0, debit = 0;
    double h0h = 0;

    int numberBlind = 0;
    int numberGlassObject = 0;
    int numberThermalElement = 0;
    int posBlind = -1;

    vector<double> coeffHR(7);                        // Coefficient d'échange radiatif
    vector<double > coeffHC(7);                       // Coefficient d'échange convectif
    vector<double > coeffEPSI(7);                     // Facteur d'échange radiative

    double tam = 0, dTam = 0;                         // Température et ecart d'ambiance pour calcul  coeffHC
    double bbb = 0;                                   // Surfaces de ventilation
    double coeffHXI = 0, coeffHXA = 0;
    double betaxx = 0, beta = 0;
    double hrv = 0;                                   // Coefficient d'échange radiatif pour comparaison
    numberGlassObject = (int)_data->_glass->getGlasses().size();

    if (*flagBlind.get()) {
        posBlind = _data->_blind->getPositionBlind();
        beta = _data->_blind->getBlinds().at(0)->getOpennessFactor();
        numberBlind = 1;
        numberGlassObject ++;
    }

    if (getVentilatedAirSpace()->getTypeVentilation() == 0) {
        debit = getVentilatedAirSpace()->getAirFlow();
    }

    numberThermalElement = 2 * numberGlassObject - 1;
    //**************************HXI, hxvi, HC, HR, debit, Q***************
    tam    = 283;
    dTam   = 15;
    coeffHXI = numberBlind * calculationHXI();
    hxvi   = calculationHXI(getVentilatedAirSpace());
    coeffHXA = coeffHXI;

    if (getVentilatedAirSpace()->getTypeVentilation() == 0) {
        Q = 0.34 * debit / _data->_width / _data->_height * 10000 * 100;
        hxva = Q;
        qq = Q;
    } else {
        hxva = hxvi;
        Q = hxva;
        hxvb = hxva;
        qq = 0;
    }

    h0h = qq / 2.0f / 4.0f;
    (h0h < 0.000001f) ? (h0h = 0.000001f) : false;
    bbb = (bbb / _data->_height * 100.0f);
    tam = 283.0;
    dTam = 15.0;
    betaxx = beta / 100;
    radialExchangeCoefficients(coeffEPSI, coeffHR, hrv);

    for (int at = 0; at < (int)(numberGlassObject - 1); at++) {
        coeffHC[at] = coefficientConvectiveExchange(tam, dTam, getGasByIndex(at));
    }

    bool stop = false;
    int count = 0;
    vector<double> result;

    while (!stop && count < 200) {
        count++;
        vector<vector<double> > matrixCV = conditionMatrixTemperatures(coeffHC, coeffHR, hrv, coeffHXA, h0h, qq, hxva);
        result = resolutionSystem(matrixCV);
        stop = resultIsAccepted(result, coeffHR, coeffHXI, coeffHXA, coeffHC, coeffEPSI, dTam, tam, h0h, qq, hxva , hxvi);
    }

    result.push_back(coeffHR[numberGlassObject - numberBlind - 1]);
    result.push_back(coeffHXA);
    result.push_back(hxvb);
    result.push_back(Q);
    result.push_back(h0h);

    return result;
}

void GlazingUValueVentilation::zeroingPeripheralSpaces(double &lateralVentilation, double &lowVentilation, double &highVentilation)
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
    if ((positionBlind == numberGlassObject) && (getVentilatedAirSpace()->getTypeVentilation() == 0) && (positionVentilation == positionBlind - 1)) {
        lateralVentilation = 0;
        lowVentilation = 0;
        highVentilation = 0;
    }
}

double GlazingUValueVentilation::calculationHXI()
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
    double coeffHXA = 0;

    double width = _data->_width;
    double height = _data->_height;

    if (*flagBlind.get()) {
        lateral = _data->_blind->getLateralSpace();
        top = _data->_blind->getTopSpace();
        low = _data->_blind->getBottomSpace();

        beta = _data->_blind->getBlinds().at(0)->getOpennessFactor();
        betaxx = beta / 100.0;

        bbb = (2.0 / 3.0) * height * (2.0f * lateral + betaxx * width);
        aaa = low * _data->_width;
        ccc = top * _data->_width;
    }

    neutralAxis = calculationCALZX(aaa, bbb, ccc);
    neutrefabsAxis = neutralAxis * _data->_height / 100;
    bbb = bbb / _data->_height  * 100;

    coeffHXI = (1200.0f * 0.85f * 0.1975f * 0.96f
                * (aaa * pow(neutrefabsAxis, 0.5f) + bbb * pow(neutrefabsAxis , 1.5f))
                / _data->_width / _data->_height);

    coeffHXI = coeffHXI / (double)sqrt(10);
    coeffHXA = coeffHXI;

    return coeffHXI;
}

double GlazingUValueVentilation::calculationHXI(GasGap *gas)
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
    double coeffHXA = 0;

    double width = _data->_width;
    double height = _data->_height;

    if (gas->getType() == 2) {
        lateral = gas->getLateral();
        top = gas->getHigh();
        low = gas->getLow();
    }

    zeroingPeripheralSpaces(lateral, low, height);

    if (gas->getType() == 2) { //2: Ventilation
        beta = 0;
        betaxx = beta / 100.0f;
        bbb = (2.0f / 3.0f) * height * (2.0f * lateral + betaxx * width);
        aaa = low * _data->_width;
        ccc = top * _data->_width;
    }

    neutralAxis = calculationCALZX(aaa, bbb, ccc);
    neutrefabsAxis = neutralAxis * _data->_height / 100;
    bbb = bbb / _data->_height  * 100;

    coeffHXI = (1200.0f * 0.85f * 0.1975f * 0.96f
                * (aaa * pow(neutrefabsAxis, 0.5f) + bbb * pow(neutrefabsAxis , 1.5f))
                / _data->_width / _data->_height);

    coeffHXI = coeffHXI / (double)sqrt(10);
    coeffHXA = coeffHXI;

    return coeffHXI;
}

void GlazingUValueVentilation::radialExchangeCoefficients(vector<double> &EPSI, vector<double> &HR, double &hrv)
{
    double tmpEM1;
    double tmpEM2;
    double epsrv;

    double tam = 283.0f;
    int numGlassObject = _data->_glass->getGlasses().size();
    int posBlind = -1;

    if (*flagBlind.get()) {
        numGlassObject++;
        posBlind = _data->_blind->getPositionBlind();
    }

    for (unsigned int at = 0 ; at < numGlassObject - 1; at ++) {
        tmpEM1 = getEmissivityByIndex(at, 1) ;
        tmpEM2 = getEmissivityByIndex(at + 1, 0);
        EPSI[at] = 1.0f / (1.0f / tmpEM1 + 1.0f / tmpEM2 - 1);
        HR[at] = 4.0f * _StefanBoltzmann * EPSI[at] * pow(tam , 3.0f);
    }

    for (int in = 1 ; in < (int)numGlassObject; in++) {
        if (in == posBlind && in < (int)numGlassObject - 1) {
            tmpEM1 = getEmissivityByIndex(in - 1, 1);
            tmpEM2 = getEmissivityByIndex(in + 1, 0);
            epsrv = (1.0f / (1.0f / tmpEM1 + 1.0 / tmpEM2 - 1.0f));
            hrv = (4.0f * _StefanBoltzmann * epsrv * pow(tam , 3.0f));
        }
    }
}

double GlazingUValueVentilation::emc(double valEmn)
{
    return (double)(1.2f * valEmn - 0.54f * valEmn * valEmn + 0.28f * valEmn * valEmn * valEmn);
}

double GlazingUValueVentilation::coefficientConvectiveExchange(double temperature, double dTemperature, GasGap *gasgap)
{
    double distanceFacetoFace;
    double fabsoluteTemperature;

    int    ipos;

    double tam = temperature;
    double dTam = dTemperature;

    double concentrationAir, concentrationArg , concentrationKr, concentrationXe;
    double densityGasGaps, densityAir, densityArg, densityKr, densityXe;
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
    (_data->_incline < 60) ? ipos = 2 : ipos ;
    (_data->_incline < 30) ? ipos = 3 : ipos ;

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
    heatOfXe = 0/*159.0f*/;

    //Calcul pour Mélange des 3 gaz:
    densityGasGaps = densityAir * concentrationAir + densityArg * concentrationArg + densityKr * concentrationKr + densityXe * concentrationXe;
    conductivityGasGaps = concentrationAir * conductivityAir + concentrationArg * conductivityArg + concentrationKr * conductivityKr + concentrationXe * conductivityXe;
    viscosityGasGaps = concentrationAir * viscosityAir + concentrationArg * viscosityArg + concentrationKr * viscosityKr + concentrationXe * viscosityXe;
    heatOfGasGaps = concentrationAir * heatOfAir + concentrationArg * heatOfArg + concentrationKr * heatOfKr + concentrationXe * heatOfXe;

    //Calcul Grashof et Prandtl
    numberGrashof = 9.81 * pow(distanceFacetoFace , 3) * fabs(dTam) * pow(densityGasGaps , 2) / tam / pow(viscosityGasGaps , 2);
    numberPandl = heatOfGasGaps * viscosityGasGaps / conductivityGasGaps;

    //Calcul Nusselt selon Inclinaison
    (ipos == 1) ? numberNusselt = 0.035 * pow((numberGrashof * numberPandl) , 0.38) : numberNusselt ;
    (ipos == 3) ? numberNusselt = 0.16 * pow((numberGrashof * numberPandl) , 0.28) : numberNusselt;
    (ipos == 2) ? numberNusselt = 0.1 * pow((numberGrashof * numberPandl) , 0.31) : numberNusselt;

    //Calcul du coefficient d'échange
    (numberNusselt < 1) ? (numberNusselt = 1) : (numberNusselt) ;

    return (2.0 * numberNusselt * conductivityGasGaps) / distanceFacetoFace;
}

vector<vector<double > > GlazingUValueVentilation::conditionMatrixTemperatures(vector<double> coeffHC, vector<double> coeffHR, double hrv, double coeffHXA, double H0H, double QQ, double HXVA)
{
    double varRex    = 0;

    // Ventilation air Gap
    bool   ventilation_forcee;
    double Temperature_entree = 0;
    bool   ventilation_sur_exterieur;
    int    position_ventilation;

    //Blind
    double betaX         = 0;
    int numGasGap        = (int)_data->_glass->getNumberGasgap();
    int numberGlassObject = (int)_data->_glass->getGlasses().size();
    int positionBlind    = -1;

    // function
    double rapq;
    double fra = 0;
    int numberThermalElements;
    int    levelV, levelC;

    if (*flagBlind.get()) {
        betaX = _data->_blind->getBlinds().at(0)->getOpennessFactor() / 100.0;
        numGasGap ++;
        numberGlassObject ++;
        positionBlind = _data->_blind->getPositionBlind();
    }

    if (getVentilatedAirSpace() != 0) {
        position_ventilation = getPositionVentilation();
        ventilation_sur_exterieur = getVentilatedAirSpace()->getVentilationFrom();  //Interior = 0, Exterior = 1

        if (getVentilatedAirSpace()->getTypeVentilation() == 0) {                   // 0: forcee
            Temperature_entree = getVentilatedAirSpace()->getAirTemperature();
            ventilation_forcee = true;
        }
    } else {
        cout << "does not exist ventilation air gap" << endl;
    }

    numberThermalElements = 2 * numberGlassObject - 1;
    levelV = numberGlassObject + numGasGap;
    levelC = (int)pow(levelV, 2);

    vector<double > matrixV(levelV, 0);
    vector<double> matrixC(levelC, 0);
    vector<vector<double> > matrixCV(levelV, vector<double> (levelV + 1));

    matrixV[0] = (climateConditions.get()->getHe()) * (climateConditions.get()->getTe());
    matrixV[numberGlassObject - 1] = matrixV[numberGlassObject - 1] + climateConditions.get()->getHi() * climateConditions.get()->getTi();

    for (size_t i = 0 ; i < numberGlassObject; i++) {
        if (!(*flagBlind.get())) {
            matrixV[i] = matrixV[i] + _data->_absorptionEffectiveGlass[i + 3] * climateConditions.get()->getFi();
        } else {
            matrixV[i] = matrixV[i] + _data->_absorptionEffectiveGlobal[0][i + 3] * climateConditions.get()->getFi();
        }
    }

    for (size_t i = 0 ; i < numberGlassObject; i++) {
        for (size_t j = 0 ; j < numberGlassObject; j++) {
            size_t id = 0;
            id = numberThermalElements * (i) + j;

            if (i == j) {
                /*break;*/
            } else {
                if (positionBlind  != i && positionBlind != j) {
                    (j == i + 1) ? (matrixC[id] = -coeffHR[i]) : (matrixC[id]);
                    (j == i - 1) ? (matrixC[id] = -coeffHR[j]) : (matrixC[id]);

                    if (j == i + 2) {
                        (positionBlind == (i + 1)) ? (matrixC[id] = (-hrv) * betaX) : (matrixC[id]);
                    }

                    if (j == i - 2 && i > 0) {
                        (positionBlind == (i - 1)) ? (matrixC[id] = (-hrv) * betaX) : (matrixC[id]);
                    }
                } else {
                    if (positionBlind == i) {
                        (j == i + 1) ? (matrixC[id] = -coeffHR[i] * (1.0f - betaX)) : (matrixC[id]);
                        (j == i - 1) ? (matrixC[id] = -coeffHR[j] * (1.0f - betaX)) : (matrixC[id]);
                    } else if (positionBlind == j) {
                        (i == j + 1) ? (matrixC[id] = -coeffHR[j] * (1.0f - betaX)) : (matrixC[id]);
                        (i == j - 1) ? (matrixC[id] = -coeffHR[i] * (1.0f - betaX)) : (matrixC[id]);
                    } else {
                        //notthing
                    }
                }
            }
        }
    }

    int i1 = numberThermalElements;

    for (size_t i = 0 ; i < numberGlassObject; i++) {
        for (size_t j = numberGlassObject ; j < i1; j++) {
            size_t  id = 0;
            size_t  jd = 0;
            id = numberThermalElements * (i) + j ;
            jd = numberThermalElements * (j) + i ;

            if (j == numberGlassObject + i) {
                matrixC[id] = -coeffHC[i];
                matrixC[jd] = matrixC[id];
            }

            if (j == numberGlassObject + i - 1) {
                matrixC[id] = -coeffHC[i - 1];
                matrixC[jd] = matrixC[id];
            }
        }
    }

    for (unsigned int i = 0;  i < numberGlassObject - 1; i++) {
        for (unsigned int j = 0 ; j < numberGlassObject - 1; j++) {
            unsigned int id = 0;
            id = numberThermalElements * (i + 1 + numberGlassObject - 1) + j + numberGlassObject;
            (j == i + 1 && positionBlind == j) ? matrixC[id] = -coeffHXA : false;
            (j == i - 1 && positionBlind == i) ? matrixC[id] = -coeffHXA : false;
        }
    }

    for (unsigned int i = 0 ; i < numberThermalElements; i++) {
        i1 = numberThermalElements * (i) + i;

        for (unsigned int j = 0 ; j < numberThermalElements; j++) {
            unsigned int ij = 0;

            if (j != i) {
                ij = numberThermalElements * (i) + j;
                matrixC[i1] = matrixC[i1] - matrixC[ij];
            }
        }

        (i == 0) ? (matrixC[i1] = matrixC[i1] + climateConditions.get()->getHe()) : (matrixC[i1]) ;

        if (i == numberGlassObject - 1) {
            matrixC[i1] = matrixC[i1] + climateConditions.get()->getHi();
        }

        if (i == numberGlassObject && positionBlind == 0) {
            matrixC[i1] = matrixC[i1] + coeffHXA;
            matrixV[i] = matrixV[i] + coeffHXA * climateConditions.get()->getTe();
        }

        if (i == 1 && positionBlind == 0) {
            matrixC[i1] = matrixC[i1] + coeffHR[0] * betaX;
            matrixV[i] = matrixV[i] + coeffHR[0] * betaX * climateConditions.get()->getTe();
        }

        if (i == numberThermalElements - 1 && positionBlind == numberGlassObject - 1) {
            matrixC[i1] = matrixC[i1] + coeffHXA;
            matrixV[i] = matrixV[i] + coeffHXA * climateConditions.get()->getTi();
        }

        if (i == numberGlassObject - 2 && positionBlind == numberGlassObject - 1) {
            matrixC[i1] = matrixC[i1] + coeffHR[i] * betaX;
            matrixV[i] = matrixV[i] + coeffHR[i] * betaX * climateConditions.get()->getTi();
            fra = coeffHR[i] * betaX;
        }

        if (i == position_ventilation + numberGlassObject - 1) {
            if (ventilation_forcee == true) {
                varRex = 1.0f - exp(-1.0f / H0H);
                rapq = varRex / (1.0f - H0H * varRex);
                matrixC[i1] = matrixC[i1] + QQ * rapq;
                matrixV[i] = matrixV[i] + QQ * Temperature_entree * rapq;
            } else {
                matrixC[i1] = matrixC[i1] + HXVA;

                if (ventilation_sur_exterieur == true) {
                    matrixV[i] = matrixV[i] + HXVA * climateConditions.get()->getTe();
                } else {
                    matrixV[i] = matrixV[i] + HXVA * climateConditions.get()->getTi();
                }
            }
        }
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

bool GlazingUValueVentilation::resultIsAccepted(vector<double> &matrixV, vector<double> &coeffHR, double &coeffHXI,
        double &coeffHXA, vector<double> &coeffHC, vector<double> &coeffEPSI,
        double &dTam, double &tam, double &H0H, double &QQ, double &HXVA , double &HXVI)
{
    // Function
    double coeffHRad = 0;
    double varHXB = 0;
    double varHXVB = 0;
    double tolerance = 0;
    double ta1, ta2;
    double vair = 0;
    bool   stop = false;
    double coeffHConv = 0;
    int    numberGlassObject;

    // Blind
    int numBlind = 0;
    int posBlind = -1;

    //Ventilation air Gaps
    bool ventilation_sur_exterieur = false;
    int  position_ventilation = -1;
    bool ventilation_forcee = false;
    double debit = 0;

    // init
    if (*flagBlind.get()) {
        numBlind = (1);
        posBlind = _data->_blind->getPositionBlind();
    }

    if (getVentilatedAirSpace() != 0) {
        if (getVentilatedAirSpace()->getTypeVentilation() == 0) {
            ventilation_forcee = true;
            debit = getVentilatedAirSpace()->getAirFlow();
            ventilation_sur_exterieur = false;
        } else {
            ventilation_forcee = false;
            ventilation_sur_exterieur = getVentilatedAirSpace()->getVentilationFrom();
        }

        position_ventilation = getPositionVentilation();
    }

    numberGlassObject = (int)_data->_glass->getGlasses().size() + numBlind;
    //todo
    stop = true;

    for (int i = 0 ; i < numberGlassObject - 1 ; i++) {
        GasGap *tmpGas;
        tmpGas = getGasByIndex(i);
        tam = 273.0f + (matrixV[i] + matrixV[i + 1]) / 2.0f;
        dTam = fabs(matrixV[i + 1] - matrixV[i]);
        coeffHRad = 4.0f * coeffEPSI[i] * _StefanBoltzmann * tam * tam * tam;
        coeffHConv = coeffHC[i];
        coeffHConv = coefficientConvectiveExchange(tam, dTam, tmpGas);

        if (i == posBlind) {
            vair = (coeffHXA / 1.2f / tmpGas->getThickness());
            coeffHConv = (coeffHConv + 4.1f * vair);
        }

        if (i == position_ventilation - 1) {
            if (ventilation_forcee == true) {
                vair = debit / (_data->_width * tmpGas->getThickness()) / 0.0036f;
                coeffHConv = coeffHConv + 4.1f * vair;
                H0H = QQ / 2.0f / coeffHConv;
            } else {
                vair = HXVA / 0.34f / tmpGas->getThickness() / 3.6f;
                coeffHConv = coeffHConv + 4.1f * vair;
                H0H = HXVA / 2.0f / coeffHConv;
            }
        }

        (H0H < 0.000001f) ? (H0H = 0.000001f) : false;

        if (((posBlind - (i)) <= 1) && ((posBlind - (i)) >= 0) && (QQ < 0.000001f)) {
            coeffHConv = coefficientConvectiveExchange(tam, dTam, tmpGas);
            vair = varHXB / 1.2 / tmpGas->getThickness();                   //Vair = Qe/b.e = H.HXB/Cro/e (m/s)
            coeffHConv = coeffHConv + 4.1 * vair;
        }

        tolerance = (double)(abs(coeffHR[i] - coeffHRad));

        if (tolerance > 0.05) {
            stop = false;
            coeffHR[i] = coeffHRad;
        }

        tolerance = (double)(abs(coeffHC[i] - coeffHConv));

        if (tolerance > 0.05) {
            stop = false;
            coeffHC[i] = coeffHConv;
        }
    }

    for (unsigned int i = 0 ; i < numberGlassObject; i++) {
        if (posBlind == i) {
            if (i == 0) {
                ta1 =  climateConditions.get()->getTe();
            } else {
                ta1 = matrixV[numberGlassObject + i - 1];
            }

            if (i == numberGlassObject - 1) {
                ta2 = climateConditions.get()->getTi();
            } else {
                ta2 = matrixV[numberGlassObject + i];
            }

            varHXB = (coeffHXI * sqrt(fabs(ta2 - ta1)));

            if (fabs(varHXB - coeffHXA) > 0.1) {
                stop = false;
                coeffHXA = varHXB;
            }
        }

        if (ventilation_forcee == false) {
            if (ventilation_sur_exterieur == true) {
                ta1 = climateConditions.get()->getTe();
            } else {
                ta1 = climateConditions.get()->getTi();
            }

            ta2 = matrixV[numberGlassObject + position_ventilation - 1];
            varHXVB = HXVI * sqrt(abs(ta2 - ta1));

            if (abs(varHXVB - HXVA) > 0.1f) {
                stop = false;
                HXVA = varHXVB;
            }
        }
    }

    return stop;
}

void GlazingUValueVentilation::calculateCoeffUValueVentilation(vector<double> energy)
{
    int positionBlind = -1;
    double beta = 0;
    double rex, rapq;
    double temperaturesOfExit;
    int    numberGlassObject, numberGasGaps;
    double tent;
    double h0h;
    double entryTemperature = 0;
    bool ventilationForced = false;
    bool ventilationExterior = false;
    int  positionVentilation = -1;
    double Q;

    //
    double coeffHXVWithoutSolar = 0, coeffHRWithoutSolar = 0, coeffHXAWithoutSolar = 0;
    double temperaturesElementInteriorNonSolar = 0;
    double temperaturesGasGapLatterNonSolar = 0;
    double temperaturesGlazingLatterNonSolar = 0;
    double airFlowOutlet = 0;
    double fluxIncomingNonSolar;
    double coefficientU, equivalentR;

    //init
    numberGlassObject = (int)_data->_glass->getGlasses().size();
    numberGasGaps = _data->_glass->getNumberGasgap();

    if (*flagBlind.get()) {
        numberGlassObject++;
        positionBlind = _data->_blind->getPositionBlind();
        beta = _data->_blind->getBlinds().at(0)->getOpennessFactor();
        numberGasGaps ++;
    }

    temperaturesGlazingLatterNonSolar = energy[numberGlassObject - 2];
    temperaturesElementInteriorNonSolar = energy[numberGlassObject - 1];
    temperaturesGasGapLatterNonSolar = energy[numberGlassObject + numberGasGaps - 1];

    coeffHRWithoutSolar = energy[numberGlassObject + numberGasGaps];
    coeffHXAWithoutSolar = energy[numberGlassObject + numberGasGaps + 1];
    coeffHXVWithoutSolar = energy[numberGlassObject + numberGasGaps + 2];

    Q = energy[numberGlassObject + numberGasGaps + 3];
    airFlowOutlet = (int)(getVentilatedAirSpace()->getAirflowOutlet()) ;

    if (getVentilatedAirSpace() != 0) {
        if (getVentilatedAirSpace()->getTypeVentilation() == 0) {
            ventilationForced = true;
            ventilationExterior = getVentilatedAirSpace()->getAirflowOutlet();
            entryTemperature = getVentilatedAirSpace()->getAirTemperature();
        } else {
            ventilationForced = false;
            ventilationExterior = getVentilatedAirSpace()->getVentilationFrom();
        }

        positionVentilation = getPositionVentilation();
    }

    h0h = energy.back();
    energy.pop_back();
    rex = 1.0f - exp(-1.0f / h0h);
    rapq = rex  / (1.0f - h0h * rex);
    //Temperature de sortie de la lame ventilee
    tent = entryTemperature;

    if (ventilationForced == false) {
        if (ventilationExterior == true) {
            tent = climateConditions.get()->getTe();
        } else {
            tent = climateConditions.get()->getTi();
        }
    }

    temperaturesOfExit = tent + (energy[numberGlassObject + abs(positionVentilation) - 1] - tent) * rapq;

    if (positionBlind == numberGlassObject - 1) {
        coeffHRWithoutSolar = 4 * 0.84 * _StefanBoltzmann * pow((273.15 + (0.5 * (temperaturesGlazingLatterNonSolar + climateConditions.get()->getTi()))) , 3);
        fluxIncomingNonSolar = (climateConditions.get()->getHi() - (4 * 0.9 * _StefanBoltzmann * pow((273.15 + (0.5 * (temperaturesElementInteriorNonSolar + climateConditions.get()->getTi()))) , 3))) * (temperaturesElementInteriorNonSolar - climateConditions.get()->getTi()) +
                               (1 - (beta / 100)) * 4 * 0.9 * _StefanBoltzmann * pow((273.15 + (0.5 * (temperaturesElementInteriorNonSolar + climateConditions.get()->getTi()))) , 3) * (temperaturesElementInteriorNonSolar - climateConditions.get()->getTi()) +
                               coeffHXAWithoutSolar * (temperaturesGasGapLatterNonSolar - climateConditions.get()->getTi()) +
                               beta / 100 * coeffHRWithoutSolar * (temperaturesGlazingLatterNonSolar - climateConditions.get()->getTi()) +
                               (1 - abs(airFlowOutlet)) * (temperaturesOfExit - climateConditions.get()->getTi()) * (Q * (int)(ventilationForced) + coeffHXVWithoutSolar * (1 - (int)(ventilationForced))) ;// Soit Q (ventilation forcé) soit HXVA (ventilation nat)
    } else {
        fluxIncomingNonSolar = climateConditions.get()->getHi() * (temperaturesElementInteriorNonSolar - climateConditions.get()->getTi()) +
                               (1 - abs(airFlowOutlet)) * (temperaturesOfExit - climateConditions.get()->getTi()) * (Q * (int)(ventilationForced) + coeffHXVWithoutSolar * (1 - (int)(ventilationForced))) ;// Soit Q (ventilation forcé) soit HXVA (ventilation nat)
    }

    coefficientU = abs((fluxIncomingNonSolar / (climateConditions.get()->getTi() - climateConditions.get()->getTe())));
    equivalentR = 1 / coefficientU;

    for (int i = 0 ; i < _data->_glass->getNumberPane() ; i ++) {
        equivalentR = equivalentR + (_data->_glass->getGlasses()[i]->getThicknessTotal() / 1000) ; //Correction coeff U avec épaisseur verre.....
    }

    coefficientU = 1 / equivalentR;
    //string key =  to_string((int)*flagBlind.get());
    _results.push_back(coefficientU);
}

vector<double> GlazingUValueVentilation::resolutionSystem(vector< vector<double > > matrixCX)
{
    int n = matrixCX.size();

    for (int i = 0; i < n; i++) {
        double maxEl = ((double)fabs(matrixCX[i][i]));
        int maxRow = i;

        for (int k = i + 1; k < n; k++) {
            if (fabs(matrixCX[k][i]) > maxEl) {
                maxEl = fabs(matrixCX[k][i]);
                maxRow = k;
            }
        }

        for (int k = i; k < n + 1; k++) {
            double tmp = matrixCX[maxRow][k];
            matrixCX[maxRow][k] = matrixCX[i][k];
            matrixCX[i][k] = tmp;
        }

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

    vector<double> y(n);

    for (int i = n - 1; i >= 0; i--) {
        y[i] = matrixCX[i][n] / matrixCX[i][i];

        for (int k = i - 1; k >= 0; k--) {
            matrixCX[k][n] -= matrixCX[k][i] * y[i];
        }
    }

    return y;
}

double GlazingUValueVentilation::calculationCALZX(double aaa, double bbb, double ccc)
{
    double neutralAxis = 0.5f;
    double f1, f0 , x0 , x1;

    if (fabs(ff(aaa, bbb, ccc, neutralAxis)) < 0.001f) {
        return double(neutralAxis);
    }

    neutralAxis = 0;
    f0 = ff(aaa, bbb, ccc, neutralAxis);
    x0 = neutralAxis;

    neutralAxis = 1;
    f1 = ff(aaa, bbb, ccc, neutralAxis);
    x1 = neutralAxis;

    int countExit = 0;

    while (countExit <= 1000) {
        neutralAxis = x0 - f0 * (x1 - x0) / (f1 - f0);

        if (fabs(ff(aaa, bbb, ccc, neutralAxis)) < 0.001f) {
            return (double)neutralAxis;
        }

        if (ff(aaa, bbb, ccc, neutralAxis) < 0) {
            x0 = neutralAxis;
            f0 = ff(aaa, bbb, ccc, neutralAxis);
        }

        if (ff(aaa, bbb, ccc, neutralAxis) > 0) {
            x1 = neutralAxis;
            f1 = ff(aaa, bbb, ccc, neutralAxis);
        }

        countExit++;
    }

    return neutralAxis;
}

double GlazingUValueVentilation::ff(double aaa, double bbb, double ccc, double neutralAxis)
{
    return aaa * pow(neutralAxis, 0.5f)
           + bbb * pow(neutralAxis , 1.5f)
           - ccc * pow((1.0f - neutralAxis) , 0.5f)
           - bbb * pow((1.0f - neutralAxis) , 1.5f);
}

double GlazingUValueVentilation::getEmissivityByIndex(int x, int y)
{
    int positionBlind = ((*flagBlind.get()) ? (_data->_blind->getPositionBlind()) : (-1));

    if (x == positionBlind) {
        return (((y == 0) ? _data->_blind->getBlinds()[0]->getEmn1() : _data->_blind->getBlinds()[0]->getEmn2()) / 100.0f) ;
    } else {
        if (x < positionBlind || positionBlind == -1) {
            return emc(((y == 0) ? _data->_glass->getGlasses()[x]->getEmn1() : _data->_glass->getGlasses()[x]->getEmn2()) / 100.0f);
        } else {
            return emc(((y == 0) ? _data->_glass->getGlasses()[x - 1]->getEmn1() : _data->_glass->getGlasses()[x - 1]->getEmn2()) / 100.0f);
        }
    }
}

GasGap *GlazingUValueVentilation::getVentilatedAirSpace()
{
    vector<GasGap *> gasGaps = _data->_glass->getGasGaps();

    for (auto it = gasGaps.begin(); it != gasGaps.end(); it++) {
        if ((*it)->getType() == 2) {
            return *it;
        }
    }

    return 0;
}

int GlazingUValueVentilation::getPositionVentilation()
{
    int indexVentilation = 0;
    int typeVentilation = 0;
    int positionVentilation = 0;
    int positionBlind = -1;
    int positionVentilationToBlind = -1;

    for (int i = 0; i < (int)_data->_glass->getGasGaps().size(); i++) {
        if (_data->_glass->getGasGaps()[i]->getType() == 2) {
            indexVentilation = i;
            typeVentilation = getVentilatedAirSpace()->getTypeVentilation();
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
        } else {
            positionVentilation = (indexVentilation + 1);
        }
    } else {
        positionVentilation = (indexVentilation + 1);
    }

    return positionVentilation;
}

vector<double > GlazingUValueVentilation::getResultUValueVentilation() const
{
    return _results;
}

GasGap *GlazingUValueVentilation::getGasByIndex(int index)
{
    int numGlassObject =  _data->_glass->getGlasses().size();
    int posBlind = ((*flagBlind.get()) ? _data->_blind->getPositionBlind() : -1);

    if (*flagBlind.get() == true) {
        numGlassObject = numGlassObject + 1;

        if (_data->_blind->getPositionBlind() == 0 || posBlind == numGlassObject - 1) {
            if (index == _data->_blind->getPositionBlind() || index == _data->_blind->getPositionBlind() - 1) {
                GasGap *tempGas = new GasGap();

                tempGas->setThickness(_data->_blind->getDistanceBlindGlazing());
                tempGas->setArgon(0);
                tempGas->setKrypton(0);
                tempGas->setXenon(0);

                return tempGas;
            } else {
                if (index < (_data->_blind->getPositionBlind() - 1)) {
                    return _data->_glass->getGasGaps()[index];
                } else {
                    return _data->_glass->getGasGaps()[index - 1];
                }
            }
        } else {
            if (index == _data->_blind->getPositionBlind() || index ==  _data->_blind->getPositionBlind() - 1) {
                GasGap  *tmpGasGap = _data->_glass->getGasGaps()[_data->_blind->getPositionBlind() - 1];
                GasGap *gas = new GasGap();
                *gas = *tmpGasGap;
                gas->setThickness(gas->getThickness() / 2.0);
                return gas;
            } else {
                if (index < _data->_blind->getPositionBlind()) {
                    return _data->_glass->getGasGaps()[index];
                } else {
                    return _data->_glass->getGasGaps()[index - 1];
                }
            }
        }
    } else {
        GasGap *gasGap = _data->_glass->getGasGaps()[index];
        return gasGap;
    }
}

void GlazingUValueVentilation::setData(Object::ObjectUValue *data)
{
    _data = data;
}
