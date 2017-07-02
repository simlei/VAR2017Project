#include "guitaroverlay.h"
#include "guitar.h"
#include <cmath>


float xCallibration = +0.125f;
float zCallibration = -0.645f;


GuitarOverlay::GuitarOverlay(Guitar& pGuitar):
    guitar(pGuitar)
{
    setGuitar(pGuitar);

    std::vector<int> tempVec;
    for(int stringIdx = 0; stringIdx<Guitar::MAX_STRING; stringIdx++) {
        for(int fretIdx = 0; fretIdx<Guitar::MAX_FRET; fretIdx++) {
            tempVec = {stringIdx, fretIdx};
            scale.at(GuitarOverlay::getHalftoneFor(stringIdx,fretIdx)).push_back(tempVec);
        }
    }

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
        stringHalftone = 14; //could be 2
    }
    if(stringIdx == 3) {
        stringHalftone = 19; //could be 7
    }
    if(stringIdx == 4) {
        stringHalftone = 23; //could be 11
    }
    if(stringIdx == 5) {
        stringHalftone = 28; //could be 4
    }

    return ((stringHalftone + fretIdx) % 12);
}

ofColor GuitarOverlay::getColorFor(int stringIdx, int fretIdx) {

    int halftone = getHalftoneFor(stringIdx, fretIdx);
    if(halftone == 0) { //C
        return ofColor::red;
    }
    if(halftone == 2) { //D
        return ofColor::orange;
    }
    if(halftone == 4) { //E
        return ofColor::yellow;
    }
    if(halftone == 5) { //F
        return ofColor::green;
    }
    if(halftone == 7) { //G
        return ofColor::blue;
    }
    if(halftone == 9) { //A
        return ofColor::purple;
    }
    if(halftone == 11) { //H
        return ofColor::beige;
    }
    return ofColor::black;

}

void GuitarOverlay::setup(){
    renderer.setup();
    box.set(0.2f);
    for(int i=0; i<6; i++) {
        box.setSideColor(i, ofColor::blue);
    }
}

void GuitarOverlay::customDraw(){

    float zLength = 1.10f;
    float xHeight = 0.09f;
    for(int stringIdx = 0; stringIdx<Guitar::MAX_STRING; stringIdx++) {
        for(int fretIdx = 0; fretIdx<12; fretIdx++) {
            bool doit = state.getStringState(stringIdx, fretIdx);
            //doit = true;
            if(doit) {
                ofColor color = getColorFor(stringIdx, fretIdx);
                ofVec3f offset;
                offset = calculateOffset(stringIdx, fretIdx);
                renderer.draw(offset, 1, color);
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

ofVec3f GuitarOverlay::calculateOffset(int stringIdx, int fretIdx){
    float zLength = 1.10f; //should be read out of the 4 fretpos //TODO
    float xHeight = 0.09f; //should be read out of the 4 fretpos //TODO

    return ofVec3f(
                xCallibration+(xHeight*stringIdx/6.f),
                0.f,
                zCallibration+ zLength*(1-(((float)pow((1-(1/17.817f)), fretIdx) + (float)pow((1-(1/17.817f)), fretIdx+1))/2.f)));
}
