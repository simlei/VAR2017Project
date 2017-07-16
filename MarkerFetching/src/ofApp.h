#pragma once

#include "ofMain.h"
#include "guitarreader.h"
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
        ofxDatGuiLabel* currentChordLabel;
        bool mFullscreen;
        uint tIndex;
        vector<ofxDatGuiTheme*> themes;
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
        const static string PLAY_ALONG;
        const static string CHORD_WORKSHOP;
        const static string PLAY;
        const static string PAUSE;
        const static string RESET_CHORD;

        ofVideoGrabber grabber;
        ofVideoPlayer player;
		ofBaseVideoDraws * video;
        ofPixels mirroredPixels;
        ofxAruco aruco;
        ofImage board;
        ofImage marker;

		bool useVideo;
		bool showMarkers;
		bool showBoard;
		bool showBoardImage;
        float runningTime;

        ofVec3f posLN = ofVec3f(0.0f, 0.0f, 0.0f);
        ofVec3f posLB = ofVec3f(-0.2f, 0, 0);
        ofVec3f posHN = ofVec3f(0, 0, 0.1f);
        ofVec3f posHB = ofVec3f(0.2f, 0, 0.1f);



        //GuitarMeasure testMeasure = GuitarMeasure(posLN, posLB, posHN, posHB);
        Guitar guitar = Guitar(posLN, posLB, posHN, posHB);
        GuitarOverlay* overlay;
        SongPlayer* songPlayer;
        GuitarReader* reader;
        noteRenderer renderer;

    private:


};
