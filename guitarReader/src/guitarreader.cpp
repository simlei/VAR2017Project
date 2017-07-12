#include "guitarreader.h"


//--------------------------------------------------------------
void guitarreader::setup()
{	 
    requestLastTime = 0;
    requestPeriod = 80; // this is fast

    for(int i=0; i<6; i++) {
        for(int k=0; k<8; k++) {
            state[i][k] = false;
        }
    }

    serial.setup("/dev/ttyACM0", 9600);
	serial.startContinuousRead();
    ofAddListener(serial.NEW_MESSAGE,this,&guitarreader::onNewMessage);
	
	message = "";
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

void guitarreader::onNewMessage(string & message)
{
    cout << "onNewMessage, message: " << message << "\n";
	
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
                    state[stringIdx][fretIdx] = true;
                } else {
                    state[stringIdx][fretIdx] = false;
                }
            }
        } else {
            cout << "unrecognized guitar message above ::2\n";
        }

    } else {
        cout << "unrecognized guitar message above ::1\n";
    }
}

void guitarreader::update()
{
    cout << "update!\n";
    if(ofGetElapsedTimeMillis() - requestLastTime > requestPeriod)
     {
        cout << "req!\n";
//        serial.sendRequest();

        requestLastTime = ofGetElapsedTimeMillis();
     }
}

//--------------------------------------------------------------
void guitarreader::draw()
{
    int topLeftX = 100;
    int topLeftY = 100;
    int width = 30;
    int height = 70;
    int deltaH = 40;
    int deltaW = 80;

    for(int i=0; i<6; i++) {
        for(int k=0; k<8; k++) {

            ofColor color = state[i][k] ? ofColor::green : ofColor::darkGray;
            ofSetColor(color);

            int midX = topLeftX + k*deltaW;
            int midY = topLeftY + i*deltaH;
            ofRect(midX, midY, width, height);
        }
    }
}

//--------------------------------------------------------------
void guitarreader::mousePressed(int x, int y, int button){
//	requestRead = true;
}
