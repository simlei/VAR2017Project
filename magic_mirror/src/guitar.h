#ifndef GUITAR_H
#define GUITAR_H

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "guitarmeasure.h"

/*
 * This class is a prototype to be implemented
 * whenever a guitar wants to be drawn.
 * What has to be provided, is an abstract description of how the fretboard of the guitar looks.
 * This is done in the obligatory measures arguments.
 *
 * Implementors of this class have to override the customDraw routine
 * in a way that the rendered image and the provided measure is consistent.
 * to test this, one can call the method "auxDraw" in "customDraw" to paint the local coordinate system
 * and the bounding box of the fretboard according to the measurements.
 *
 * if customDraw is not overridden, auxDraw is called by default in customDraw to provide a very basic visualization.
 *
 */
class Guitar: public ofNode
{
public:
    Guitar(GuitarMeasure &measures);
    ~Guitar();

    virtual void setup(); // to do everything the constructor can't. Probably, set up OpenGL graphics directives.
    void customDraw(); // by default calls auxDraw for coordsys/bounding box rendering
    void auxDraw(); // draws a basic coordinate system and bounding box

    // contains everything about the geometry of the fretboard
    GuitarMeasure measures;

private:

    // coordinate system and boiunding box primitives
    ofPath ksX;
    ofPath ksY;
    ofPath ksZ;
};

#endif // GUITAR_H
