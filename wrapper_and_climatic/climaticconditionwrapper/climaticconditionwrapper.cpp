#include "climaticconditionwrapper.h"

bool ClimaticConditionWrapper::_initialized = false;

ClimaticConditionWrapper *ClimaticConditionWrapper::_currentClimatic = NULL;

ClimaticConditionWrapper *ClimaticConditionWrapper::currentClimatic()
{
    if (_currentClimatic == NULL) {
        ClimaticConditionWrapper::_currentClimatic = new ClimaticConditionWrapper();
    }

    return ClimaticConditionWrapper::_currentClimatic;
}

ClimaticConditionWrapper::ClimaticConditionWrapper(QObject *parent) :
    QObject(parent)
{
    if (!ClimaticConditionWrapper::_initialized) {
        ClimaticConditionWrapper::_initialized = true;

        _baseData = NULL;
        _environments = NULL;

        _orientations = vector<Object::Orientation> {};

        _tmaxClimatics.clear();

        _seasons = vector<Object::Season> { Object::Season::Spring,
                Object::Season::Summer,
                Object::Season::Autumn,
                Object::Season::Winter };

        _climateBaySolarFactor = new BaySolarFactorClimaticConditions(_baseData);
        _climateGlazingSolarFactor = new GlazingSolarFactorClimaticCondition(_baseData);
        _climateGlazingUValue = new GlazingUValueClimaticCondition(_baseData);
        _climateTmaxSealingJoint = new TmaxSealingJointClimaticCondition(_baseData);
        _climateThermalBreakage = new ThermalBreakageClimaticCondition(_baseData);
    }
}

void ClimaticConditionWrapper::calculateClimateCondition()
{
    updateBaseData();

    if (_environments->thermal()->active()) {
        if (_environments->getBaySolarOptionEnabled() && _environments->thermal()->baySolarDataCount() > 0) {
            _climateBaySolarFactor->specificClimaticCondition();
        }

        if (_environments->getGlazingSolarOptionEnabled() && _environments->thermal()->glazingSolarThermalData()) {
            _climateGlazingSolarFactor->specificClimaticCondition();
        }

        if (_environments->getGlazingCoeffUOptionEnabled() && _environments->thermal()->glazingUValueThermalData()) {
            _climateGlazingUValue->specificClimaticCondition();
        }

        if ((_environments->getSealingJointVECOptionEnabled() || _environments->getSealingJointOptionEnabled() || _environments->getTemperaturesOptionEnabled()) &&
                 _environments->thermal()->temperatureDataCount() > 0) {
            _climateTmaxSealingJoint->specificClimaticCondition();
        }

        if (_environments->getThermalOptionEnabled() &&
                (_environments->thermal()->dynamicDataCount() > 0 || _environments->thermal()->staticDataCount() > 0 || _environments->thermal()->slidingSashThermalData())) {
            _climateThermalBreakage->specificClimaticCondition();
        }
    } else {
        _climateBaySolarFactor->normalClimaticCondition();
        _climateGlazingSolarFactor->normalClimaticCondition();
        _climateGlazingUValue->normalClimaticCondition();
        _climateTmaxSealingJoint->normalClimaticCondition();
        _climateThermalBreakage->normalClimaticCondition();
    }

    emit climaticConditionChanged();

    //Get Te, Ti values of climateTmaxSealingJoint
    if (!compareClimatic(_climateTmaxSealingJoint->climatic())) {
        emit tmaxClimaticsChanged();
    }
}

QVariantMap ClimaticConditionWrapper::tmaxClimatics() const
{
    return _tmaxClimatics;
}

bool ClimaticConditionWrapper::compareClimatic(QMap<QString, Climatic *> data)
{
    bool isEqual = true;

    if (_tmaxClimatics.size() != data.size()) {
        isEqual = false;

        _tmaxClimatics.clear();

        QStringList keys = data.keys();

        for (int i = 0; i < data.size(); i++) {
            QVariantList values = QVariantList{};

            values << QVariant::fromValue(data[keys[i]]->teMax());
            values << QVariant::fromValue(data[keys[i]]->ti());

            _tmaxClimatics.insert(keys[i], QVariant::fromValue(values));
        }
    } else {
        QStringList keys = data.keys();

        QStringList deleteKeys;

        foreach (QString key, _tmaxClimatics.keys()) {
            if (!keys.contains(key)) {
                deleteKeys.append(key);
            }
        }

        foreach (QString key, deleteKeys) {
            _tmaxClimatics.remove(key);
        }

        for (int i = 0; i < data.size(); i++) {
            Climatic *temp = NULL;

            if (_tmaxClimatics.count(keys[i])) {
                temp = data[keys[i]];
            }

            QList<double> oldValues = fromVariantList(_tmaxClimatics[keys[i]].toList());

            if (!temp || oldValues.size() < 2 || !equalDouble(temp->teMax(), oldValues[0]) || !equalDouble(temp->ti(), oldValues[1])) {
                isEqual = false;

                QVariantList values = QVariantList{};

                values << QVariant::fromValue(data[keys[i]]->teMax());
                values << QVariant::fromValue(data[keys[i]]->ti());

                _tmaxClimatics.insert(keys[i], QVariant::fromValue(values));
            }
        }
    }

    return isEqual;
}

bool ClimaticConditionWrapper::equalDouble(double a, double b, double threshold)
{
    return qAbs(a - b) <= threshold;
}

QList<double> ClimaticConditionWrapper::fromVariantList(QVariantList data)
{
    QList<double> results;

    for (QVariantList::iterator i = data.begin(); i != data.end(); i++) {
        results.append((*i).toDouble());
    }

    return results;
}

void ClimaticConditionWrapper::updateBaseData()
{
    _climateBaySolarFactor->updateData(this->_baseData);
    _climateGlazingSolarFactor->updateData(this->_baseData);
    _climateGlazingUValue->updateData(this->_baseData);
    _climateTmaxSealingJoint->updateData(this->_baseData);
    _climateThermalBreakage->updateData(this->_baseData);
}

BaySolarFactorClimaticConditions *ClimaticConditionWrapper::climateBaySolarFactor() const
{
    return _climateBaySolarFactor;
}

void ClimaticConditionWrapper::setClimateBaySolarFactor(BaySolarFactorClimaticConditions *climateBaySolarFactor)
{
    _climateBaySolarFactor = climateBaySolarFactor;
}

GlazingSolarFactorClimaticCondition *ClimaticConditionWrapper::climateGlazingSolarFactor() const
{
    return _climateGlazingSolarFactor;
}

void ClimaticConditionWrapper::setClimateGlazingSolarFactor(GlazingSolarFactorClimaticCondition *climateGlazingSolarFactor)
{
    _climateGlazingSolarFactor = climateGlazingSolarFactor;
}

GlazingUValueClimaticCondition *ClimaticConditionWrapper::climateGlazingUValue() const
{
    return _climateGlazingUValue;
}

void ClimaticConditionWrapper::setClimateGlazingUValue(GlazingUValueClimaticCondition *climateGlazingUValue)
{
    _climateGlazingUValue = climateGlazingUValue;
}

TmaxSealingJointClimaticCondition *ClimaticConditionWrapper::climateTmaxSealingJoint() const
{
    return _climateTmaxSealingJoint;
}

void ClimaticConditionWrapper::setClimateTmaxSealingJoint(TmaxSealingJointClimaticCondition *climateTmaxSealingJoint)
{
    _climateTmaxSealingJoint = climateTmaxSealingJoint;
}

vector<Object::Orientation> ClimaticConditionWrapper::orientations() const
{
    return _orientations;
}

void ClimaticConditionWrapper::setOrientations(const vector<Object::Orientation> &orientations)
{
    _orientations = orientations;
}

vector<Object::Season> ClimaticConditionWrapper::seasons() const
{
    return _seasons;
}

void ClimaticConditionWrapper::setSeasons(const vector<Object::Season> &seasons)
{
    _seasons = seasons;
}

ThermalBreakageClimaticCondition *ClimaticConditionWrapper::climateThermalBreakage() const
{
    return _climateThermalBreakage;
}

void ClimaticConditionWrapper::setClimateThermalBreakage(ThermalBreakageClimaticCondition *climateThermalBreakage)
{
    _climateThermalBreakage = climateThermalBreakage;
}

BaseClimaticCondition *ClimaticConditionWrapper::baseData() const
{
    return _baseData;
}

void ClimaticConditionWrapper::setBaseData(BaseClimaticCondition *baseData)
{
    if (_baseData != baseData) {
        _baseData = baseData;

        _baseData->setOrientations(QList<Object::Orientation>::fromVector(QVector<Object::Orientation>::fromStdVector(_orientations)));
    }
}

ProjectCase *ClimaticConditionWrapper::environments() const
{
    return _environments;
}

void ClimaticConditionWrapper::setEnvironments(ProjectCase *environments)
{
    if (environments != _environments) {
        _environments = environments;

        connect(_environments, SIGNAL(orientationChanged()), this, SLOT(onOrientationChanged()));
        connect(_environments, SIGNAL(requestCalculated()), this, SLOT(calculateClimateCondition()));
    }
}

void ClimaticConditionWrapper::onOrientationChanged()
{
    QList<int> orientations = _environments->thermal()->orientations();

    _orientations.clear();

    if (orientations.contains(0)) {
        _orientations.push_back(Object::Orientation::North);
    }

    if (orientations.contains(1)) {
        _orientations.push_back(Object::Orientation::NorthEast);
    }

    if (orientations.contains(2)) {
        _orientations.push_back(Object::Orientation::East);
    }

    if (orientations.contains(3)) {
        _orientations.push_back(Object::Orientation::SouthEast);
    }

    if (orientations.contains(4)) {
        _orientations.push_back(Object::Orientation::South);
    }

    if (orientations.contains(5)) {
        _orientations.push_back(Object::Orientation::SouthWest);
    }

    if (orientations.contains(6)) {
        _orientations.push_back(Object::Orientation::West);
    }

    if (orientations.contains(7)) {
        _orientations.push_back(Object::Orientation::NorthWest);
    }

    if (orientations.contains(8)) { // bugb1206 p11
        _orientations.push_back(Object::Orientation::StandardConditions);
    }

    if (_baseData) {
        _baseData->setOrientations(QList<Object::Orientation>::fromVector(QVector<Object::Orientation>::fromStdVector(_orientations)));
    }

    calculateClimateCondition();

    emit orientationChanged();
}

void ClimaticConditionWrapper::calculationClimaticThermal()
{
    if (!_environments->thermal()->active()) {
        _climateThermalBreakage->normalClimaticCondition();
    } else {
        _climateThermalBreakage->specificClimaticCondition();
    }

    emit climaticConditionThermalChanged();
}

void ClimaticConditionWrapper::setModeThermalBreakage(int mode)
{
    if (mode != this->_climateThermalBreakage->getModeThermalBreakage()) {
        this->_climateThermalBreakage->setModeThermalBreakage(mode);

        calculationClimaticThermal();
    }
}
