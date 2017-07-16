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
    lastChord = Chord {0, EMPTY};
    currentChord = Chord {0, EMPTY};
    nextChord = Chord {0, EMPTY};
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


    //std::cout << "BaseTone for Colour: " << baseTone << std::endl;
    int halftone = getHalftoneFor(stringIdx, fretIdx);
    halftone = (halftone + 12 - baseTone) % 12;
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
    //std::cout << "Did return black for: " << halftone << std::endl;

    return ofColor::black;
}

void GuitarOverlay::setup(){
    renderer.setup();
    /*
    box.set(0.2f);
    for(int i=0; i<6; i++) {
        box.setSideColor(i, ofColor::blue);
    }
    */
    launchTime = ofGetElapsedTimef();


    mainChordFont.load("ASongForJennifer.tff",30);
    sideChordFont.load("ASongForJennifer.tff",15);
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

void GuitarOverlay::drawChords(int state){
    ofSetColor(255,255,255);
    if(state == 1){
        mainChordFont.drawString(chordToString(currentChord),(640/2)-(mainChordFont.stringWidth(chordToString(currentChord))/2), 20 + mainChordFont.stringHeight(chordToString(currentChord))); //Should be connected to CAM_WIDTH
        if(&lastChord != NULL){
            sideChordFont.drawString(chordToString(lastChord),(640/2)-mainChordFont.getSize()-55, 10 + mainChordFont.getSize()); //Should be connected to CAM_WIDTH
        }
        if(&nextChord != NULL){
            sideChordFont.drawString(chordToString(nextChord),(640/2)+mainChordFont.getSize()+45, 10 + mainChordFont.getSize()); //Should be connected to CAM_WIDTH
        }
    }
    else if(state == 2){
        mainChordFont.drawString(chordToString(currentChord),(640/2)-(mainChordFont.stringWidth(chordToString(currentChord))/2), 20 + 120 + mainChordFont.stringHeight(chordToString(currentChord))); //Should be connected to CAM_WIDTH
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
    if(displayedChord.type != chordType::EMPTY){
        lastChord = currentChord;
        currentChord = displayedChord;
        int interval = 5;
        resetState();
        //Tonic
        setNote(displayedChord.baseTone, startFret, interval);
        //std::cout << "Tonic: " << displayedChord.baseTone << std::endl;
        if((displayedChord.type == MAYOR) || (displayedChord.type == MAYOR7)){
            //Major Third
            setNote((displayedChord.baseTone+4)%12, startFret, interval);
            //std::cout << "MayorT: " << (displayedChord.baseTone+4)%12 << std::endl;
        }else if(displayedChord.type == MINOR){
            //Minor Third
            setNote((displayedChord.baseTone+3)%12, startFret, interval);
            //std::cout << "MinorT: " << (displayedChord.baseTone+3)%12 << std::endl;
        }
        //Fifth
        setNote((displayedChord.baseTone+7)%12, startFret, interval);
        //std::cout << "Fifth: " << (displayedChord.baseTone+7)%12 << std::endl;
        if(displayedChord.type == MAYOR7){
            //Seventh
            setNote((displayedChord.baseTone+10)%12, startFret, interval);
            //std::cout << "Seventh: " << (displayedChord.baseTone+10)%12 << std::endl;
        }
    }
}


void GuitarOverlay::resetState(){
    for(int i=0; i<Guitar::MAX_STRING; i++) {
        state.stateBoard.at(i) = std::vector<bool>(Guitar::MAX_FRET);
        for(int fret = 0; fret<Guitar::MAX_FRET; fret++) {
            state.stateBoard.at(i).at(fret) = false;
        }
    }
}


string GuitarOverlay::toneToString(int tone){
    string resultString = "";
    if(tone%12 == 0) resultString = "C";
    else if(tone%12 == 1) resultString = "C#";
    else if(tone%12 == 2) resultString = "D";
    else if(tone%12 == 3) resultString = "D#";
    else if(tone%12 == 4) resultString = "E";
    else if(tone%12 == 5) resultString = "F";
    else if(tone%12 == 6) resultString = "F#";
    else if(tone%12 == 7) resultString = "G";
    else if(tone%12 == 8) resultString = "G#";
    else if(tone%12 == 9) resultString = "A";
    else if(tone%12 == 10) resultString = "A#";
    else if(tone%12 == 11) resultString = "B";
    return resultString;
}

string GuitarOverlay::chordToString(Chord chord){
    string resultString = "";
    resultString.append(toneToString(chord.baseTone));
    if(chord.type == chordType::MINOR) resultString.append("m");
    if(chord.type == chordType::MAYOR7) resultString.append("7");
    return resultString;
}
