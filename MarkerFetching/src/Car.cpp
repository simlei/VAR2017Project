#include "Car.h"



//Out of 3D-MLExample

GLfloat lightOnePosition[] = {40.0, 40, 100.0, 0.0};
GLfloat lightOneColor[] = {0.99, 0.99, 0.99, 1.0};

GLfloat lightTwoPosition[] = {-40.0, 40, 100.0, 0.0};
GLfloat lightTwoColor[] = {0.99, 0.99, 0.99, 1.0};


Car::Car(){
}

void Car::setup(){
    material.setDiffuseColor(ofFloatColor::green);

    /*
    // This is how we append the 2 headlamps to the car.
    // Calling setParent, we are telling to the lights that they are
    // a child of the object car, and that teir movement are relative to
    // the movement of the car

    lightL.setParent(geometry);
    lightR.setParent(geometry);
    
    lightL.move(-45,20,-51);
    lightR.move(45,20,-51);
    lightL.tilt(-20);
    lightR.tilt(-20);
    lightL.setSpotlight();
    lightR.setSpotlight();
    lightL.setDiffuseColor(ofFloatColor::yellow);
    lightR.setDiffuseColor(ofFloatColor::yellow);
    lightL.setup();
    lightR.setup();
    */


    //Out of 3D-MLExample

    //some model / light stuff
    //ofEnableDepthTest();
    glShadeModel (GL_SMOOTH);

    /* initialize lighting */
    glLightfv (GL_LIGHT0, GL_POSITION, lightOnePosition);
    glLightfv (GL_LIGHT0, GL_DIFFUSE, lightOneColor);
    glEnable (GL_LIGHT0);
    glLightfv (GL_LIGHT1, GL_POSITION, lightTwoPosition);
    glLightfv (GL_LIGHT1, GL_DIFFUSE, lightTwoColor);
    glEnable (GL_LIGHT1);
    glEnable (GL_LIGHTING);
    glColorMaterial (GL_FRONT_AND_BACK, GL_DIFFUSE);
    glEnable (GL_COLOR_MATERIAL);

    //load the squirrel model - the 3ds and the texture file need to be in the same folder
    squirrelModel.loadModel("arrow.3ds", 20);

    //you can create as many rotations as you want
    //choose which axis you want it to effect
    //you can update these rotations later on
    //squirrelModel.setRotation(0, 90, 1, 0, 0);
    //squirrelModel.setRotation(1, 270, 0, 0, 1);
    squirrelModel.setScale(0.9, 0.9, 0.9);
    //squirrelModel.setPosition(ofGetWidth()/2, ofGetHeight()/2, 0);

}

void Car::draw(){

    //material.begin();
    geometry.draw();
    //material.end();

    ofDrawBox(0.2);
    //lightR.draw();
    //lightL.draw();

    squirrelModel.drawFaces();
}

void Car::update(){
    /*vel += acceleration;
    vel *= 0.9;
    acceleration *= 0.99;
    // here we are defining the vector that contains the direction
    // in which the car should move, that is defined by the z-axis of the car and the velocity
    auto velVector = geometry.getZAxis() * -vel;
    geometry.move(velVector);*/
}

/*
void Car::brake(){
    acceleration -= 0.1;
}

void Car::accellerate(){
    acceleration += 0.1;
}

void Car::steer(float dir){
    geometry.rotate(dir, 0, 1, 0); // the rotation happens on the y axis
}
*/
