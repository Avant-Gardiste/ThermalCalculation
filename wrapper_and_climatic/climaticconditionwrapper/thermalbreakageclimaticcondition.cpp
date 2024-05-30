#include "thermalbreakageclimaticcondition.h"

#include "fstream"

#include "thermal.h"
#include "projectcase.h"
#include <QDebug>
#include <QtGlobal>

ThermalBreakageClimaticCondition::ThermalBreakageClimaticCondition(BaseClimaticCondition *parent) :
    BaseClimaticCondition(parent)
{
    _modeThermalBreakage = 0; // 0: RegTrans  1: RegPerm 2: sliding sash
                              //    RegPerm is when
                              //        gasGapsVentilationExistence
                              //        OR obstacleExistence
                              //        OR radiatorExistence
                              //        OR numglass > 3
    _climatic = QMap<QString, Climatic *> {};
}

void ThermalBreakageClimaticCondition::specificClimaticCondition()
{
    QMap<QString, Climatic *> climatics;

    if (_modeThermalBreakage == 0) {
        double tmpFluxSpecific;
        double inclinaisonCalc = ProjectCase::currentProject()->glassParameters()->inclination();

        if (inclinaisonCalc > 75) {
            tmpFluxSpecific = 750;
        } else if (75 >= inclinaisonCalc && inclinaisonCalc > 60) {
            tmpFluxSpecific = 850;
        } else if (60 >= inclinaisonCalc && inclinaisonCalc > 45) {
            tmpFluxSpecific = 900;
        } else if (45 >= inclinaisonCalc && inclinaisonCalc > 0) {
            tmpFluxSpecific = 950;
        } else if (inclinaisonCalc = 0) {
            tmpFluxSpecific = 900;
        }

        for (int i = 0; i < 4; i++) {
            ThermalObject *object = ProjectCase::currentProject()->thermal()->dynamicData(i);

            if (object) {
                Climatic *tmpClimate = new Climatic();
                tmpClimate->setFlux(object->flux().toDouble());
                tmpClimate->setHe(object->he().toDouble());
                tmpClimate->setHi(object->hi().toDouble());
                tmpClimate->setTeMax(object->teMax().toDouble());
                tmpClimate->setTi(object->ti().toDouble());
                tmpClimate->setTeMin(object->teMin().toDouble());

                tmpClimate->setFaFlux(tmpClimate->flux() / tmpFluxSpecific);
                climatics[QString::number(i)] = tmpClimate;  // i: season: spring, summer, autumn, winter
            }
        } //check value 4 5
    } else if (_modeThermalBreakage == 1) {
        QList<Object::Orientation> orientations = this->orientations();

        while (!orientations.isEmpty()) {
            int i = orientations.takeFirst();

            for (int j = 0; j < 4; j++) {
                ThermalObject *object = ProjectCase::currentProject()->thermal()->staticData(i * 4 + j);

                if (object) {
                    Climatic *tmpClimate = new Climatic();
                    QString key = QString::number(i) + QString::number(j);

                    tmpClimate->setFlux(object->flux().toDouble());
                    tmpClimate->setHe(object->he().toDouble());
                    tmpClimate->setHi(object->hi().toDouble());
                    tmpClimate->setTeMax(object->teMax().toDouble());
                    tmpClimate->setTi(object->ti().toDouble());

                    climatics[key] = tmpClimate;
                }
            }
        }
    } else {
        //Specific climate sliding sash
        ThermalObject *object = ProjectCase::currentProject()->thermal()->slidingSashThermalData();

        if (object) {
            Climatic *tmpClimate = new Climatic();
            tmpClimate->setFlux(object->flux().toDouble());
            tmpClimate->setHe(object->he().toDouble());
            tmpClimate->setHi(object->hi().toDouble());
            tmpClimate->setTeMax(object->teMax().toDouble());
            tmpClimate->setTi(object->ti().toDouble());

            climatics["SlidingSash"] = tmpClimate;
        }
    }

    _climatic = climatics;
}

void ThermalBreakageClimaticCondition::normalClimaticCondition()
{
    QMap<QString, Climatic *> climaticsRegTrans;
    QMap<QString, Climatic *> climaticsRegPerm;

    Object::Season season;
    QList<Object::Orientation> orientations = this->orientations();

    QString zoneVE = ProjectCase::currentProject()->locations()->getZoneVE();
    QString zoneVH = ProjectCase::currentProject()->locations()->getZoneVH();
    QString zoneVA = ProjectCase::currentProject()->locations()->getZoneVA();

    double inclination = ProjectCase::currentProject()->glassParameters()->inclination();
    double altitude = ProjectCase::currentProject()->locations()->altitude();

    bool zoneUrbaine = ProjectCase::currentProject()->locations()->urbanZone();
    bool zoneCotiere = ProjectCase::currentProject()->locations()->coastalZone();

    bool isAirCondition = ProjectCase::currentProject()->thermal()->airCondition();
    bool isHeated = ProjectCase::currentProject()->thermal()->heated();

    int numDepartement = ProjectCase::currentProject()->locations()->department();

    for (int i = 0; i < 4; i++) {
        switch (i) {
            case 0:
                season = Object::Season::Spring;
                break;

            case 1:
                season = Object::Season::Summer;
                break;

            case 2:
                season = Object::Season::Autumn;
                break;

            case 3:
                season = Object::Season::Winter;
                break;

            default:
                break;
        }

        Climatic *tmpClimate = new Climatic();

        tmpClimate->setFlux(calculationFluxRegTrans(zoneUrbaine, inclination, altitude));
        tmpClimate->setHe(calculationHeRegTrans(inclination, season));
        tmpClimate->setHi(calculationHiRegTrans(inclination, season));

        if (_modeThermalBreakage == 0) {
            tmpClimate->setTeMax(round(calculationTeMaxRegTrans(numDepartement, zoneVH, zoneVA, zoneVE, zoneCotiere, altitude, season)));
            tmpClimate->setTeMin(round(calculationTeMinRegTrans(numDepartement, zoneVH, zoneVA, zoneVE, zoneCotiere, altitude, season)));
        } else {
            tmpClimate->setTeMax(/*round*/(calculationTeMaxRegTrans(numDepartement, zoneVH, zoneVA, zoneVE, zoneCotiere, altitude, season)));
            tmpClimate->setTeMin(/*round*/(calculationTeMinRegTrans(numDepartement, zoneVH, zoneVA, zoneVE, zoneCotiere, altitude, season)));
        }
        tmpClimate->setTi(calculationTiRegTrans(season));
        tmpClimate->setFaFlux(calculationFafluRegTrans(zoneUrbaine, inclination, altitude));

        climaticsRegTrans[QString::number(season)] =  tmpClimate;
    }

    if (_modeThermalBreakage == 1) {
        QMap<QString, Climatic *> climaticsGS6;
        climaticsGS6 = climaticConditionGS6();
        climaticsRegPerm = climaticsGS6;

        for (int orient = 0; orient < orientations.size(); orient++) {
            for (int ss = 0; ss < 4 ; ss++) {
                QString key = QString::number(orientations[orient]) + QString::number(ss);

                if (ss == 0) {
                    double teMinSpring = climaticsRegTrans["0"]->teMin();
                    climaticsRegPerm[key]->setTeMax(teMinSpring + 5);
                }

                if (ss == 3) {
                    double teMinWinter = climaticsRegTrans["3"]->teMin();
                    climaticsRegPerm[key]->setTeMax(teMinWinter + 5);
                }

                climaticsRegPerm[key]->setFlux(calculationFluxRegPerm(ss, zoneUrbaine, inclination, altitude, orientations[orient]));
                climaticsRegPerm[key]->setTi(calculationTiRegPerm(zoneVE, isAirCondition, isHeated, ss, inclination, orientations[orient], altitude));
            }
        }
    }

    if (_modeThermalBreakage == 0) {
        _climatic = climaticsRegTrans;
    } else if (_modeThermalBreakage == 1) {
        _climatic = climaticsRegPerm;
    } else if (_modeThermalBreakage == 2) {
        _climatic = climaticConditionsThermalBreakageSlidingSlash();
    }
}

std::map<string, ClimateConditions::Climate *> ThermalBreakageClimaticCondition::getClimaticConditionCore()
{
    map<string, ClimateConditions::Climate *> clone;

    for (auto it = this->_climatic.begin(); it != this->_climatic.end(); it++) {
        string key = it.key().toStdString();
        ClimateConditions::Climate *value = (*it)->toCoreObject();
        clone[key] = value;
    }

    return clone;
}

QMap<QString, Climatic *> ThermalBreakageClimaticCondition::climatic() const
{
    return _climatic;
}

void ThermalBreakageClimaticCondition::setClimatic(const QMap<QString, Climatic *> &climatic)
{
    _climatic = climatic;
}

double ThermalBreakageClimaticCondition::calculationFluxRegTrans(bool urbanZone, double incline, double altitude)
{
    double flux1, flux2;
    double indexSite;

    if (altitude <= 500) {
        if (urbanZone) {
            indexSite = 1;
        } else {
            indexSite = 1.07;
        }
    } else if (500 < altitude && altitude <= 1000) {
        if (urbanZone) {
            indexSite = 1.07f;
        } else {
            indexSite = 1.13;
        }
    } else if (altitude > 1000) {
        if (urbanZone) {
            indexSite = 1.2;
        } else {
            indexSite = 1.27;
        }
    }

    if (incline > 75) {
        flux1 = 750;
    } else if (75 >= incline && incline > 60) {
        flux1 = 850;
    } else if (60 >= incline && incline > 45) {
        flux1 = 900;
    } else if (45 >= incline && incline > 0) {
        flux1 = 950;
    } else if (incline == 0) {
        flux1 = 900;
    }

    flux2 = indexSite * flux1;

    qDebug() << "flux 2 = " << flux2;
    qDebug() << "round(flux2 / 50) = " << qRound(flux2 / 50);

    return qRound(flux2 / 50) * 50; // in VD they use "CInt(Flux2 / 50) * 50 " which does rounding
}

double ThermalBreakageClimaticCondition::calculationHeRegTrans(double incline, Object::Season season)
{
    double tmpHe = 99999;

    switch (season) {
        case Object::Season::Spring:
            if (incline > 60) {
                tmpHe = 11;
            } else {
                tmpHe = 15;
            }

            break;

        case Object::Season::Summer:
            if (incline > 60) {
                tmpHe = 13;
            } else {
                tmpHe = 15;
            }

            break;

        case Object::Season::Autumn:
            if (incline > 60) {
                tmpHe = 11;
            } else {
                tmpHe = 15;
            }

            break;

        case Object::Season::Winter:
            if (incline > 60) {
                tmpHe = 11;
            } else {
                tmpHe = 15;
            }

            break;

        default:
            break;
    }

    return tmpHe;
}

double ThermalBreakageClimaticCondition::calculationHiRegTrans(double incline, Object::Season season)
{
    double tmpHi = 99999;

    switch (season) {
        case Object::Season::Spring:
            if (incline >= 60) {
                tmpHi = 9;
            } else {
                tmpHi = 6;
            }

            break;

        case Object::Season::Summer:
            if (incline >= 60) {
                tmpHi = 9;
            } else {
                tmpHi = 6;
            }

            break;

        case Object::Season::Autumn:
            if (incline >= 60) {
                tmpHi = 9;
            } else {
                tmpHi = 6;
            }

            break;

        case Object::Season::Winter:
            if (incline >= 60) {
                tmpHi = 9;
            } else {
                tmpHi = 11;
            }

            break;

        default:
            break;
    }

    return tmpHi;
}

double ThermalBreakageClimaticCondition::calculationTeMaxRegTrans(int numDepartment, QString zoneVH, QString zoneVA, QString zoneVE, bool zoneCotiere, double altitude, Object::Season season)
{
    double amplitude ;
    double tmpTeMax = 99999;

    if (zoneVA == "VA1" || zoneCotiere) {
        zoneVA = "VA1";
        amplitude = 15;
    } else if (zoneVA == "VA2") {
        amplitude = 20;
    }

    double teMin = calculationTeMin(numDepartment, zoneVH, zoneVA, zoneCotiere, altitude);
    double teMax = calculationTeMax(zoneCotiere, zoneVE, zoneVA, altitude);

    switch (season) {
        case Object::Season::Spring:
            tmpTeMax = (2.0f / 3.0f) * (teMin + (amplitude / 2)) + (1.0f / 3.0f) * (teMax - amplitude / 2) + (amplitude / 2);
            break;

        case Object::Season::Summer:
            tmpTeMax = teMax;
            break;

        case Object::Season::Autumn:
            tmpTeMax = (1.0f / 3.0f) * (teMin + (amplitude / 2)) + (2.0f / 3.0f) * (teMax - amplitude / 2) + (amplitude / 2);
            break;

        case Object::Season::Winter:
            tmpTeMax = teMin + amplitude;

        default:
            break;
    }

    return tmpTeMax;
}

double ThermalBreakageClimaticCondition::calculationTiRegTrans(Object::Season season)
{
    double tmpTi = 99999;

    switch (season) {
        case Object::Season::Spring:
            tmpTi = 20;
            break;

        case Object::Season::Summer:
            tmpTi = 25;
            break;

        case Object::Season::Autumn:
            tmpTi = 20;
            break;

        case Object::Season::Winter:
            tmpTi = 20;
            break;

        default:
            break;
    }

    return tmpTi;
}

double ThermalBreakageClimaticCondition::calculationTeMinRegTrans(int numDepartment, QString zoneVH, QString zoneVA, QString zoneVE, bool zoneCotiere, double altitude, Object::Season season)
{
    double amplitude ;
    double tmpTeMin;

    if (zoneVA == "VA1" || zoneCotiere) {
        zoneVA = "VA1";
        amplitude = 15;
    } else if (zoneVA == "VA2") {
        amplitude = 20;
    }

    double teMin = calculationTeMin(numDepartment, zoneVH, zoneVA, zoneCotiere, altitude);
    double teMax = calculationTeMax(zoneCotiere, zoneVE, zoneVA, altitude);

    switch (season) {
        case Object::Season::Spring:
            tmpTeMin = (2.0f / 3.0f) * (teMin + (amplitude / 2)) + (1.0f / 3.0f) * (teMax - amplitude / 2) - (amplitude / 2);
            break;

        case Object::Season::Summer:
            tmpTeMin = teMax - amplitude;
            break;

        case Object::Season::Autumn:
            tmpTeMin = (1.0f / 3.0f) * (teMin + (amplitude / 2)) + (2.0f / 3.0f) * (teMax - amplitude / 2) - (amplitude / 2);
            break;

        case Object::Season::Winter:
            tmpTeMin = teMin;
            break;

        default:
            break;
    }

    return tmpTeMin;
}

double ThermalBreakageClimaticCondition::calculationFafluRegTrans(bool urbanZone, double incline, double altitude)
{
    double flux1 , flux2;

    if (incline > 75) {
        flux1 = 750;
    } else if (75 >= incline && incline > 60) {
        flux1 = 850;
    } else if (60 >= incline && incline > 45) {
        flux1 = 900;
    } else if (45 >= incline && incline > 0) {
        flux1 = 950;
    } else if (incline == 0) {
        flux1 = 900;
    }

    flux2 = calculationFluxRegTrans(urbanZone, incline, altitude);
    return flux2 / flux1;
}

QMap<QString, Climatic *> ThermalBreakageClimaticCondition::climaticConditionGS6()
{
    QMap<QString, Climatic *> tabConditionClimateGS6;
    QList<Object::Orientation> orientations = this->orientations();
    Object::Orientation orientation;
    Object::Season season;

    int amplitudeGS6 = 0;

    bool isAirCondition = ProjectCase::currentProject()->thermal()->airCondition();
    bool isHeated = ProjectCase::currentProject()->thermal()->heated();

    int numDepartement = ProjectCase::currentProject()->locations()->department();

    double inclinaison = ProjectCase::currentProject()->glassParameters()->inclination();
    double projectAltitude = ProjectCase::currentProject()->locations()->altitude();

    bool isCityZone = ProjectCase::currentProject()->locations()->coastalZone();
    bool isUrbanZone = ProjectCase::currentProject()->locations()->urbanZone();

    QString zoneVE = ProjectCase::currentProject()->locations()->getZoneVE();
    QString zoneVH = ProjectCase::currentProject()->locations()->getZoneVH();
    QString zoneVA = ProjectCase::currentProject()->locations()->getZoneVA();

    if (zoneVA == "VA1") {
        amplitudeGS6 = 15;
    } else if (zoneVA == "VA2") {
        if (isCityZone) {
            amplitudeGS6 = 15;
        } else {
            amplitudeGS6 = 20;
        }
    } else {
        amplitudeGS6 = 0;
    }

    for (int i = 0; i < orientations.size(); i++) {
        switch (orientations[i]) {
            case 0:
                orientation = Object::Orientation::North; //"N"
                break;

            case 1:
                orientation = Object::Orientation::NorthEast; //"NE"
                break;

            case 2:
                orientation = Object::Orientation::East;   //"E"
                break;

            case 3:
                orientation = Object::Orientation::SouthEast;    //"SE"
                break;

            case 4:
                orientation = Object::Orientation::South;       //"S"
                break;

            case 5:
                orientation = Object::Orientation::SouthWest; //"SO"
                break;

            case 6:
                orientation = Object::Orientation::West ;   //"O"
                break;

            case 7:
                orientation = Object::Orientation::NorthWest;     //"NO"
                break;

            case 8:
                orientation = Object::Orientation::StandardConditions;     // b1206 p11
                break;

            default:
                break;
        }

        for (int i = 0; i < 4; i++) {
            switch (i) {
                case 0:
                    season = Object::Season::Spring;
                    break;

                case 1:
                    season = Object::Season::Summer;
                    break;

                case 2:
                    season = Object::Season::Autumn;
                    break;

                case 3:
                    season = Object::Season::Winter;
                    break;

                default:
                    break;
            }

            Climatic *climate = new Climatic();

            climate->setFlux(calculationFluxGS6(isUrbanZone, inclinaison, projectAltitude, orientation, season));
            climate->setHe(calculationHeGS6(inclinaison, season));
            climate->setHi(calculationHiGS6(inclinaison, season));
            climate->setTeMax(calculationTeMaxGS6(zoneVE, season, projectAltitude, orientation, inclinaison));
            climate->setTi(calculationTiGS6(zoneVE, isAirCondition, isHeated, season, inclinaison, orientation, projectAltitude));
            climate->setTeMin(calculationTeMinGS6(numDepartement, zoneVH, zoneVA, isCityZone, season, projectAltitude));

            if (season != Object::Season::Winter) {
                climate->setTeMin(climate->teMax() - amplitudeGS6);
            } else {
                climate->setTeMax(climate->teMin() + amplitudeGS6);
            }

            QString key = QString::number(orientation) + QString::number(season);
            tabConditionClimateGS6[key] = climate;
        }
    }

    return tabConditionClimateGS6;
}

double ThermalBreakageClimaticCondition::calculationFluxGS6(bool urbanZone, double inclinaison, double altitude, Object::Orientation orientation, Object::Season saison)
{
    double flux1 = 800;

    double flux2 = 0;
    double flux3 = 0;

    if (urbanZone == true) {
        flux2 = 0.94 * flux1;
    } else {
        flux2 = flux1;
    }

    if (altitude < 500) {
        flux3 = flux2;
    } else if (500 <= altitude && altitude <= 2000) {
        flux3 = flux2 * (1 + ((altitude - 500) / 10000));
    } else if (altitude > 2000) {
        flux3 = 920;
    }

    if (saison == Object::Season::Winter) {
        return 0;
    } else {
        return approxVect(saison == Object::Season::Summer ? 1 : 0, (int)orientation, inclinaison) * flux3;
    }
}

double ThermalBreakageClimaticCondition::calculationHeGS6(double inclinaison, Object::Season saison)
{
    switch (saison) {
        case Object::Season::Spring: // "printemps"
            if (inclinaison >= 60) {
                return 11;
            } else {
                return  12;
            }

            break;

        case Object::Season::Summer: // "ete"
            if (inclinaison >= 60) {
                return  13;
            } else {
                return  14;
            }

            break;

        case Object::Season::Autumn: //"automne"
            if (inclinaison >= 60) {
                return 11;
            } else {
                return  12;
            }

            break;

        case Object::Season::Winter: // "hiver"
            if (inclinaison >= 60) {
                return  11;
            } else {
                return  12;
            }

            break;

        default:
            return  9999999;
    }
}

double ThermalBreakageClimaticCondition::calculationHiGS6(double inclinaison, Object::Season saison)
{
    switch (saison) {
        case Object::Season::Spring: // "printemps"
            if (inclinaison >= 60) {
                return 9;
            } else {
                return 6;
            }

        case Object::Season::Summer: // "ete"
            if (inclinaison >= 60) {
                return 9;
            } else {
                return 6;
            }

        case Object::Season::Autumn: // "automne"
            if (inclinaison >= 60) {
                return 9;
            } else {
                return 6;
            }

        case Object::Season::Winter: // "hiver"
            if (inclinaison >= 60) {
                return 9;
            } else {
                return 11;
            }

        default:
            return 999999;
    }
}

double ThermalBreakageClimaticCondition::calculationTeMaxGS6(QString zoneVE, Object::Season saison, double altitude, Object::Orientation orientation, double inclinaison)
{
    double Temax1, Temax2, Temax3;

    if (zoneVE == "VE1") {
        Temax1 = 32;
    } else if (zoneVE == "VE2") {
        Temax1 = 35;
    } else if (zoneVE == "VE3") {
        Temax1 = 38;
    } else if (zoneVE == "VE4") {
        Temax1 = 42;
    } else {
        Temax1 = 999999;
    }


    if (altitude > 200) {
        Temax2 = Temax1 - 1 * ((altitude - 200) / 200);
    } else {
        Temax2 = Temax1;
    }

    if (inclinaison < 30) {
        Temax3 = Temax2;
    } else if ((30 <= inclinaison) && (inclinaison <= 60)) {
        switch (orientation) {
            case Object::Orientation::North: // "N"
                Temax3 = Temax2 - 4;
                break;

            case Object::Orientation::NorthEast: // "NE"
                Temax3 = Temax2 - 6;
                break;

            case Object::Orientation::East: // "E"
                Temax3 = Temax2 - 5;
                break;

            case Object::Orientation::SouthEast: // "SE"
                Temax3 = Temax2 - 4;
                break;

            case Object::Orientation::South: // "S"
                Temax3 = Temax2 - 2;
                break;

            case Object::Orientation::SouthWest: // "SO":
                Temax3 = Temax2;
                break;

            case Object::Orientation::West: // "O"
                Temax3 = Temax2 - 2;
                break;

            case Object::Orientation::NorthWest: // "NO"
                Temax3 = Temax2 - 3;
                break;

            default:
                break;
        }
    } else if (inclinaison > 60) {
        switch (orientation) {
            case Object::Orientation::North: // "N"
                Temax3 = Temax2 - 8;
                break;

            case Object::Orientation::NorthEast: // "NE"
                Temax3 = Temax2 - 12;
                break;

            case Object::Orientation::East: // "E"
                Temax3 = Temax2 - 10;
                break;

            case Object::Orientation::SouthEast: // "SE"
                Temax3 = Temax2 - 8;
                break;

            case Object::Orientation::South: // "S"
                Temax3 = Temax2 - 4;
                break;

            case Object::Orientation::SouthWest: // "SO"
                Temax3 = Temax2;
                break;

            case Object::Orientation::West: // "O"
                Temax3 = Temax2 - 4;
                break;

            case Object::Orientation::NorthWest: // "NO"
                Temax3 = Temax2 - 6;
                break;

            default:
                break;
        }
    } else {
    }

    switch (saison) {
        case Object::Season::Spring: // "printemps"
            return Temax3 - 5;

        case Object::Season::Summer: // "ete"
            return Temax3;

        case Object::Season::Autumn: // "automne"
            return Temax3 - 5;

        default:
            return 999999; //Valeur indiquant une valeur bidon:car en hiver ce n'est pas déterminé
            break;
    }
}

double ThermalBreakageClimaticCondition::calculationTiGS6(QString zoneVE, bool isAirCondition, bool isHeated, Object::Season saison, double inclinaison, Object::Orientation orientation, double altitude)
{
    double Te;
    Te = calculationTeMaxGS6(zoneVE, saison, altitude, orientation, inclinaison);

    switch (saison) {
        case Object::Season::Spring: // "printemps"
            if (inclinaison > 60) {
                return 20;
            } else {
                if (isHeated) {
                    return 20;
                } else {
                    return 10;
                }
            }

        case Object::Season::Summer: // "ete"
            if (inclinaison >= 60) {
//                if (isAirCondition) {
//                    return 25;
//                } else {
//                    if (Te > 35) {
//                        return 35;
//                    } else {
//                        return Te;
//                    }
//                }
                return 25; // according to 241) Remarques VD6_V3.pdf
            } else {
                if (isAirCondition) {
                    return 30;
                } else {
                    if (Te > 35) {
                        return 35;
                    } else {
                        return Te;
                    }
                }
            }

        case Object::Season::Autumn: // "automne"
            if (inclinaison > 60) {
                return 20;
            } else {
                if (isHeated) {
                    return 20;
                } else {
                    return 10;
                }
            }

        case Object::Season::Winter: // "hiver"
            if (isHeated) {
                return 15;
            } else {
                return 5;
            }

        default:
            return 999999;
    }
}

double ThermalBreakageClimaticCondition::calculationTeMinGS6(int numDepartment, QString zoneVH, QString zoneVA, bool cityZone,
                                                             Object::Season saison, double altitude)
{
    double Te_min1 = 0;
    double Te_min_GS6 = 999999;

    if (saison == Object::Season::Winter) {
        if (zoneVH == "VH1") {
            Te_min1 = -25;
        } else if (zoneVH == "VH2") {
            Te_min1 = -22;
        } else if (zoneVH == "VH3") {
            Te_min1 = -20;
        } else if (zoneVH == "VH4") {
            Te_min1 = -17;
        } else if (zoneVH ==  "VH5") {
            if (cityZone == true) {
                switch (numDepartment) {
                    case 6:
                        Te_min1 = -13;

                    case 66:
                        Te_min1 = -13;

                    case 83:
                        Te_min1 = -13;

                    default:
                        Te_min1 = -15;
                }
            } else {
                Te_min1 = -15;
            }
        } else if (zoneVH == "VH6") {
            Te_min1 = -13;
        } else {
        }

        if (zoneVA ==  "VA1") {
            if (altitude > 200) {
                Te_min_GS6 = Te_min1 - 1 * ((altitude - 200) / 200);
            } else {
                Te_min_GS6 = Te_min1;
            }
        } else if (zoneVA == "VA2") {
            if (cityZone == true) {
                zoneVA = "VA1";

                if (altitude > 200) {
                    Te_min_GS6 = Te_min1 - 1 * ((altitude - 200) / 200);
                } else {
                    Te_min_GS6 = Te_min1;
                }
            } else { //Cas ou on est en zone VA2 et zone non cotiere
                if (altitude > 200) {
                    Te_min_GS6 = Te_min1 - 1 * ((altitude - 200) / 100);
                } else {
                    Te_min_GS6 = Te_min1;
                }
            }
        } else {
        }
    }  else {
        Te_min_GS6 = 999999;
    }

    return Te_min_GS6;
}

double ThermalBreakageClimaticCondition::calculationTeMin(int numDepartment, QString zoneVH, QString zoneVA, bool cityZone, double altitude)
{
    double teMin1 = 0, tmpTeMin = 0;

    if (zoneVH == "VH1") {
        teMin1 = -25;
    } else if (zoneVH == "VH2") {
        teMin1 = -22;
    } else if (zoneVH == "VH3") {
        teMin1 = -20;
    } else if (zoneVH == "VH4") {
        teMin1 = -17;
    } else if (zoneVH == "VH5") {
        if (cityZone) {
            if (numDepartment == 6 || numDepartment == 66 || numDepartment == 83) {
                teMin1 = -13;
            } else {
                teMin1 = -15;
            }
        } else {
            teMin1 = -15;
        }
    } else if (zoneVH == "VH6") {
        teMin1 = -13;
    }

    if (zoneVA == "VA1") {
        if (altitude > 200) {
            tmpTeMin = teMin1 - 1 * ((altitude - 200) / 200);
        } else {
            tmpTeMin = teMin1;
        }
    } else if (zoneVA == "VA2") {
        if (cityZone) {
            zoneVA = "VA1";

            if (altitude > 200) {
                tmpTeMin = teMin1 - 1 * ((altitude - 200) / 200);
            } else {
                tmpTeMin = teMin1;
            }
        } else {
            if (altitude > 200) {
                tmpTeMin = teMin1 - 1 * ((altitude - 200) / 100);
            } else {
                tmpTeMin = teMin1;
            }
        }
    }

    return tmpTeMin;
}

double ThermalBreakageClimaticCondition::calculationTeMax(bool cityZone, QString zoneVE, QString zoneVA, double altitude)
{
    double teMax1 = 0, tmpTeMax = 0;

    if (zoneVE == "VE1") {
        teMax1 = 32;
    } else if (zoneVE == "VE2") {
        teMax1 = 35;
    } else if (zoneVE == "VE3") {
        teMax1 = 38;
    } else if (zoneVE == "VE4") {
        teMax1 = 42;
    }

    if (zoneVA == "VA1") {
        if (altitude > 200) {
            tmpTeMax = teMax1 - 1 * ((altitude - 200) / 200);
        } else {
            tmpTeMax = teMax1;
        }
    } else if (zoneVA == "VA2") {
        if (cityZone) {
            zoneVA = "VA1";

            if (altitude > 200) {
                tmpTeMax = teMax1 - 1 * ((altitude - 200) / 200);
            } else {
                tmpTeMax = teMax1;
            }
        } else {
            if (altitude > 200) {
                tmpTeMax = teMax1 - 1 * ((altitude - 200) / 100);
            } else {
                tmpTeMax = teMax1;
            }
        }
    }

    return tmpTeMax;
}

double ThermalBreakageClimaticCondition::calculationFluxSlidingSash()
{
    bool isUrbanZone = ProjectCase::currentProject()->locations()->urbanZone();
    double altitude = ProjectCase::currentProject()->locations()->altitude();
    double inclinaison = ProjectCase::currentProject()->glassParameters()->inclination();

    double Coeff_site;
    double Ci;

    double flux0 = 750;

    if (altitude <= 500) {
        if (isUrbanZone) {
            Coeff_site = 1;
        } else {
            Coeff_site = 1.07;
        }
    } else if ((500 < altitude) && (altitude <= 1000)) {
        if (isUrbanZone) {
            Coeff_site = 1.07;
        } else {
            Coeff_site = 1.13;
        }
    } else if (altitude > 1000) {
        if (isUrbanZone) {
            Coeff_site = 1.2;
        } else {
            Coeff_site = 1.27;
        }
    }

    double flux1 = flux0 * Coeff_site;

    Ci = -0.00008 * pow(inclinaison, 2.0) + 0.0048 * inclinaison + 1.2032;

    return Ci * flux1;
}

double ThermalBreakageClimaticCondition::calculationTiRegPerm(QString zoneVE, bool isAirCondition, bool isHeated, int saison,
                                                              double inclinaison, int orientation, double altitude)
{
    double te = 0;
    double ti = INT_MAX;

    Object::Season season = (Object::Season)saison;
    Object::Orientation orient = (Object::Orientation)orientation;

    te = calculationTeMaxGS6(zoneVE, season, altitude, orient, inclinaison);

    switch (saison) {
        case 0: //"printemps"
            if (inclinaison > 60) {
                ti = 20;
            } else {
                if (isHeated) {
                    ti = 20;
                } else {
                    ti = 10;
                }
            }

            break;

        case 1: //"ete"
            if (inclinaison >= 60) {
//                if (isAirCondition) {
//                    ti = 25;
//                } else {
//                    if (te > 35) {
//                        ti = 35;
//                    } else {
//                        ti = te;
//                    }
//                }
                ti = 25; // according to 241) Remarques VD6_V3.pdf
            } else {
                if (isAirCondition) {
                    ti = 30;
                } else {
                    if (te > 35) {
                        ti = 35;
                    } else {
                        ti = te;
                    }
                }
            }

            break;

        case 2: //"automne"
            if (inclinaison > 60) {
                ti = 20;
            } else {
                if (isHeated) {
                    ti = 20;
                } else {
                    ti = 10;
                }
            }

            break;

        case 3: //"hiver"
            if (isHeated) {
                //Ti_Casse_Therm_Reg_Perm = 15
                ti = 20;
            } else {
                ti = 5;
            }

            break;

        default:
            break;
    }

    return ti;
}

double ThermalBreakageClimaticCondition::calculationFluxRegPerm(int saison, bool urbanZone, double inclinaison, double altitude, int orient)
{
    double Flux_Casse_Therm_Reg_Perm = 999999;
    //Reprendre Flux_Casse_Therm_Reg_Perm et utiliser les Ci
    double Flux0, Flux1 ; //Flux_Casse_Therm_Reg_Trans à différentes étapes du calcul
    double Coeff_site ;
    double Ci ;

    //Détermination du flux maximal en fonction de la saison et l//orient pour une paroi verticale
    //Les valeurs fournies par AG
    switch (orient) {
        case 0: //N
            switch (saison) {
                case  0:// "printemps"
                    Flux0 = 110;
                    break;

                case 1: //"ete"
                    Flux0 = 200;
                    break;

                case 2: //"automne"
                    Flux0 = 110;
                    break;

                case 3: //"hiver"
                    Flux0 = 60;
                    break;

                default:
                    break;
            }

            break;

        case 1: //NE
            switch (saison) {
                case  0:// "printemps"
                    Flux0 = 330;
                    break;

                case 1: //"ete"
                    Flux0 = 580;
                    break;

                case 2: //"automne"
                    Flux0 = 330;
                    break;

                case 3: //"hiver"
                    Flux0 = 60;
                    break;

                default:
                    break;
            }

            break;

        case 2: //E
            switch (saison) {
                case  0:// "printemps"
                    Flux0 = 600;
                    break;

                case 1: //"ete"
                    Flux0 = 750;
                    break;

                case 2: //"automne"
                    Flux0 = 600;
                    break;

                case 3: //"hiver"
                    Flux0 = 410;
                    break;

                default:
                    break;
            }

            break;

        case 3: //se
            switch (saison) {
                case  0:// "printemps"
                    Flux0 = 750;
                    break;

                case 1: //"ete"
                    Flux0 = 610;
                    break;

                case 2: //"automne"
                    Flux0 = 750;
                    break;

                case 3: //"hiver"
                    Flux0 = 670;
                    break;

                default:
                    break;
            }

            break;

        case 4: //S
            switch (saison) {
                case  0:// "printemps"
                    Flux0 = 750;
                    break;

                case 1: //"ete"
                    Flux0 = 460;
                    break;

                case 2: //"automne"
                    Flux0 = 750;
                    break;

                case 3: //"hiver"
                    Flux0 = 750;
                    break;

                default:
                    break;
            }

            break;

        case 5: //SO
            switch (saison) {
                case  0:// "printemps"
                    Flux0 = 750;
                    break;

                case 1: //"ete"
                    Flux0 = 610;
                    break;

                case 2: //"automne"
                    Flux0 = 750;
                    break;

                case 3: //"hiver"
                    Flux0 = 670;
                    break;

                default:
                    break;
            }

            break;

        case 6: //O
            switch (saison) {
                case  0:// "printemps"
                    Flux0 = 600;
                    break;

                case 1: //"ete"
                    Flux0 = 750;
                    break;

                case 2: //"automne"
                    Flux0 = 600;
                    break;

                case 3: //"hiver"
                    Flux0 = 410;
                    break;

                default:
                    break;
            }

            break;

        case 7: //NO
            switch (saison) {
                case  0:// "printemps"
                    Flux0 = 330;
                    break;

                case 1: //"ete"
                    Flux0 = 580;
                    break;

                case 2: //"automne"
                    Flux0 = 350;
                    break;

                case 3: //"hiver"
                    Flux0 = 60;
                    break;

                default:
                    break;
            }

            break;

        default:
            break;
    }

    //Prise en compte de l//influence de l//altitude et de la pollution sur le flux incident
    if (altitude <= 500) {
        if (urbanZone == true) {
            Coeff_site = 1;
        } else {
            Coeff_site = 1.07;
        }
    } else if ((500 < altitude) && (altitude <= 1000)) {
        if (urbanZone == true) {
            Coeff_site = 1.07;
        } else {
            Coeff_site = 1.13;
        }
    } else if (altitude > 1000) {
        if (urbanZone == true) {
            Coeff_site = 1.2;
        } else {
            Coeff_site = 1.27;
        }
    }

    Flux1 = Flux0 * Coeff_site;

    //Prise en compte de l//influence de l//inclinaison en utilisant les coefficients Ci
    //Pour l//instant pas de valeurs pour le pritemps et l//automne en attente des résultats d//AG
    Ci = approxVect(saison == Object::Season::Summer ? 1 : saison == Object::Season::Winter ? 2 : 0, -1, inclinaison);

    //Résultats
    Flux_Casse_Therm_Reg_Perm = Ci * Flux1;

    qDebug() << "Flux1 = " << Flux1;
    qDebug() << "Ci = " << Ci;
    qDebug() << "Flux_Casse_Therm_Reg_Perm = " << Flux_Casse_Therm_Reg_Perm;

    if (Flux_Casse_Therm_Reg_Perm < 80) {
        Flux_Casse_Therm_Reg_Perm = 80;
    }

    return Flux_Casse_Therm_Reg_Perm;
}

int ThermalBreakageClimaticCondition::modeThermalBreakage() const
{
    return _modeThermalBreakage;
}

QMap<QString, Climatic *> ThermalBreakageClimaticCondition::climaticConditionsThermalBreakageSlidingSlash()
{
    QMap<QString, Climatic *> slidingSlashClimate;

    Climatic *climate = new Climatic();

    climate->setFlux(calculationFluxSlidingSash());
    climate->setHe(11);
    climate->setHi(9);
    climate->setTeMax(15);
    climate->setTi(20);
    slidingSlashClimate["SlidingSash"] = climate;

    return slidingSlashClimate;
}

int ThermalBreakageClimaticCondition::getModeThermalBreakage() const
{
    return _modeThermalBreakage;
}

void ThermalBreakageClimaticCondition::setModeThermalBreakage(int mode)
{
    _modeThermalBreakage = mode;
}




