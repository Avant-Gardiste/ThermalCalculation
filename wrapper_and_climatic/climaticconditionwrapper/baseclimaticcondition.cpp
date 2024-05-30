#include "baseclimaticcondition.h"

BaseClimaticCondition::BaseClimaticCondition(QObject *parent) : QObject(parent)
{
    _seasons = QList<Object::Season> {};
    _orientations = QList<Object::Orientation> {Object::Orientation::North};

    _fluxApproximately["10"] = QList<double>{ 1.2, 1, 0.8, 0.6, 0.45, 0.33, 0.25 };
    _fluxApproximately["11"] = QList<double>{ 1.2, 1.12, 1.04, 0.97, 0.93, 0.89, 0.87 };
    _fluxApproximately["12"] = QList<double>{ 1.2, 1.21, 1.23, 1.23, 1.2, 1.13, 1 };
    _fluxApproximately["13"] = QList<double>{ 1.2, 1.27, 1.28, 1.24, 1.13, 1, 0.8 };
    _fluxApproximately["14"] = QList<double>{ 1.2, 1.27, 1.27, 1.15, 1.07, 0.97, 0.6 };
    _fluxApproximately["15"] = QList<double>{ 1.2, 1.27, 1.28, 1.24, 1.13, 1, 0.8 };
    _fluxApproximately["16"] = QList<double>{ 1.2, 1.21, 1.23, 1.23, 1.2, 1.13, 1 };
    _fluxApproximately["17"] = QList<double>{ 1.2, 1.12, 1.04, 0.97, 0.93, 0.89, 0.87 };
    _fluxApproximately["00"] = QList<double>{ 0.95, 0.73, 0.6, 0.47, 0.33, 0.23, 0.2 };
    _fluxApproximately["01"] = QList<double>{ 0.95, 0.75, 0.67, 0.57, 0.51, 0.48, 0.47 };
    _fluxApproximately["02"] = QList<double>{ 0.95, 0.97, 1, 1, 0.97, 0.91, 0.8 };
    _fluxApproximately["03"] = QList<double>{ 0.95, 1.09, 1.2, 1.24, 1.24, 1.13, 0.97 };
    _fluxApproximately["04"] = QList<double>{ 0.95, 1.13, 1.27, 1.29, 1.24, 1.13, 0.95 };
    _fluxApproximately["05"] = QList<double>{ 0.95, 1.09, 1.2, 1.24, 1.24, 1.13, 0.97 };
    _fluxApproximately["06"] = QList<double>{ 0.95, 0.97, 1, 1, 0.97, 0.91, 0.8 };
    _fluxApproximately["07"] = QList<double>{ 0.95, 0.75, 0.67, 0.57, 0.51, 0.48, 0.47 };
    _fluxApproximately["0-1"] = QList<double>{ 0.95, 1.1, 1.2, 1.25, 1.2, 1.15, 1 };
    _fluxApproximately["1-1"] = QList<double>{ 1.2, 1.25, 1.25, 1.25, 1.2, 1.15, 1 };
    _fluxApproximately["2-1"] = QList<double>{ 0.5, 0.75, 0.95, 1.05, 1.15, 1.15, 1 };
}

void BaseClimaticCondition::updateData(BaseClimaticCondition *parent)
{
    this->_seasons = parent->_seasons;
    this->_orientations = parent->_orientations;
}

void BaseClimaticCondition::specificClimaticCondition()
{
}

void BaseClimaticCondition::normalClimaticCondition()
{
}

std::map<string, ClimateConditions::Climate *> BaseClimaticCondition::getClimaticConditionCore()
{
    return std::map<string, ClimateConditions::Climate *> {};
}

double BaseClimaticCondition::approxVect(int season, int orientation, double inclination)
{
    vector<int> scale = {0, 15, 30, 45, 60, 75, 90};
    vector<double> value = convertVector(_fluxApproximately[QString::number(season) + QString::number(orientation)]);

    int index = -1;
    int nextIndex = -1;
    int previousIndex = -1;

    int nb = value.size();

    if (inclination == scale[0]) {
        index = 0;
    } else if (inclination < scale[0]) {
        nextIndex = 0;
    } else if (inclination > scale[nb - 1]) {
        previousIndex = nb - 1;
    } else {
        for (int i = 0 ; i < nb; i++) {
            if (inclination == scale[i]) {
                index = i;
            } else if (i >= 1) {
                if (inclination < scale[i] && inclination > scale[i - 1]) {
                    nextIndex = i;
                    previousIndex = i - 1;
                }
            }
        }
    }

    if (index != -1) {
        return value[index];
    } else if (previousIndex == nb - 1) {
        return value[nb - 1];
    } else if (nextIndex == 0) {
        return value[0];
    } else { // inclination is not in array scale
        return value[previousIndex] + (((value[nextIndex] - value[previousIndex]) / (scale[nextIndex] - scale[previousIndex])) * (inclination - scale[previousIndex]));
    }

    return 0;
}

QList<Object::Orientation> BaseClimaticCondition::orientations() const
{
    return this == NULL ? QList<Object::Orientation>() : _orientations;
}

void BaseClimaticCondition::setOrientations(const QList<Object::Orientation> &orientations)
{
    _orientations = orientations;
}

QList<Object::Season> BaseClimaticCondition::seasons() const
{
    return _seasons;
}

void BaseClimaticCondition::setSeasons(const QList<Object::Season> &seasons)
{
    _seasons = seasons;
}

vector<double> BaseClimaticCondition::convertVector(QList<double> list)
{
    std::vector<double> vi;
    std::list<double> tmp = list.toStdList();

    copy(tmp.begin(), tmp.end(), back_inserter(vi));

    return vi;
}
