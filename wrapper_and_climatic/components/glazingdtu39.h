#ifndef GLAZINGDTU39_H
#define GLAZINGDTU39_H

#include "components_global.h"

/**
 * @brief
 *
 */
class COMPONENTSSHARED_EXPORT GlazingDTU39
{
public:
     /**
      * @brief
      *
      */
     GlazingDTU39();
     /**
      * @brief
      *
      */
     ~GlazingDTU39();

     /**
      * @brief
      *
      * @return int
      */
     int type() const;
     /**
      * @brief
      *
      * @param type
      */
     void setType(const int &type);

     /**
      * @brief
      *
      * @return int
      */
     int numberLayer() const;
     /**
      * @brief
      *
      * @param numberLayer
      */
     void setNumberLayer(int numberLayer);

     /**
      * @brief
      *
      * @return double
      */
     double gasThickness() const;
     /**
      * @brief
      *
      * @param gasThickness
      */
     void setGasThickness(double gasThickness);

     /**
      * @brief
      *
      * @return int
      */
     int natureType() const;
     /**
      * @brief
      *
      * @param natureType
      */
     void setNatureType(int natureType);

private:
     int _type; /**< TODO: describe */
     int _natureType; /**< TODO: describe */
     int _numberLayer; /**< TODO: describe */

     double _gasThickness; /**< TODO: describe */
};

#endif // GLAZINGDTU39_H
