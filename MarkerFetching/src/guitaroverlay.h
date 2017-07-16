#ifndef GUITAROVERLAY_H
#define GUITAROVERLAY_H

#include "ofMain.h"
#include "guitar.h"
#include "guitarstringstate.h"


class GuitarOverlay: public ofNode
{
public:
    GuitarOverlay(Guitar& pGuitar);


    enum chordType {MAYOR, MINOR, MAYOR7, EMPTY};

    struct Chord{
        int baseTone;
        chordType type; //Kind of chord.

    };

    void cameraTestOutputStuff();

    void setup();
    void customDraw();
    void drawChords();
    void update();


    int getHalftoneFor(int stringIdx, int fretIdx);
    ofColor getColorFor(int stringIdx, int fretIdx, int baseTone);
    Guitar getGuitar();
    ofVec3f calculateOffset(int stringIdx, int fretIdx);
    string toneToString(int tone);
    string chordToString(Chord chord);
    void setGuitar(Guitar &guitar);
    void setNote(int halfTone, int startFret, int fretInterval);
    void setChord(Chord displayedChord, int startFret=0);
    void resetChords();
    void resetState();


    //Contains a vector containing the positions of occurrence (on the fretboard) for each halfstep-note
    //  The String will be written first like so:
    //  { [string,fret] | [string,fret] | [string,fret] }
    std::vector<std::vector<std::vector<int>>> scale = std::vector<std::vector<std::vector<int>>>(12);
    GuitarStringState state;
    Chord nextChord;
    int mode;


private:

    ofTrueTypeFont mainChordFont;
    ofTrueTypeFont sideChordFont;
    Guitar guitar;
    noteRenderer renderer;
    ofBoxPrimitive box;
    float launchTime;
    Chord lastChord;
    Chord currentChord;
};

#endif // GUITAROVERLAY_H
