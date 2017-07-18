#include "guitarreader.h"


//--------------------------------------------------------------
GuitarReader::GuitarReader(GuitarOverlay* inputOverlay):overlay(inputOverlay){
    overlay = inputOverlay;
    lockedChord = false;
    selectedType = GuitarOverlay::chordType::EMPTY;
    requestLastTime = 0;
    requestPeriod = 80; // this is fast
    toneCandidate = -1;
    setup();
}

void GuitarReader::setup()
{
    overlay->resetState();
    overlay->resetChords();
    overlay->mode = 2;
    resetState();
    serial.setup("/dev/ttyACM0", 19200);
    serial.startContinuousRead(false);
    ofAddListener(serial.NEW_MESSAGE,this,&GuitarReader::onNewMessage);
    message = "";
    //overlay->setChord(GuitarOverlay::Chord{10, GuitarOverlay::chordType::MAYOR});
}

GuitarReader::~GuitarReader(){

}

string trim(const string& str)
{
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

void GuitarReader::onNewMessage(string & message)
{
    //cout << "onNewMessage, message: " << message << "\n";
	
	vector<string> input = ofSplitString(message, ",");
	
//    cout << "size  " << input.size() << "\n";
//    cout << "at(0) " << input.at(0) << "\n";
    if(input.size() == 3 && trim(input.at(0)) == "string")
	{
        int stringIdx = std::stoi(input.at(1));
        string line = input.at(2);
        if(line.length() == 8) {
            for(int fretIdx = 0; fretIdx < 8; fretIdx++) {
                if(line.at(fretIdx) == 'o') {
                    electricFeedback[stringIdx][fretIdx] = true;
                } else {
                    electricFeedback[stringIdx][fretIdx] = false;
                }
            }
        } else {
            cout << "unrecognized guitar message above ::2\n";
        }

    } else {
        cout << "unrecognized guitar message above ::1\n";
    }
}

void GuitarReader::update()
{
    //std::cout << "update\n";
    if(ofGetElapsedTimeMillis() - requestLastTime > requestPeriod)
     {
        //serial.sendRequest();
        requestLastTime = ofGetElapsedTimeMillis();
     }
    if(!locked){
        //std::cout << "locked loop\n";

        int tempInt;
        bool doBreak = false;
        for(int strings=0; strings<6; strings++) {
            for(int frets=0; frets<8; frets++) {
                if(doBreak)break;
                if(electricFeedback[strings][frets]){
                    if((frets < 7) && electricFeedback[strings][frets+1]) //trying to get out the some uncertainty
                        {tempInt = overlay->getHalftoneFor(strings,frets+2);}
                    else
                        {tempInt = overlay->getHalftoneFor(strings,frets+1);}
                    doBreak = true;
                }
            }
            if(doBreak)break;
        }
        if(tempInt == toneCandidate){
            std::cout << toneCandidate << " | " << tempInt << std::endl;
            bufferTime += (float)ofGetLastFrameTime();
        }else if(doBreak){
            toneCandidate = tempInt;
            bufferTime = 0;
        }
        if(bufferTime >= 1){
            bufferTime = 0;
            if(selectedType != GuitarOverlay::chordType::EMPTY){
            overlay->setChord(GuitarOverlay::Chord{toneCandidate, selectedType});
            locked = true;
            }
        }
    }

}

//--------------------------------------------------------------
void GuitarReader::draw()
{
    int stringHeight = (BOARD_HEIGHT/STRINGS)-2;        //==18 (6 Strings)
    int gapHeight = STRINGS*2;                          //==12 (6 Strings)
    int fretWidth = (stringHeight/3)*2;                 //==12 (6 Strings)
    int gapWidth = (BOARD_WIDTH - 8*fretWidth)/8;       //==28 (6St & 8Frets)



    ofSetColor(ofColor::lightGrey);
    ofDrawRectangle(BOARD_WIDTH/2, 0, BOARD_WIDTH, BOARD_HEIGHT);

    for(int strings=0; strings<6; strings++) {
        for(int frets=0; frets<8; frets++) {
            ofColor color = electricFeedback[strings][frets] ? ofColor::green : ofColor::darkGray;
            int leftX = BOARD_WIDTH/2 + gapWidth/2 + (gapWidth+fretWidth)*frets;
            int topY = gapHeight/2 + stringHeight*strings;
            ofSetColor(color);
            ofDrawRectRounded(leftX, topY, fretWidth, stringHeight, 20.f);
        }
    }
}

//--------------------------------------------------------------
void GuitarReader::mousePressed(int x, int y, int button){
//	requestRead = true;
}

void GuitarReader::resetState(){
    for(int strings=0; strings<6; strings++) {
        for(int frets=0; frets<8; frets++) {
            electricFeedback[strings][frets] = false;
        }
    }
}

void GuitarReader::unlock(){
    //could just call setup() but that seems overkill
    overlay->resetState();
    toneCandidate = -1;
    locked = false;
}
