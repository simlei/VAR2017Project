#ifndef FENDERRENDER_H
#define FENDERRENDER_H

#include "guitar.h"

/*
 * Example guitar renderer. Draws a fender stratocaster.
 * Instead of this, one also could also draw a webcam picture
 * for which the global (camera) coordinates / orientation
 * is provided by setter method, and for which the local measurements
 * (see GuitarMeasure) are known.
 *
 * Note, that this class alone knows which dimensions the fender 3ds model has
 * and as such it hardcodes measurements and drawing of the model s. t. it fits.
 * this single-responsibility principle should be abided by in other implementations also.
 *
 * Please also note, that the class Guitar inherits from ofNode and as such, positioning and orientation
 * are set via the default methods of ofNode.
 */
class FenderRender : public Guitar
{
public:
    FenderRender(); // empty paramList, measurements hardcoded in constructor
    void setup(); // overridden to implement 3d model, lighting and texture stuff
    void customDraw();

private:
    ofxAssimpModelLoader guitarModel;
};

#endif // FENDERRENDER_H
