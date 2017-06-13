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

    Guitar guitar;
    Car arrow;
    ofBoxPrimitive box;
private:



};

#endif // GUITAROVERLAY_H
