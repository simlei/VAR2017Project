#include "ofApp.h"
#include "ofxCv.h"
#include "ofBitmapFont.h"


void drawMarker(float size, const ofColor & color){
	ofDrawAxis(size);
	ofPushMatrix();
		// move up from the center by size*.5
		// to draw a box centered at that point
		ofTranslate(0,size*0.5,0);
		ofFill();
		ofSetColor(color,50);
		ofDrawBox(size);
		ofNoFill();
		ofSetColor(color);
		ofDrawBox(size);
	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
    useVideo = false;
	string boardName = "boardConfiguration.yml";

	if(useVideo){
		player.load("videoboard.mp4");
		player.play();
		video = &player;
	}else{
        grabber.listDevices();
        grabber.setDeviceID(1);
        //grabber.initGrabber(320,240);
        grabber.initGrabber(640,480);
        //grabber.initGrabber(1920,1080);
		video = &grabber;
	}

	//aruco.setThreaded(false);
	aruco.setup("intrinsics.int", video->getWidth(), video->getHeight(), boardName);
	aruco.getBoardImage(board.getPixels());
	board.update();

	showMarkers = true;
	showBoard = true;
	showBoardImage = false;

    ofEnableAlphaBlending();

    //Out of ofNodeExample

    //light.setup();
    //light.setPosition(-100, 200,0);
    car.setup();

}

//--------------------------------------------------------------
void ofApp::update(){
	video->update();
	if(video->isFrameNew()){
        aruco.detectBoards(video->getPixels());
        // std::cout << aruco.getNumMarkers() << endl;
        /*
        if(aruco.getNumMarkers() > 0){
            double position [3];
            double orientation [4];
            aruco.getMarkers()[0].OgreGetPoseParameters(position, orientation);
            std::cout << position[0] << ", " << position[1] << ", " << position[2] << std::endl;
        }
        */
	}

    //Out of ofNodeExample
    car.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255);
	video->draw(0,0);

	//aruco.draw();


    vector<aruco::Marker> markers = aruco.getMarkers();

	if(showMarkers){
		for(int i=0;i<aruco.getNumMarkers();i++){
			aruco.begin(i);
            //drawMarker(0.15,ofColor::white);

            aruco::Marker currentMarker = markers[i];
           if((currentMarker.idMarker == 404) || (currentMarker.idMarker == 505)){
                float offset = 0.1f;
                car.draw();
                car.draw(offset,offset);
                car.draw(-offset, offset);
                car.draw(offset, -offset);
                car.draw(-offset, -offset);
            }


            //if(true){car.draw();} //i == 0 //Should look for id 404 oor 505

            // Loading the 3d-model messxes with the color
            ofSetColor(255);
			aruco.end();
		}
	}


	if(showBoard && aruco.getBoardProbability()>0.03){
		for(int i=0;i<aruco.getNumBoards();i++){
			aruco.beginBoard(i);
            //drawMarker(.5,ofColor::red);
			aruco.end();
		}
	}


	ofSetColor(255);
	if(showBoardImage){
		board.draw(ofGetWidth()-320,0,320,320*float(board.getHeight())/float(board.getWidth()));
	}
	ofDrawBitmapString("markers detected: " + ofToString(aruco.getNumMarkers()),20,20);
	ofDrawBitmapString("fps " + ofToString(ofGetFrameRate()),20,40);
	ofDrawBitmapString("m toggles markers",20,60);
	ofDrawBitmapString("b toggles board",20,80);
	ofDrawBitmapString("i toggles board image",20,100);
	ofDrawBitmapString("s saves board image",20,120);
	ofDrawBitmapString("0-9 saves marker image",20,140);

    //Out of ofNodeExample

    /*
    if(aruco.getNumMarkers() > 0){
        aruco.begin(0);
            car.draw();
        aruco.end();
    }*/



}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(key=='m') showMarkers = !showMarkers;
	if(key=='b') showBoard = !showBoard;
	if(key=='i') showBoardImage = !showBoardImage;
	if(key=='s') board.save("boardimage.png");
	if(key>='0' && key<='9'){
		// there's 1024 different markers
		int markerID = key - '0';
		aruco.getMarkerImage(markerID,240,marker);
		marker.save("marker"+ofToString(markerID)+".png");
	}
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

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
