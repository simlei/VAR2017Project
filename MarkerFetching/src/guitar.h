#ifndef GUITAR_H
#define GUITAR_H

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
//#include "guitarmeasure.h"
#include "noteRenderer.h"

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
    Guitar(
            const ofVec3f &posLowerNeck,
            const ofVec3f &posLowerBridge,
            const ofVec3f &posHigherNeck,
            const ofVec3f &posHigherBridge
            );
    ~Guitar();



    static const int MAX_STRING = 6;
    static const int MAX_FRET = 30;

    std::vector<float> fretRatios;

    static void check_access(int stringIdx, int fretIdx) { // centralized checking if fret pos is valid
        if(stringIdx < 0 || stringIdx >= MAX_STRING || fretIdx < 0 || fretIdx >= MAX_FRET) {
            ofLogError("Guitar.cpp") << "string or fret index out of range!";
            ofExit(1);
        }
    }

    virtual void setup(); // to do everything the constructor can't. Probably, set up OpenGL graphics directives.
    void drawdraw();
    void customDraw(); // by default calls auxDraw for coordsys/bounding box rendering
    void auxDraw(); // draws a basic coordinate system and bounding box

    // contains everything about the geometry of the fretboard
    // GuitarMeasure measures;  // not needed anymore

private:

    // coordinate system and boiunding box primitives
    ofPath ksX;
    ofPath ksY;
    ofPath ksZ;
};

#endif // GUITAR_H
