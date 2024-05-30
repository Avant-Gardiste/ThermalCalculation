#include "defineblind.h"

#include "common.h"

using namespace VD6::Common;

DefineBlind::DefineBlind()
{
    _topSpace = 0;

    _slatsDistance = 0;
    _slatsWidth = 0;

    _infraredTransmission = 0;
    _positionSlats = 0;
    _colorSlats = "";

    _positionBlind = -1;
    _positionVentilationToBlind = -1;

    _spectralIndex = false;
}

DefineBlind::DefineBlind(DefineBlind *clone)
{
    if (clone) {
        this->_listId = clone->getListId();

        this->_spectralIndex = clone->getSpectralIndex();
        this->_reverse = clone->getReverse();

        this->_numberBlind = clone->numberBlind();

        this->_distanceBlindGlazing = clone->getDistanceBlindGlazing();
        this->_positionVentilationToBlind = clone->getPositionVentilationToBlind();
        this->_positionBlind = clone->getPositionBlind();

        this->_typeMovementBlind = clone->getTypeMovementBlind();

        this->_topSpace = clone->getTopSpace();
        this->_lateralSpace = clone->getLateralSpace();
        this->_bottomSpace = clone->getBottomSpace();
        this->_tth = clone->getTth();

        this->_slatsDistance = clone->getSlatsDistance();
        this->_slatsWidth = clone->getSlatsWidth();

        this->_infraredTransmission = clone->getInfraredTransmission();
        this->_porosity = clone->getPorosity();

        this->_positionSlats = clone->getPositionSlats();
        this->_colorSlats = clone->getColorSlats();

        this->_characteristicsBlindVenetian = clone->getCharacteristicsBlindVenetian();

        this->_blinds.clear();

        int size = clone->blindCount();

        for (int i = 0; i < size; i++) {
            this->_blinds.push_back(new BlindVD(clone->blind(i)));
        }
    } else {
        _topSpace = 0;

        _slatsDistance = 0;
        _slatsWidth = 0;

        _infraredTransmission = 0;
        _positionSlats = 0;
        _colorSlats = "";

        _positionBlind = -1;
        _positionVentilationToBlind = -1;

        _spectralIndex = false;
    }
}

DefineBlind::~DefineBlind()
{
    for (vector<BlindVD*>::iterator it = _blinds.begin();it != _blinds.end(); it++) {
        delete (*it);
    }
}

bool DefineBlind::spectralIndex() const
{
    return _spectralIndex;
}

void DefineBlind::setSpectralIndex(bool spectralIndex)
{
    _spectralIndex = spectralIndex;
}

int DefineBlind::numberBlind() const
{
    return _numberBlind;
}

void DefineBlind::setNumberBlind(int numberBlind)
{
    _numberBlind = numberBlind;
}

double DefineBlind::getDistanceBlindGlazing() const
{
    return _distanceBlindGlazing;
}

void DefineBlind::setDistanceBlindGlazing(double value)
{
    _distanceBlindGlazing = value;
}

int DefineBlind::getPositionBlind() const
{
    return _positionBlind;
}

void DefineBlind::setPositionBlind(int positionBlind)
{
    _positionBlind = positionBlind;
}

int DefineBlind::getTypeMovementBlind() const
{
    return _typeMovementBlind;
}

void DefineBlind::setTypeMovementBlind(int typeMovementBlind)
{
    _typeMovementBlind = typeMovementBlind;
}

double DefineBlind::getTopSpace() const
{
    return _topSpace;
}

void DefineBlind::setTopSpace(double value)
{
    _topSpace = value;
}

double DefineBlind::getLateralSpace() const
{
    return _lateralSpace;
}

void DefineBlind::setLateralSpace(double lateralSpace)
{
    _lateralSpace = lateralSpace;
}

double DefineBlind::getBottomSpace() const
{
    return _bottomSpace;
}

void DefineBlind::setBottomSpace(double bottomSpace)
{
    _bottomSpace = bottomSpace;
}

double DefineBlind::getTth() const
{
    return _tth;
}

void DefineBlind::setTth(double tth)
{
    _tth = tth;
}

vector<int> DefineBlind::getListId() const
{
    return _listId;
}

void DefineBlind::setListId(const vector<int> &listId)
{
    _listId = listId;
}

vector<BlindVD *> DefineBlind::getBlinds() const
{
    return _blinds;
}

void DefineBlind::setBlinds(const vector<BlindVD *> &blinds)
{
    _blinds = blinds;
}

int DefineBlind::blindCount()
{
    return _blinds.size();
}

BlindVD *DefineBlind::blind(int index)
{
    if (index < _blinds.size()) {
        return _blinds[index];
    }

    return NULL;
}

vector<int> DefineBlind::getReverse() const
{
    return _reverse;
}

void DefineBlind::setReverse(const vector<int> &value)
{
    _reverse = value;
}

double DefineBlind::getSlatsDistance() const
{
    return _slatsDistance;
}

void DefineBlind::setSlatsDistance(double slatsDistance)
{
    _slatsDistance = slatsDistance;
}

double DefineBlind::getSlatsWidth() const
{
    return _slatsWidth;
}

void DefineBlind::setSlatsWidth(double slatsWidth)
{
    _slatsWidth = slatsWidth;
}

double DefineBlind::getInfraredTransmission() const
{
    return _infraredTransmission;
}

void DefineBlind::setInfraredTransmission(double infraredTransmission)
{
    _infraredTransmission = infraredTransmission;
}

int DefineBlind::getPositionSlats() const
{
    return _positionSlats;
}

void DefineBlind::setPositionSlats(int positionSlats)
{
    _positionSlats = positionSlats;
}

string DefineBlind::getColorSlats() const
{
    return _colorSlats;
}

void DefineBlind::setColorSlats(const string &colorSlats)
{
    _colorSlats = colorSlats;
}

vector<double> DefineBlind::getCharacteristicsBlindVenetian() const
{
    return _characteristicsBlindVenetian;
}

void DefineBlind::setCharacteristicsBlindVenetian(const vector<double> &characteristicsBlindVenetian)
{
    _characteristicsBlindVenetian = characteristicsBlindVenetian;
}

int DefineBlind::getPositionVentilationToBlind() const
{
    return _positionVentilationToBlind;
}

void DefineBlind::setPositionVentilationToBlind(int positionVentilationToBlind)
{
    _positionVentilationToBlind = positionVentilationToBlind;
}

double DefineBlind::getPorosity() const
{
    return _porosity;
}

void DefineBlind::setPorosity(double porosity)
{
    _porosity = porosity;
}

bool DefineBlind::getSpectralIndex() const
{
    return _spectralIndex;
}

bool DefineBlind::equal(DefineBlind *another)
{
    if (!another) {
        return false;
    }

    if (this->_listId != another->getListId()) {
        return false;
    }

    if (this->_reverse != another->getReverse()) {
        return false;
    }

    if (this->_spectralIndex != another->getSpectralIndex()) {
        return false;
    }

    if (this->_numberBlind != another->numberBlind()) {
        return false;
    }

    if (!equalDouble(this->_distanceBlindGlazing, another->getDistanceBlindGlazing())) {
        return false;
    }

    if (this->_positionVentilationToBlind != another->getPositionVentilationToBlind()) {
        return false;
    }
    if (this->_positionBlind != another->getPositionBlind()) {
        return false;
    }

    if (this->_typeMovementBlind != another->getTypeMovementBlind()) {
        return false;
    }

    if (!equalDouble(this->_topSpace, another->getTopSpace())) {
        return false;
    }

    if (!equalDouble(this->_lateralSpace, another->getLateralSpace())) {
        return false;
    }

    if (!equalDouble(this->_bottomSpace, another->getBottomSpace())) {
        return false;
    }

    if (!equalDouble(this->_slatsDistance, another->getSlatsDistance())) {
        return false;
    }

    if (!equalDouble(this->_slatsWidth, another->getSlatsWidth())) {
        return false;
    }

    if (!equalDouble(this->_infraredTransmission, another->getInfraredTransmission())) {
        return false;
    }

    if (!equalDouble(this->_porosity, another->getPorosity())) {
        return false;
    }

    if (this->_positionSlats != another->getPositionSlats()) {
        return false;
    }

    if (this->_characteristicsBlindVenetian != another->getCharacteristicsBlindVenetian()) {
        return false;
    }

    if (this->blindCount() != another->blindCount()) {
        return false;
    } else {
        int size = this->blindCount();

        for (int i = 0; i < size; i++) {
            if (!this->blind(i)->equal(another->blind(i))) {
                return false;
            }
        }
    }

    return true;
}
