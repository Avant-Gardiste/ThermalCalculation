#ifndef CLIMATIC_H
#define CLIMATIC_H

#include "climaticconditionwrapper_global.h"
#include "climateconditions.h"

#include <QObject>

using namespace VD6::Common;

/**
 * @brief
 *
 */
class CLIMATICCONDITIONWRAPPERSHARED_EXPORT Climatic : public QObject
{
    Q_OBJECT

    Q_PROPERTY(double flux READ flux WRITE setFlux NOTIFY fluxChanged)
    Q_PROPERTY(double he READ he WRITE setHe NOTIFY heChanged)
    Q_PROPERTY(double hi READ hi WRITE setHi NOTIFY hiChanged)

    Q_PROPERTY(double teMax READ teMax WRITE setTeMax NOTIFY teMaxChanged)
    Q_PROPERTY(double ti READ ti WRITE setTi NOTIFY tiChanged)
    Q_PROPERTY(double teMin READ teMin WRITE setTeMin NOTIFY teMinChanged)

    Q_PROPERTY(double faFlux READ faFlux WRITE setFaFlux NOTIFY faFluxChanged)

public:
    /**
     * @brief
     *
     * @param parent
     */
    explicit Climatic(QObject *parent = 0);
    /**
     * @brief
     *
     * @param clone
     */
    explicit Climatic(Climatic *clone);

    /**
     * @brief
     *
     * @return ClimateConditions::Climate
     */
    ClimateConditions::Climate *toCoreObject();

    /**
     * @brief
     *
     * @return double
     */
    double flux() const;
    /**
     * @brief
     *
     * @param flux
     */
    void setFlux(double flux);

    /**
     * @brief
     *
     * @return double
     */
    double he() const;
    /**
     * @brief
     *
     * @param he
     */
    void setHe(double he);

    /**
     * @brief
     *
     * @return double
     */
    double hi() const;
    /**
     * @brief
     *
     * @param hi
     */
    void setHi(double hi);

    /**
     * @brief
     *
     * @return double
     */
    double teMax() const;
    /**
     * @brief
     *
     * @param teMax
     */
    void setTeMax(double teMax);

    /**
     * @brief
     *
     * @return double
     */
    double ti() const;
    /**
     * @brief
     *
     * @param ti
     */
    void setTi(double ti);

    /**
     * @brief
     *
     * @return double
     */
    double teMin() const;
    /**
     * @brief
     *
     * @param teMin
     */
    void setTeMin(double teMin);

    /**
     * @brief
     *
     * @return double
     */
    double faFlux() const;
    /**
     * @brief
     *
     * @param faFlux
     */
    void setFaFlux(double faFlux);

signals:
    /**
     * @brief
     *
     */
    void fluxChanged();
    /**
     * @brief
     *
     */
    void heChanged();
    /**
     * @brief
     *
     */
    void hiChanged();

    /**
     * @brief
     *
     */
    void teMaxChanged();
    /**
     * @brief
     *
     */
    void tiChanged();
    /**
     * @brief
     *
     */
    void teMinChanged();

    /**
     * @brief
     *
     */
    void faFluxChanged();

private:
    double _flux; /**< TODO: describe */
    double _he; /**< TODO: describe */
    double _hi; /**< TODO: describe */

    double _teMax; /**< TODO: describe */
    double _ti; /**< TODO: describe */
    double _teMin; /**< TODO: describe */

    double _faFlux; /**< TODO: describe */
};

#endif // CLIMATIC_H
