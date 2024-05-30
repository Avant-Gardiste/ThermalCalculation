#include "tmaxsealingjointclimaticcondition.h"

#include "projectcase.h"

TmaxSealingJointClimaticCondition::TmaxSealingJointClimaticCondition(BaseClimaticCondition *parent) :
    BaseClimaticCondition(parent)
{
}

void TmaxSealingJointClimaticCondition::specificClimaticCondition()
{
    QMap<QString, Climatic *> climatics;

    QList<Object::Orientation> orientation = this->orientations();

    while (!orientation.isEmpty()) {
        int i = orientation.takeFirst();

        for (int j = 0; j < 4; j++) {
            ThermalObject *object = ProjectCase::currentProject()->thermal()->temperatureData(i * 4 + j);

            if (object) {
                Climatic *tmpClimate = new Climatic();
                tmpClimate->setFlux(object->flux().trimmed() == "" ? 0 : object->flux().toDouble());
                tmpClimate->setHe(object->he().trimmed() == "" ? 0 : object->he().toDouble());
                tmpClimate->setHi(object->hi().trimmed() == "" ? 0 : object->hi().toDouble());
                tmpClimate->setTeMax(object->teMax().trimmed() == "" ? 0 : object->teMax().toDouble());
                tmpClimate->setTi(object->ti().trimmed() == "" ? 0 : object->ti().toDouble());
                tmpClimate->setTeMin(object->teMin().trimmed() == "" ? 0 : object->teMin().toDouble());

                climatics[QString::number(i) + QString::number(j)] = tmpClimate;
            }
        }
    }

    _climatic = climatics;
}

void TmaxSealingJointClimaticCondition::normalClimaticCondition()
{
    QMap<QString, Climatic *> climateData;

    QList<Object::Season> seasons = {
        Object::Season::Spring,
        Object::Season::Summer,
        Object::Season::Autumn,
        Object::Season::Winter,
    };

    double indexDepartment = ProjectCase::currentProject()->locations()->department();
    double inclinaisonCalc = ProjectCase::currentProject()->glassParameters()->inclination();

    double altitudeProjet = ProjectCase::currentProject()->locations()->altitude();

    bool zoneUrbaine = ProjectCase::currentProject()->locations()->urbanZone();
    bool zoneCotiere = ProjectCase::currentProject()->locations()->coastalZone();

    double localChauffe = ProjectCase::currentProject()->thermal()->heated();
    double localClimate = ProjectCase::currentProject()->thermal()->airCondition();

    QString zoneVE = ProjectCase::currentProject()->locations()->getZoneVE();
    QString zoneVH = ProjectCase::currentProject()->locations()->getZoneVH();
    QString zoneVA = ProjectCase::currentProject()->locations()->getZoneVA();

    QList<Object::Orientation> orientation = this->orientations();

    for (int i = 0; i < orientation.size(); i++) {
        for (int j = 0; j < 4; j++) {
            Climatic *tmpClimate = new Climatic();
            if (orientation[i] == 8){ // b1206 p11
                tmpClimate->setFlux(calculationFluxStandard(seasons[j], inclinaisonCalc, altitudeProjet));
                tmpClimate->setHe(calculationHeStandard(seasons[j], inclinaisonCalc));
                tmpClimate->setHi(calculationHiStandard(seasons[j], inclinaisonCalc));
                tmpClimate->setTeMax(calculationTeMaxStandard(seasons[j], altitudeProjet));
                tmpClimate->setTi(calculationTiStandard(seasons[j], inclinaisonCalc));
                tmpClimate->setTeMin(calculationTeMinStandard(seasons[j], altitudeProjet));
                climateData[QString::number(orientation[i]) + QString::number(seasons[j])] = tmpClimate;
            }else{
                tmpClimate->setFlux(calculationFlux(zoneUrbaine, inclinaisonCalc, altitudeProjet, orientation[i], seasons[j]));
                tmpClimate->setHe(calculationHe(inclinaisonCalc, seasons[j]));
                tmpClimate->setHi(calculationHi(inclinaisonCalc, seasons[j]));
                tmpClimate->setTeMax(calculationTeMax(zoneVE, seasons[j], altitudeProjet, orientation[i], inclinaisonCalc));
                tmpClimate->setTi(calculationTi(zoneVE, localClimate, localChauffe, seasons[j], inclinaisonCalc, orientation[i], altitudeProjet));
                tmpClimate->setTeMin(calculationTeMin(indexDepartment, zoneVH, zoneVA, zoneCotiere, seasons[j], altitudeProjet));
                climateData[QString::number(orientation[i]) + QString::number(seasons[j])] = tmpClimate;
            }
        }
    }

    _climatic = climateData;
}

std::map<string, ClimateConditions::Climate *> TmaxSealingJointClimaticCondition::getClimaticConditionCore()
{
    map<string, ClimateConditions::Climate *> clone;

    for (auto it = this->_climatic.begin(); it != this->_climatic.end(); it++) {
        string key = it.key().toStdString();
        ClimateConditions::Climate *value = (*it)->toCoreObject();
        clone[key] = value;
    }

    return clone;
}

QMap<QString, Climatic *> TmaxSealingJointClimaticCondition::climatic() const
{
    return _climatic;
}

void TmaxSealingJointClimaticCondition::setClimatic(const QMap<QString, Climatic *> &climatic)
{
    _climatic = climatic;
}

double TmaxSealingJointClimaticCondition::calculationFlux(bool urbanZone, double incline, double altitude, Object::Orientation orientation, Object::Season season)
{
    double flux1 = 800;
    double flux2 = 0, flux3 = 0;

    if (urbanZone) {
        flux2 = 0.94f * flux1;
    } else {
        flux2 = flux1;
    }

    if (altitude < 500.0) {
        flux3 = flux2;
    } else if (500.0 <= altitude && altitude <= 2000.0) {
        flux3 = flux2 * (1 + ((altitude - 500.0) / 10000.0));
    } else if (altitude > 2000) {
        flux3 = 920;
    }

    if (season == Object::Season::Winter) {
        return 0;
    } else {
        return approxVect(season == Object::Season::Summer ? 1 : 0, (int)orientation, incline) * flux3;
    }
}


double TmaxSealingJointClimaticCondition::calculationHe(double incline, Object::Season season)
{
    double tmpHe = 0;

    switch (season) {
        case Object::Season::Spring:
            if (incline > 60) {
                tmpHe = 11;
            } else {
                tmpHe = 12;
            }

            break;

        case Object::Season::Summer:
            if (incline > 60) {
                tmpHe = 13;
            } else {
                tmpHe = 14;
            }

            break;

        case Object::Season::Autumn:
            if (incline > 60) {
                tmpHe = 11;
            } else {
                tmpHe = 12;
            }

            break;

        case Object::Season::Winter:
            if (incline > 60) {
                tmpHe = 11;
            } else {
                tmpHe = 20;
            }

            break;

        default:
            break;
    }

    return tmpHe;
}

double TmaxSealingJointClimaticCondition::calculationHi(double incline, Object::Season season)
{
    return incline > 60 ? 9 : season == Object::Season::Winter ? 11 : 6;
}

double TmaxSealingJointClimaticCondition::calculationTeMax(QString zoneVE, Object::Season season, double altitude, Object::Orientation orientation, double inclinaison)
{
    double maxTe1 = 0, maxTe2 = 0, maxTe3 = 0;

    if (zoneVE == "VE1") {
        maxTe1 = 32;
    } else if (zoneVE == "VE2") {
        maxTe1 = 35;
    } else if (zoneVE == "VE3") {
        maxTe1 = 38;
    } else if (zoneVE == "VE4") {
        maxTe1 = 42;
    }

    if (altitude > 200) {
        maxTe2 = maxTe1 - 1 * ((altitude - 200.0) / 200.0);
    } else {
        maxTe2 = maxTe1;
    }

    if (inclinaison < 30) {
        maxTe3 = maxTe2;
    } else if ((30 <= inclinaison) && (inclinaison <= 60)) {
        switch (orientation) {
            case Object::Orientation::North:
                maxTe3 = maxTe2 - 4;
                break;

            case Object::Orientation::NorthEast:
                maxTe3 = maxTe2 - 6;
                break;

            case Object::Orientation::East:
                maxTe3 = maxTe2 - 5;
                break;

            case Object::Orientation::SouthEast:
                maxTe3 = maxTe2 - 4;
                break;

            case Object::Orientation::South:
                maxTe3 = maxTe2 - 2;
                break;

            case Object::Orientation::SouthWest:
                maxTe3 = maxTe2;
                break;

            case Object::Orientation::West:
                maxTe3 = maxTe2 - 2;
                break;

            case Object::Orientation::NorthWest:
                maxTe3 = maxTe2 - 3;
                break;

            default:
                break;
        }
    } else if (inclinaison > 60) {
        switch (orientation) {
            case Object::Orientation::North:
                maxTe3 = maxTe2 - 8;
                break;

            case Object::Orientation::NorthEast:
                maxTe3 = maxTe2 - 12;
                break;

            case Object::Orientation::East:
                maxTe3 = maxTe2 - 10;
                break;

            case Object::Orientation::SouthEast:
                maxTe3 = maxTe2 - 8;
                break;

            case Object::Orientation::South:
                maxTe3 = maxTe2 - 4;
                break;

            case Object::Orientation::SouthWest:
                maxTe3 = maxTe2;
                break;

            case Object::Orientation::West:
                maxTe3 = maxTe2 - 4;
                break;

            case Object::Orientation::NorthWest:
                maxTe3 = maxTe2 - 6;
                break;

            default:
                break;
        }
    }

    switch (season) {
        case Object::Season::Spring:
            return maxTe3 - 5;
            break;

        case Object::Season::Summer:
            return maxTe3;
            break;

        case Object::Season::Autumn:
            return maxTe3 - 5;
            break;

        default:
            return 999999;
            break;
    }
}

double TmaxSealingJointClimaticCondition::calculationTi(QString zoneVE, bool localClimate, bool localChauffe,
                                                        Object::Season season, double inclinaison,
                                                        Object::Orientation orientation, double altitude)
{
    double valueTi;

    double tmpTe = calculationTeMax(zoneVE, season, altitude, orientation, inclinaison);

    switch (season) {
        case Object::Season::Spring:
            if (inclinaison > 60) {
                valueTi = 20;
            } else {
                if (localChauffe) {
                    valueTi = 20;
                } else {
                    valueTi = 10;
                }
            }

            break;

        case Object::Season::Summer:
            if (inclinaison > 60) {
                if (localClimate) {
                    valueTi = 25;
                } else {
                    if (tmpTe > 35) {
                        valueTi = 35;
                    } else {
                        valueTi = tmpTe;
                    }
                }
            } else {
                if (localClimate) {
                    valueTi = 30;
                } else {
                    if (tmpTe > 35) {
                        valueTi = 35;
                    } else {
                        valueTi = tmpTe;
                    }
                }
            }

            break;

        case Object::Season::Autumn:
            if (inclinaison > 60) {
                valueTi = 20;
            } else {
                if (localChauffe) {
                    valueTi = 20;
                } else {
                    valueTi = 10;
                }
            }

            break;

        case Object::Season::Winter:
            if (localChauffe) {
                valueTi = 15;
            } else {
                valueTi = 5;
            }

            break;

        default:
            break;
    }

    return valueTi;
}

double TmaxSealingJointClimaticCondition::calculationTeMin(int numDepartment, QString zoneVH, QString zoneVA, bool zoneCotiere,
                                                           Object::Season season, double altitude)
{
    double teMin1 = 999999;
    double varTeMin = 999999;

    if (season == Object::Season::Winter) {
        (zoneVH == "VH1") ? (teMin1 = -25) : true;
        (zoneVH == "VH2") ? (teMin1 = -22) : true;
        (zoneVH == "VH3") ? (teMin1 = -20) : true;
        (zoneVH == "VH4") ? (teMin1 = -17) : true;

        if (zoneVH == "VH5") {
            if (zoneCotiere) {
                switch (numDepartment) {
                    case 6:
                        teMin1 = -13;
                        break;

                    case 66:
                        teMin1 = -13;
                        break;

                    case 83:
                        teMin1 = -13;
                        break;

                    default:
                        teMin1 = -15;
                        break;
                }
            } else {
                teMin1 = -15;
            }
        }

        (zoneVH == "VH6") ? (teMin1 = -13) : true;

        if (zoneVA == "VA1") {
            if (altitude > 200) {
                varTeMin = teMin1 - 1 * ((altitude - 200) / 200);
            } else {
                varTeMin = teMin1;
            }
        }

        if (zoneVA == "VA2") {
            if (zoneCotiere) {
                zoneVA = "VA1";

                if (altitude > 200) {
                    varTeMin = teMin1 - 1 * ((altitude - 200) / 200);
                } else {
                    varTeMin = teMin1;
                }
            } else {
                if (altitude > 200) {
                    varTeMin = teMin1 - 1 * ((altitude - 200) / 100);
                } else {
                    varTeMin = teMin1;
                }
            }
        }
    } else {
        varTeMin = 999999;
    }

    return varTeMin;
}

double TmaxSealingJointClimaticCondition::calculationFluxStandard(Object::Season season, double inclinaison, double altitude)
{
    double tmpFluxStandardClimate = 0;

    if (season == Object::Season::Winter) {
        tmpFluxStandardClimate = 0;
    } else {
        if (inclinaison > 60) {
            if (altitude <= 500) {
                tmpFluxStandardClimate = 800;
            } else if ((500 < altitude) && (altitude <= 1000)) {
                tmpFluxStandardClimate = 850;
            } else if ((1000 < altitude) && (altitude < 2000)) {
                tmpFluxStandardClimate = 900;
            } else { // 'Mettre un message d'erreur quand altitude > 2000m
                //check code
            }
        } else {
            if (altitude < 500) {
                tmpFluxStandardClimate = 950;
            } else if ((500 <= altitude) && (altitude < 1000)) {
                tmpFluxStandardClimate = 1000;
            } else if ((1000 <= altitude) && (altitude < 2000)) {
                tmpFluxStandardClimate = 1150;
            }
        }
    }

    return tmpFluxStandardClimate;
}

double TmaxSealingJointClimaticCondition::calculationHeStandard(Object::Season season, double inclinaison)
{
    double valueHeStandardClimate = 0;

    if (season == Object::Season::Winter) {
        if (inclinaison > 60) {
            valueHeStandardClimate = 17;
        } else {
            valueHeStandardClimate = 20;
        }
    } else {
        if (inclinaison > 60) {
            valueHeStandardClimate = 13;
        } else {
            valueHeStandardClimate = 14;
        }
    }

    return valueHeStandardClimate;
}

double TmaxSealingJointClimaticCondition::calculationHiStandard(Object::Season season, double inclinaison)
{
    double valueHiStandardClimate;

    if (season == Object::Season::Winter) {
        if (inclinaison > 60) {
            valueHiStandardClimate = 9;
        } else {
            valueHiStandardClimate = 11;
        }
    } else {
        if (inclinaison > 60) {
            valueHiStandardClimate = 9;
        } else {
            valueHiStandardClimate = 6;
        }
    }

    return valueHiStandardClimate;
}

double TmaxSealingJointClimaticCondition::calculationTeMaxStandard(Object::Season season, double altitude)
{
    double valueTeMaxStanderdClimate = 0;

    switch (season) {
        case Object::Season::Spring:
            if (altitude < 500) {
                valueTeMaxStanderdClimate = 35;
            } else if ((500 <= altitude) && (altitude < 1000)) {
                valueTeMaxStanderdClimate = 32;
            } else if ((1000 <= altitude) && (altitude < 2000)) {
                valueTeMaxStanderdClimate = 26;
            }

            break;

        case Object::Season::Summer:
            if (altitude < 500) {
                valueTeMaxStanderdClimate = 35;
            } else if ((500 <= altitude) && (altitude < 1000)) {
                valueTeMaxStanderdClimate = 32;
            } else if ((1000 <= altitude) && (altitude < 2000)) {
                valueTeMaxStanderdClimate = 26;
            }

            break;

        case Object::Season::Autumn:
            if (altitude < 500) {
                valueTeMaxStanderdClimate = 35;
            } else if (500 <= altitude && altitude < 1000) {
                valueTeMaxStanderdClimate = 32;
            } else if (1000 <= altitude && altitude < 2000) {
                valueTeMaxStanderdClimate = 26;
            }

        default:
            break;
    }

    return valueTeMaxStanderdClimate;
}

double TmaxSealingJointClimaticCondition::calculationTiStandard(Object::Season season, double inclinaison)
{
    if (season == Object::Season::Winter) {
        return 15;
    } else {
        if (inclinaison > 60) {
            return 25;
        } else {
            return 30;
        }
    }
}

double TmaxSealingJointClimaticCondition::calculationTeMinStandard(Object::Season season, double altitude)
{
    if (season == Object::Season::Winter) {
        if (altitude > 200) {
            return (-25) - 1 * ((altitude - 200) / 100);
        } else {
            return -25;
        }
    } else {
        return 999999; //'Pas de valeur pour Temin aux autres saisons
    }
}
