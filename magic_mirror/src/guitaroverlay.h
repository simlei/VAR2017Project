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

    GuitarStringState state;
    void setGuitar(Guitar &guitar);
    Guitar getGuitar();

    Guitar guitar;
private:



};

#endif // GUITAROVERLAY_H
