#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

class Car{
public:
    Car();
    void setup();
    void draw();
    void update();
    /*
    void brake();
    void accellerate();
    void steer(float dir);
    */
    
private:
    float acceleration;
    float vel;
    ofBoxPrimitive geometry;
    ofMaterial material;
    ofLight lightR, lightL;

    //Out of 3D-MLExample
    ofxAssimpModelLoader squirrelModel;
};
