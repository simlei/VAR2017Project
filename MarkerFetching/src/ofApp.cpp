#include "ofApp.h"
#include "../../../../addons/ofxCv/src/ofxCv.h"
#include "ofBitmapFont.h"
//#include "guitarmeasure.h"


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




    //ofLog() << "TEst1: " << testMeasure.getStringPos(1, 3);

	ofSetVerticalSync(true);
    useVideo = false;
	string boardName = "boardConfiguration.yml";

	if(useVideo){
		player.load("videoboard.mp4");
		player.play();
		video = &player;
	}else{
        grabber.listDevices();
        grabber.setDeviceID(0);
        grabber.initGrabber(CAM_WIDTH,CAM_HEIGHT);
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

    renderer.setup();
    overlay.setup();



    //overlay.setNote(4);
    overlay.setChord(GuitarOverlay::Chord{4, GuitarOverlay::MAYOR});
    //overlay.resetState();


}

//--------------------------------------------------------------
void ofApp::update(){

    songPlayer.update();
    video->update();
	if(video->isFrameNew()){

        mirroredPixels = video->getPixels();
        mirroredPixels.mirror(0,1);

        aruco.detectBoards(mirroredPixels);
        //aruco.detectBoards(video->getPixels());
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
    renderer.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255);
    //video->draw(0,0);
    video->draw(CAM_WIDTH,0,-CAM_WIDTH, CAM_HEIGHT);

	//aruco.draw();


    vector<aruco::Marker> markers = aruco.getMarkers();

	if(showMarkers){
		for(int i=0;i<aruco.getNumMarkers();i++){
			aruco.begin(i);
            drawMarker(0.15,ofColor::white);
            aruco::Marker currentMarker = markers[i];
           if((currentMarker.idMarker == 89)){ //Was marker 404 but mirroring it results in marker 89
//               noteRenderer.draw();
               overlay.customDraw();
               /*
                float offset = 0.1f;
                noteRenderer.draw();
                noteRenderer.draw(offset,offset);
                noteRenderer.draw(-offset, offset);
                noteRenderer.draw(offset, -offset);
                noteRenderer.draw(-offset, -offset);*/
            }


            //if(true){noteRenderer.draw();} //i == 0 //Should look for id 404 oor 505

            // Loading the 3d-model messxes with the color
            ofSetColor(255);
			aruco.end();
		}
	}


	if(showBoard && aruco.getBoardProbability()>0.03){
		for(int i=0;i<aruco.getNumBoards();i++){
			aruco.beginBoard(i);
            drawMarker(.5,ofColor::red);
			aruco.end();
		}
	}


	ofSetColor(255);
	if(showBoardImage){
        board.draw(ofGetWidth()-320,0,320,320*float(board.getHeight())/float(board.getWidth()));
    }
	ofDrawBitmapString("markers detected: " + ofToString(aruco.getNumMarkers()),20,20);
    ofDrawBitmapString("fps " + ofToString(ofGetFrameRate()),20,40);
    ofDrawBitmapString("RunningTime: " + ofToString(songPlayer.runningTime),20,60);
    /*
	ofDrawBitmapString("m toggles markers",20,60);
	ofDrawBitmapString("b toggles board",20,80);
	ofDrawBitmapString("i toggles board image",20,100);
	ofDrawBitmapString("s saves board image",20,120);
	ofDrawBitmapString("0-9 saves marker image",20,140);
    */

    //Out of ofNodeExample

    /*
    if(aruco.getNumMarkers() > 0){
        aruco.begin(0);
            noteRenderer.draw();
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
