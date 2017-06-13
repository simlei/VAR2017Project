#include "Car.h"


//Out of 3D-MLExample

GLfloat lightOnePosition[] = {40.0, 40, 100.0, 0.0};
GLfloat lightOneColor[] = {0.2, 0.2, 0.2, 1.0};

GLfloat lightTwoPosition[] = {-40.0, 40, 100.0, 0.0};
GLfloat lightTwoColor[] = {0.6, 0.6, 0.6, 1.0};


Car::Car(){
}

void Car::setup(){
    material.setDiffuseColor(ofFloatColor::green);
    glShadeModel (GL_SMOOTH);
    glLightfv (GL_LIGHT0, GL_POSITION, lightOnePosition);
    glLightfv (GL_LIGHT0, GL_DIFFUSE, lightOneColor);
    glEnable (GL_LIGHT0);
    glLightfv (GL_LIGHT1, GL_POSITION, lightTwoPosition);
    glLightfv (GL_LIGHT1, GL_DIFFUSE, lightTwoColor);
    glEnable (GL_LIGHT1);
    glEnable (GL_LIGHTING);
    glColorMaterial (GL_FRONT_AND_BACK, GL_DIFFUSE);
    glEnable (GL_COLOR_MATERIAL);
    squirrelModel.loadModel("arrow.3ds", 20);
    squirrelModel.setScale(0.0001* 2.0, 0.0001* 2.0, 0.0001* 2.0);

    box.set(0.04f);
}

void Car::setBoxColor(ofColor& color) {
    for(int i=0; i<6; i++) {
        box.setSideColor(i, color);
    }
}

void Car::draw(ofVec3f& offset, int primitive, ofColor& color){
    ofPushMatrix();

    ofTranslate(offset);

    if(primitive == 0) {
        squirrelModel.drawFaces();
    } else if(primitive == 1) {
        setBoxColor(color);
        box.draw();
    }

    ofPopMatrix();
}

void Car::update(){
}
