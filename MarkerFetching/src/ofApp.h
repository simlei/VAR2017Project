#pragma once

#include "ofMain.h"
#include "ofxAruco.h"
#include "noteRenderer.h"
#include "guitar.h"
#include "guitaroverlay.h"
#include "songplayer.h"
#include "ofxDatGui.h"

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
        //GUI
        ofxDatGui* menuGui;
        ofxDatGui* modeGui;
        bool mFullscreen;
        uint tIndex;
        vector<ofxDatGuiTheme*> themes;
        void refreshWindow();
        void toggleFullscreen();
        void onButtonEvent(ofxDatGuiButtonEvent e);
        void onToggleEvent(ofxDatGuiToggleEvent e);
        void onSliderEvent(ofxDatGuiSliderEvent e);
        void onTextInputEvent(ofxDatGuiTextInputEvent e);
        void on2dPadEvent(ofxDatGui2dPadEvent e);
        void onDropdownEvent(ofxDatGuiDropdownEvent e);
        void onColorPickerEvent(ofxDatGuiColorPickerEvent e);
        void onMatrixEvent(ofxDatGuiMatrixEvent e);
        //EventSubroutines
        void makeModeGui(string mode);

        //Constant Fields
        const static int CAM_WIDTH = 640;   //Developed with 640
        const static int CAM_HEIGHT = 480;  //Developed with 480
        const static string PLAY_ALONG;     //Problems arose with the prefix "const"
        const static string CHORD_WORKSHOP; //Problems arose with the prefix "const"

        ofVideoGrabber grabber;
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
        SongPlayer* songPlayer;

        //Out of ofNodeExample
        //ofLight light;
        //ofEasyCam cam;
        noteRenderer renderer;

    private:


};
