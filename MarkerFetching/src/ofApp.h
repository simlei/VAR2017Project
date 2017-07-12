#pragma once

#include "ofMain.h"
#include "ofxAruco.h"
#include "noteRenderer.h"
//#include "guitarmeasure.h"
#include "guitar.h"
#include "guitaroverlay.h"
#include "songplayer.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
        ofVideoGrabber grabber;
        const static int CAM_WIDTH = 640; //Developed with 640
        const static int CAM_HEIGHT = 480; //Developed with 480
        ofVideoPlayer player;
		ofBaseVideoDraws * video;
        ofPixels mirroredPixels;

		bool useVideo;
		bool showMarkers;
		bool showBoard;
		bool showBoardImage;
        float runningTime;
        ofxAruco aruco;
		ofImage board;
		ofImage marker;

        ofVec3f posLN = ofVec3f(0.0f, 0.0f, 0.0f);
        ofVec3f posLB = ofVec3f(-0.2f, 0, 0);
        ofVec3f posHN = ofVec3f(0, 0, 0.1f);
        ofVec3f posHB = ofVec3f(0.2f, 0, 0.1f);



        //GuitarMeasure testMeasure = GuitarMeasure(posLN, posLB, posHN, posHB);
        Guitar guitar = Guitar(posLN, posLB, posHN, posHB);
        GuitarOverlay overlay = GuitarOverlay(guitar);
        SongPlayer songPlayer = SongPlayer(60.f);

        //Out of ofNodeExample
        //ofLight light;
        //ofEasyCam cam;
        noteRenderer renderer;

};
