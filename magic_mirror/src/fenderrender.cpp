#include "fenderrender.h"

static GuitarMeasure thisMeasure(
                ofVec3f(30, 4, 0),
                ofVec3f(-10, 6, 0),
                ofVec3f(30, -4, 0),
                ofVec3f(-10, -6, 0)
            );

FenderRender::FenderRender()
    : Guitar(thisMeasure)
{

}

void FenderRender::setup() {
    /* initialize lighting */
    GLfloat lightOnePosition[] = {40.0, 40, 100.0, 0.0}; // TODO: really necessary? arbitrary values...
    GLfloat lightOneColor[] = {0.99, 0.99, 0.99, 1.0};

    GLfloat lightTwoPosition[] = {-40.0, 40, 100.0, 0.0};
    GLfloat lightTwoColor[] = {0.99, 0.99, 0.99, 1.0};

//    ofBackground(220,220,220);
    ofSetVerticalSync(true);

    ofEnableDepthTest();
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

    guitarModel.loadModel("3ds/fender.3ds", 20);
//    guitarModel.setRotation(0, 0, 1, 0, 0);
//    guitarModel.setRotation(1, 180, 0, 0, 1);
    guitarModel.setScale(0.4, 0.4, 0.4); // also a parameter - scale to 100 units == 1 meter or something
    guitarModel.setPosition(0,0,0); // model offset is most likely a parameter; center this e.g. on aruco position if we have one
}

void FenderRender::customDraw() {
    auxDraw(); // turn this on for coordinate system and bounding box drawing
    guitarModel.drawFaces();
}
