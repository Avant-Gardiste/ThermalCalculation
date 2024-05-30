#include "defineglass.h"

#include "common.h"

using namespace VD6::Common;

DefineGlass::DefineGlass()
{

}

DefineGlass::DefineGlass(DefineGlass *clone)
{
    if (clone) {
        this->_spectralIndex = clone->getSpectralIndex();

        this->_numberPane = clone->getNumberPane();
        this->_numberGasgap = clone->getNumberGasgap();

        this->_thicknessTotal = clone->getThicknessTotal();

        this->_glazingPressureEquilibrated = clone->getGlazingPressureEquilibrated();

        this->_listId = clone->getListId();
        this->_reverse = clone->getReverse();

        this->_glasses.clear();

        int size = clone->glassCount();

        for (int i = 0; i < size; i++) {
            this->_glasses.push_back(new GlassVD(clone->glass(i)));
        }

        this->_gasGaps.clear();

        size = clone->gasGapCount();

        for (int i = 0; i < size; i++) {
            this->_gasGaps.push_back(new GasGap(clone->gasGap(i)));
        }
    }
}

DefineGlass::~DefineGlass()
{
    for (vector<GasGap*>::iterator it = _gasGaps.begin(); it != _gasGaps.end(); it++) {
        delete (*it);
    }

    for (vector<GlassVD*>::iterator it = _glasses.begin(); it != _glasses.end(); it++) {
        delete (*it);
    }
}

bool DefineGlass::getSpectralIndex() const
{
    return _spectralIndex;
}

void DefineGlass::setSpectralIndex(bool value)
{
    _spectralIndex = value;
}

vector<GlassVD *> DefineGlass::getGlasses() const
{
    return _glasses;
}

void DefineGlass::setGlasses(const vector<GlassVD *> &value)
{
    _glasses = value;
}

int DefineGlass::glassCount()
{
    return _glasses.size();
}

GlassVD *DefineGlass::glass(int index)
{
    if (index < _glasses.size()) {
        return _glasses[index];
    }

    return NULL;
}

int DefineGlass::getNumberPane() const
{
    return _numberPane;
}

void DefineGlass::setNumberPane(int value)
{
    _numberPane = value;
}

double DefineGlass::getThicknessTotal() const
{
    return _thicknessTotal;
}

void DefineGlass::setThicknessTotal(double value)
{
    _thicknessTotal = value;
}

vector<GasGap *> DefineGlass::getGasGaps() const
{
    return _gasGaps;
}

void DefineGlass::setGasGaps(const vector<GasGap *> &gasGaps)
{
    _gasGaps = gasGaps;
}

int DefineGlass::gasGapCount()
{
    return _gasGaps.size();
}

GasGap *DefineGlass::gasGap(int index)
{
    if (index < _gasGaps.size()) {
        return _gasGaps[index];
    }

    return NULL;
}

vector<int> DefineGlass::getListId() const
{
    return _listId;
}

void DefineGlass::setListId(const vector<int> &listId)
{
    _listId = listId;
}

int DefineGlass::getNumberGasgap() const
{
    return _numberGasgap;
}

void DefineGlass::setNumberGasgap(int numberGasgap)
{
    _numberGasgap = numberGasgap;
}

vector<int> DefineGlass::getReverse() const
{
    return _reverse;
}

void DefineGlass::setReverse(const vector<int> &reverse)
{
    _reverse = reverse;
}

bool DefineGlass::getGlazingPressureEquilibrated() const
{
    return _glazingPressureEquilibrated;
}

void DefineGlass::setGlazingPressureEquilibrated(bool glazingPressureEquilibrated)
{
    _glazingPressureEquilibrated = glazingPressureEquilibrated;
}

vector<int> DefineGlass::getNumCompositionGlass()
{
    vector <int> ncompv;

    for (int i = 0; i < _numberPane ; i++) {
        vector < double> thicknessByClass(5, 0);
        int numComponentGlass = 0;

        thicknessByClass[0] = _glasses[i]->getThickness1();
        thicknessByClass[1] = _glasses[i]->getThickness2();
        thicknessByClass[2] = _glasses[i]->getThickness3();
        thicknessByClass[3] = _glasses[i]->getThickness4();
        thicknessByClass[4] = _glasses[i]->getThickness5();

        for (int j = 0; j < 5; j++) {
            if (thicknessByClass[j] != 0) {
                numComponentGlass++;
            } else {
                break;
            }
        }

        ncompv.push_back(numComponentGlass);
    }

    return ncompv;
}

bool DefineGlass::getExistVentilationGasGaps()
{
    for (int i = 0; i < _numberGasgap; i++) {
        if (_gasGaps[i]->getType() == 2) {
            return true;
        }
    }

    return false;
}

bool DefineGlass::equal(DefineGlass *another)
{
    if (!another) {
        return false;
    }

    if (this->_spectralIndex != another->getSpectralIndex()) {
        return false;
    }

    if (this->_numberPane != another->getNumberPane()) {
        return false;
    }

    if (this->_numberGasgap != another->getNumberGasgap()) {
        return false;
    }

    if (!equalDouble(this->_thicknessTotal, another->getThicknessTotal())) {
        return false;
    }

    if (this->_glazingPressureEquilibrated != another->getGlazingPressureEquilibrated()) {
        return false;
    }

    if (this->_listId != another->getListId()) {
        return false;
    }

    if (this->_reverse != another->getReverse()) {
        return false;
    }

    if (this->glassCount() != another->glassCount()) {
        return false;
    } else {
        int size = this->glassCount();

        for (int i = 0; i < size; i++) {
            if (!this->glass(i)->equal(another->glass(i))) {
                return false;
            }
        }
    }

    if (this->gasGapCount() != another->gasGapCount()) {
        return false;
    } else {
        int size = this->gasGapCount();

        for (int i = 0; i < size; i++) {
            if (!this->gasGap(i)->equal(another->gasGap(i))) {
                return false;
            }
        }
    }

    return true;
}
