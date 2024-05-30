#ifndef WORKSHOP_H
#define WORKSHOP_H
#include "components_global.h"
#include <string>
#include <glassvd.h>
#include <object.h>

using namespace std;
namespace VD6 {
namespace Common{
/**
 * @brief
 *
 */
class COMPONENTSSHARED_EXPORT WorkShop
{
public:
    /**
     * @brief
     *
     */
    class ModifyThicknessLaminateObject {
    public:
        /**
         * @brief
         *
         */
        ModifyThicknessLaminateObject()
        {
            _glassIn = new GlassVD();
            _glassOut = new GlassVD();
            _paneIn = new GlassVD();
            _paneOut = new GlassVD();
        }

        GlassVD* _glassIn; /**< TODO: describe */
        GlassVD* _paneIn; /**< TODO: describe */
        bool spectralIndex; /**< TODO: describe */

        GlassVD* _glassOut; /**< TODO: describe */
        GlassVD* _paneOut; /**< TODO: describe */
    };
};
}
}

#endif // WORKSHOP_H
