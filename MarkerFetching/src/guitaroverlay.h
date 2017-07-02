#ifndef GUITAROVERLAY_H
#define GUITAROVERLAY_H

#include "ofMain.h"
#include "guitar.h"
#include "guitarstringstate.h"


class GuitarOverlay: public ofNode
{
public:
    GuitarOverlay(Guitar& pGuitar);

    void cameraTestOutputStuff();

    void setup();
    void customDraw();
    void update();

    int getHalftoneFor(int stringIdx, int fretIdx);
    ofColor getColorFor(int stringIdx, int fretIdx);

    GuitarStringState state;
    void setGuitar(Guitar &guitar);
    Guitar getGuitar();
    ofVec3f calculateOffset(int stringIdx, int fretIdx);


    //Contains a vector containing the positions of occurrence (on the fretboard) for each halfstep-note
    //  The String will be written first like so:
    //  { [string,fret] | [string,fret] | [string,fret] }
    std::vector<std::vector<std::vector<int>>> scale = std::vector<std::vector<std::vector<int>>>(12);

    Guitar guitar;
    noteRenderer renderer;
    ofBoxPrimitive box;
private:



};

#endif // GUITAROVERLAY_H
