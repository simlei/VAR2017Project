#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxSimpleSerial.h"
#include <vector>
#include "ofUtils.h"
#include "ofxDatGui.h"
#include "guitaroverlay.h"

using namespace std;

class GuitarReader {
	
	public:
        GuitarReader(GuitarOverlay* inputOverlay);
        ~GuitarReader();

        int         requestPeriod;
        bool        lockedChord;
        bool        electricFeedback[6][8];
        string		message;
        uint64_t    requestLastTime;
        ofxSimpleSerial	serial;
        GuitarOverlay* overlay;

		void		setup();
		void		update();
        void		draw(); // example visualization
		void		mousePressed(int x, int y, int button);
		void		onNewMessage(string & message);
        void        resetState();

        //Constant Fields
        const static int BOARD_WIDTH = 640/2;       // CAM_WIDTH/2
        const static int BOARD_HEIGHT = 480/4;      // CAM_HEIGHT/2
        const static int STRINGS = 6;
        const static int FRETS = 8;

	protected:
		
};	

#endif	

