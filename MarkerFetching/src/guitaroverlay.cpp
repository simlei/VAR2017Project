#include "guitaroverlay.h"
#include "vector"
#include <cmath>


float xCallibration = -0.125f; // needs to be negativ if mirrored
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
    lastChord = Chord {0, MAYOR};
    currentChord = Chord {0, MAYOR};
    nextChord = Chord {0, MAYOR};

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

ofColor GuitarOverlay::getColorFor(int stringIdx, int fretIdx, int baseTone) {

    int halftone = getHalftoneFor(stringIdx, fretIdx);
    halftone -= baseTone
;    if(halftone == 0) { //I
        return ofColor::red;
    }
    if(halftone == 2) { //II
        return ofColor::orange;
    }
    if(halftone == 4) { //III
        return ofColor::yellow;
    }
    if(halftone == 5) { //IV
        return ofColor::green;
    }
    if(halftone == 7) { //V
        return ofColor::blue;
    }
    if(halftone == 9) { //VI
        return ofColor::purple;
    }
    if(halftone == 11) { //VII
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
    launchTime = ofGetElapsedTimef();
}

void GuitarOverlay::customDraw(){

    float zLength = 1.10f;
    float xHeight = -0.09f; // needs to be negativ if mirrored
    ofVec3f offset;
    ofColor color;
    for(int stringIdx = 0; stringIdx<Guitar::MAX_STRING; stringIdx++) {
        for(int fretIdx = 0; fretIdx<12; fretIdx++) {
            bool doit = state.getStringState(stringIdx, fretIdx);
            //doit = true;
            if(doit) {
                color = getColorFor(stringIdx, fretIdx, currentChord.baseTone);
                offset = calculateOffset(stringIdx, fretIdx);
                renderer.draw(offset, 1, color);
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

    ofVec3f resultVec;
    if(fretIdx == 0){
        resultVec = ofVec3f(
                    xCallibration+(-xHeight*stringIdx/6.f),// needs to be negativ if mirrored
                    0.f,
                    zCallibration-0.015f
                    );
    }else{
        resultVec = ofVec3f(
                    xCallibration+(-xHeight*stringIdx/6.f),// needs to be negativ if mirrored
                    0.f,
                    zCallibration+ zLength*(1-(((float)pow((1-(1/17.817f)), (fretIdx-1)) + (float)pow((1-(1/17.817f)), (fretIdx)))/2.f))
                    );
   }
    return resultVec;
}

void GuitarOverlay::setNote(int halfTone, int startFret, int fretInterval){
    int stringPos;
    int fretPos;
    for(int i=0; i<scale.at(halfTone).size(); i++) {
        stringPos = scale.at(halfTone).at(i).at(0);
        fretPos = scale.at(halfTone).at(i).at(1);
        if(fretPos== 0 || (fretPos >= startFret && fretPos < (startFret+fretInterval))){
            state.set(stringPos,fretPos,true);
        }
    }
}

void GuitarOverlay::setChord(Chord displayedChord, int startFret){
    lastChord = currentChord;
    currentChord = displayedChord;
    int interval = 5;
    //Tonic
    setNote(displayedChord.baseTone, startFret, interval);
    if((displayedChord.type == MAYOR) || (displayedChord.type == MAYOR7)){
        //Major Third
        setNote((displayedChord.baseTone+4)%12, startFret, interval);
    }else if(displayedChord.type == MINOR){
        //Minor Third
        setNote((displayedChord.baseTone+3)%12, startFret, interval);
    }
    //Fifth
    setNote((displayedChord.baseTone+7)%12, startFret, interval);
}


void GuitarOverlay::resetState(){
    for(int i=0; i<Guitar::MAX_STRING; i++) {
        state.stateBoard.at(i) = std::vector<bool>(Guitar::MAX_FRET);
        for(int fret = 0; fret<Guitar::MAX_FRET; fret++) {
            state.stateBoard.at(i).at(fret) = false;
        }
    }
}
