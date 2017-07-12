#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxSimpleSerial.h"
#include <vector>
#include "ofUtils.h"

using namespace std;

class guitarreader {
	
	public:
	
		ofxSimpleSerial	serial;
		string		message;
        bool        state[6][8];
        uint64_t    requestLastTime;
        int         requestPeriod;
	
		void		setup();
		void		update();
        void		draw(); // example visualization
		void		mousePressed(int x, int y, int button);
		void		onNewMessage(string & message);
		
	protected:
		
};	

#endif	

