#include "guitarmeasure.h"

GuitarMeasure::GuitarMeasure(
        const ofVec3f &p1,
        const ofVec3f &p2,
        const ofVec3f &p3,
        const ofVec3f &p4
        )
{
    posLowerNeck = p1;
    posLowerBridge = p2;
    posHigherNeck = p3;
    posHigherBridge = p4;

    fretRatios = {0.000f,    //0th fret == bridge
                 0.056f,    //1st fret: ratio to full string length
                 0.109f,    //2nd fret: ratio to full string length
                 0.159f,    //...
                 0.206f,
                 0.251f ,0.293f ,0.333f ,0.370f,
                 0.405f ,0.439f ,0.470f ,0.500f,
                 0.528f ,0.555f ,0.580f ,0.603f,
                 0.646f ,0.666f ,0.685f ,0.703f,
                 0.719f ,0.735f ,0.750f ,0.764f,
                 0.777f ,0.790f ,0.802f ,0.813f};

    ofVec3f incNeck = (posHigherNeck - posLowerNeck) * 0.2f; // 1/5 because 5 increments (6 strings)
    ofVec3f incBridge = (posHigherBridge - posLowerBridge) * 0.2f;

    ofVec3f stringVecStart = posLowerNeck;
    ofVec3f stringVecEnd = posLowerBridge;

    stringPos = std::vector<std::vector<ofVec3f>>(MAX_STRING); //6 strings
    for(int stringIdx = 0; stringIdx < MAX_STRING; stringIdx++) {
        stringPos[stringIdx] = std::vector<ofVec3f>(MAX_FRET);
        ofVec3f stringVec = stringVecEnd - stringVecStart;

        for(int fret = 0; fret < MAX_FRET; fret++) {
            ofVec3f pos = stringVecStart + stringVec * fretRatios[fret];
            stringPos[stringIdx][fret] = pos;
        }

        stringVecStart = stringVecStart + incNeck; // increment to next guitar string
        stringVecEnd = stringVecEnd + incBridge;
    }

    fretBoundingBox.moveTo(posLowerBridge);
    fretBoundingBox.lineTo(posLowerNeck);
    fretBoundingBox.lineTo(posHigherNeck);
    fretBoundingBox.lineTo(posHigherBridge);
    fretBoundingBox.close();

}

ofPath GuitarMeasure::getBB() {
    return fretBoundingBox;
}

ofVec3f GuitarMeasure::getStringPos(int stringIdx, int fretIdx) {
    GuitarMeasure::check_access(stringIdx, fretIdx);

    return stringPos[stringIdx][fretIdx];
}
