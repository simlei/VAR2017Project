#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

class Car{
public:
    Car();
    void setup();
    void draw(float xOffset = 0.f, float zOffset = 0.f);
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
    //ofLight lightR, lightL;

    //Out of 3D-MLExample
    ofxAssimpModelLoader squirrelModel;
};
