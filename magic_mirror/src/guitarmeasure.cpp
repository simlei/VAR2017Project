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

    std::vector<float> fretRatios(15);
    fretRatios[0] = 0.000; //0th fret == bridge
    fretRatios[1] = 0.056; //1st fret: ratio to full string length
    fretRatios[2] = 0.109; //2nd fret: ratio to full string length
    fretRatios[3] = 0.159; //...
    fretRatios[4] = 0.206;
    fretRatios[5] = 0.251;
    fretRatios[6] = 0.293;
    fretRatios[7] = 0.333;
    fretRatios[8] = 0.370;
    fretRatios[9] = 0.405;
    fretRatios[10] = 0.439;
    fretRatios[11] = 0.470;
    fretRatios[12] = 0.500;
    fretRatios[13] = 0.528;
    fretRatios[14] = 0.555;
    fretRatios[15] = 0.580;
    fretRatios[16] = 0.603;
    fretRatios[17] = 0.625;
    fretRatios[18] = 0.646;
    fretRatios[19] = 0.666;
    fretRatios[20] = 0.685;
    fretRatios[21] = 0.703;
    fretRatios[22] = 0.719;
    fretRatios[23] = 0.735;
    fretRatios[24] = 0.750;
    fretRatios[25] = 0.764;
    fretRatios[26] = 0.777;
    fretRatios[27] = 0.790;
    fretRatios[28] = 0.802;
    fretRatios[29] = 0.813;

    ofVec3f incNeck = (posHigherNeck - posLowerNeck) * 0.2f; // 1/5 because 5 increments (6 strings)
    ofVec3f incBridge = (posHigherBridge - posLowerBridge) * 0.2f;

    ofVec3f stringVecStart = posLowerNeck;
    ofVec3f stringVecEnd = posLowerBridge;

    stringPos = std::vector<std::vector<ofVec3f>>(6); //6 strings
    for(int stringIdx = 0; stringIdx < 6; stringIdx++) {
        stringPos[stringIdx] = std::vector<ofVec3f>(15);
        ofVec3f stringVec = stringVecEnd - stringVecStart;

        for(int fret = 0; fret < 15; fret++) {
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
