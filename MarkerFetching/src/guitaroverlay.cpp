#include "guitaroverlay.h"
#include "guitar.h"
#include <cmath>


float xCallibration = +0.125f;
float zCallibration = -0.645f;


GuitarOverlay::GuitarOverlay(Guitar& pGuitar):
    guitar(pGuitar)
{
    setGuitar(pGuitar);

}

int GuitarOverlay::getHalftoneFor(int stringIdx, int fretIdx) {
    int stringHalftone = 0; // 0 == C
    if(stringIdx == 0) {
        stringHalftone = 4;
    }
    if(stringIdx == 1) {
        stringHalftone = 9;
    }
    if(stringIdx == 2) {
        stringHalftone = 14;
    }
    if(stringIdx == 3) {
        stringHalftone = 19;
    }
    if(stringIdx == 4) {
        stringHalftone = 23;
    }
    if(stringIdx == 5) {
        stringHalftone = 28;
    }

    return (stringHalftone + fretIdx);
}

ofColor GuitarOverlay::getColorFor(int stringIdx, int fretIdx) {

    int halftone = getHalftoneFor(stringIdx, fretIdx) % 12;
    if(halftone == 0) {
        return ofColor::red;
    }
    if(halftone == 2) {
        return ofColor::orange;
    }
    if(halftone == 4) {
        return ofColor::yellow;
    }
    if(halftone == 5) {
        return ofColor::green;
    }
    if(halftone == 7) {
        return ofColor::blue;
    }
    if(halftone == 9) {
        return ofColor::purple;
    }
    if(halftone == 11) {
        return ofColor::beige;
    }
    return ofColor::black;

}

void GuitarOverlay::setup(){
    arrow.setup();
    box.set(0.2f);
    for(int i=0; i<6; i++) {
        box.setSideColor(i, ofColor::blue);
    }
}

void GuitarOverlay::customDraw(){

    float zLength = 1.10f;
    float xHeight = 0.09f;
    for(int stringIdx = 0; stringIdx<GuitarMeasure::MAX_STRING; stringIdx++) {
        for(int fretIdx = 0; fretIdx<12; fretIdx++) {
            bool doit = state.getStringState(stringIdx, fretIdx);
            //guitar.measures.getStringPos(stringIdx, fretIdx);
            //doit = true;
            if(doit ) {
                ofColor color = getColorFor(stringIdx, fretIdx);
                //ofVec3f offset(0.05f * ((float) stringIdx), 0.f, 0.1f * ((float) fretIdx));
                ofVec3f offset(
                            xCallibration+(xHeight*stringIdx/6.f),
                            0.f,
                            zCallibration+ zLength*(1-(((float)pow((1-(1/17.817f)), fretIdx) + (float)pow((1-(1/17.817f)), fretIdx+1))/2.f)));
                arrow.draw(offset, 1, color);
            }
        }
    }

}

void GuitarOverlay::update(){

}

Guitar GuitarOverlay::getGuitar() {
    return guitar;
}

void GuitarOverlay::setGuitar(Guitar &pGuitar) {
    guitar = pGuitar;
    setParent(guitar);
}
