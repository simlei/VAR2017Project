#ifndef GUITAROVERLAY_H
#define GUITAROVERLAY_H

#include "ofMain.h"
#include "guitar.h"
#include "guitarstringstate.h"
#include "guitar.h"


class GuitarOverlay: public ofNode
{
public:
    GuitarOverlay(Guitar& pGuitar);


    enum chordType {MAYOR, MINOR, MAYOR7};

    struct Chord{
        int baseTone;
        chordType type; //Kind of chord.

    };

    void cameraTestOutputStuff();

    void setup();
    void customDraw();
    void update();

    int getHalftoneFor(int stringIdx, int fretIdx);
    ofColor getColorFor(int stringIdx, int fretIdx, int baseTone);
    Guitar getGuitar();
    ofVec3f calculateOffset(int stringIdx, int fretIdx);

    void setGuitar(Guitar &guitar);
    void setNote(int halfTone);
    void setChord(Chord displayedChord);
    void resetState();


    //Contains a vector containing the positions of occurrence (on the fretboard) for each halfstep-note
    //  The String will be written first like so:
    //  { [string,fret] | [string,fret] | [string,fret] }
    std::vector<std::vector<std::vector<int>>> scale = std::vector<std::vector<std::vector<int>>>(12);

    GuitarStringState state;

private:
    Guitar guitar;
    noteRenderer renderer;
    ofBoxPrimitive box;
    float launchTime;
    Chord lastChord;
    Chord currentChord;
    Chord nextChord;
};

#endif // GUITAROVERLAY_H
