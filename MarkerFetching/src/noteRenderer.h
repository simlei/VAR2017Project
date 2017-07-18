#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

class noteRenderer{
public:
    noteRenderer();
    void setup();
    void setBoxColor(ofColor& color);
    void draw(ofVec3f& offset, int primitive, ofColor& color);

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
    ofBoxPrimitive box;
};
