#include "guitaroverlay.h"
#include "guitar.h"

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

    for(int stringIdx = 0; stringIdx<GuitarMeasure::MAX_STRING; stringIdx++) {
        for(int fretIdx = 0; fretIdx<12; fretIdx++) {
            bool doit = state.getStringState(stringIdx, fretIdx);

            //guitar.measures.getStringPos(stringIdx, fretIdx);
            if(doit) {
                ofColor color = getColorFor(stringIdx, fretIdx);
                ofVec3f offset(0.05f * ((float) stringIdx), 0.f, 0.1f * ((float) fretIdx));
                arrow.draw(offset, 0, color);
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
