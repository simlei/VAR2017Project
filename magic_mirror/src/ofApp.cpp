#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::cameraTestOutputStuff() {
    ofPoint nearplaneTopLeft = camera.screenToWorld(ofPoint(0,0));
    ofPoint nearplaneMid = camera.screenToWorld(ofPoint(((float)ofGetWidth()/2), ((float)ofGetHeight()/2)));
    ofPoint nearplaneBottomRight = camera.screenToWorld(ofPoint(ofGetWidth(), ofGetHeight()));

    ofVec3f ui_xaxis = ofVec3f(nearplaneBottomRight.x - nearplaneTopLeft.x, 0, 0);
    ofVec3f ui_yaxis = ofVec3f(0, nearplaneBottomRight.y - nearplaneTopLeft.y, 0);
    ofVec3f ui_zaxis = ofVec3f(0, nearplaneBottomRight.z - nearplaneTopLeft.z, 0);
    ofVec3f uiMid(nearplaneMid);
    float near_z = nearplaneMid.z;

    ofLog() << "camera  : " << camera.getPosition();
    ofLog() << "cam-near: " << camera.getNearClip();
    ofLog() << "cam-look: " << camera.getLookAtDir();

    ofLog() << "topleft : " << nearplaneTopLeft;
    ofLog() << "botright: " << nearplaneBottomRight;

    ofLog() << "near_width : " << ui_xaxis.length();
    ofLog() << "near_height: " << ui_yaxis.length();
    ofLog() << "near_z: " << near_z;
}

void ofApp::setup(){

//----Maybe this camera setup code is still useful
//    float fov = 60; // camera parameter
//    float nearPlaneDist = 20;  // 20cm, arbitrary, can be changed
//    float farPlaneDist = 1000; // 10 m, arbitrary, can be changed
//    camera.setupPerspective(false, fov, nearPlaneDist, farPlaneDist, ofVec2f(0.0, 0.0));
//    camera.setPosition(ofVec3f(0.0, 0.0, 0.0));
//    camera.lookAt(ofVec3f(0.0, 0.0, -1.0));

    camera.setupPerspective(); //TODO: default calibration; must be calibrated in accordance with Aruco
    cameraTestOutputStuff();

//    gui.setup();
//    gui.add(radius.setup("radius", 140, 10, 3000));

    fender = FenderRender(); //  was already constructed, but just to make it clear, much happens in the constructor.
                             //  this object is of type "Guitar" and assigns itself its own measurememnts.
    fender.setup();

}


//--------------------------------------------------------------
void ofApp::update(){

    // here the aruco magic should be received.
    // let's say we got position and orientation of the guitar as xyz, quat:

    ofVec3f posOfGuitarLocalKSZeroPoint = ofVec3f(0, 0, 0);
    ofQuaternion orientationOfGuitarLocalKS = ofQuaternion(0, ofVec3f(0, 0, 1)); // rotated zero degrees by z axis

    fender.setPosition(posOfGuitarLocalKSZeroPoint);
    fender.setOrientation(orientationOfGuitarLocalKS);
}

//--------------------------------------------------------------
void ofApp::draw(){

//    //wall
//    ofSetColor(30, 200, 30);
//    glBegin(GL_QUADS);
//        glVertex3f(0.0, ofGetHeight(), 0);
//        glVertex3f(ofGetWidth(), ofGetHeight(), 0);
//        glVertex3f(ofGetWidth(), ofGetHeight(), -600);
//        glVertex3f(0, ofGetHeight(), -600);
//    glEnd();


    ofSetHexColor(0xFF0000);
    ofDrawBitmapString("fps: "+ofToString(ofGetFrameRate(), 2), 10, 15);

    fender.draw();  // because fender is inheriting from Guitar and thus from ofNode,
                    // we can just position it this way and all attached things move with it



////      gui-related
//    ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, radius);
//    gui.draw();
}



//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

    ofLog() << "Hi!";

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
