#ifndef GUITARMEASURE_H
#define GUITARMEASURE_H

#include "ofMain.h"

class GuitarMeasure
{
public:

    static const int MAX_STRING = 6;
    static const int MAX_FRET = 30;

    std::vector<float> fretRatios;

    static void check_access(int stringIdx, int fretIdx) { // centralized checking if fret pos is valid
        if(stringIdx < 0 || stringIdx >= MAX_STRING || fretIdx < 0 || fretIdx >= MAX_FRET) {
            ofLogError("Guitar.cpp") << "string or fret index out of range!";
            ofExit(1);
        }
    }

    // provide geometry of the fretboard relative to the local
    // coordinate system of your choosing (e. g. where you put your Aruco marker)
    GuitarMeasure(
            const ofVec3f &posLowerNeck,
            const ofVec3f &posLowerBridge,
            const ofVec3f &posHigherNeck,
            const ofVec3f &posHigherBridge
            );

    std::vector<std::vector<ofVec3f>> stringPos; // public for easy batch access

    // lowest (thickest) string == 0
    // lowest fret == neck pos == 0
    ofVec3f getStringPos(int stringIdx, int fretIdx);

    ofPath getBB();

private:
    ofVec3f posLowerNeck; // lower (== thicker) string, mostly this one is the uppermost though, geometrically speaking.
    ofVec3f posLowerBridge;
    ofVec3f posHigherNeck; // higher (== thinner) string, mostly this one is the one at the bottom though, geometrically speaking.
    ofVec3f posHigherBridge;

    ofPath fretBoundingBox;

};

#endif // GUITARMEASURE_H
