#include "guitar.h"



Guitar::Guitar(GuitarMeasure& m):
    measures(m)
{

    float ksL = 40;
    float ksW = 3;

    ksX.moveTo(0, 0, 0);
    ksX.lineTo(ksL, 0, 0);
    ksX.setStrokeColor(ofColor::red);
    ksX.setStrokeWidth(ksW);

    ksY.moveTo(0, 0, 0);
    ksY.lineTo(0, ksL, 0);
    ksY.setStrokeColor(ofColor::green);
    ksY.setStrokeWidth(ksW);

    ksZ.lineTo(0, 0, ksL);
    ksZ.setStrokeColor(ofColor::blue);
    ksZ.setStrokeWidth(ksW);



}

Guitar::~Guitar() {

}



void Guitar::setup(){

}

void Guitar::drawdraw() {
    ofDrawAxis(1.0f);
}

void Guitar::customDraw() {
    //auxDraw();
}

void Guitar::auxDraw() {
    ksX.draw();
    ksY.draw();
    ksZ.draw();
    measures.getBB().draw();
}
