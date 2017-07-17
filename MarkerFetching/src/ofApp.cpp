#include "ofApp.h"
#include "../../../../addons/ofxCv/src/ofxCv.h"
#include "ofBitmapFont.h"
#include <iostream>
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
const string ofApp::PLAY_ALONG = "Play Along";
const string ofApp::CHORD_WORKSHOP = "Chord Workshop";
const string ofApp::PLAY = "Play";
const string ofApp::PAUSE = "Pause";
const string ofApp::RESET_CHORD = "Reset Chord";

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
        grabber.setDeviceID(0);
        grabber.initGrabber(CAM_WIDTH,CAM_HEIGHT);
		video = &grabber;
	}

	//aruco.setThreaded(false);
	aruco.setup("intrinsics.int", video->getWidth(), video->getHeight(), boardName);
	aruco.getBoardImage(board.getPixels());
	board.update();

    overlay = new GuitarOverlay(guitar);
    songPlayer = new SongPlayer(overlay, SongPlayer::SMOKE_ON_THE_WATER);
    songPlayer->overlay = overlay;

	showMarkers = true;
	showBoard = true;
    showBoardImage = false;

    ofEnableAlphaBlending();

    renderer.setup();
    overlay->setup();

    //-----GUI-----
    ofxDatGui::setAssetPath("/home/tim/Schreibtisch/VAR/of_v0.9.8_linux64_release/addons/ofxDatGui/");//Dependend on local path

    // instantiate and position the gui //
        menuGui = new ofxDatGui( ofxDatGuiAnchor::TOP_LEFT );
        menuGui->setWidth(CAM_WIDTH/4);

    // add some components //
        //menuGui->addTextInput("Choose Mode");

        menuGui->addFRM();
        //gui->addBreak();

    // add a folder to group a few components together //
        //ofxDatGuiFolder* folder = gui->addFolder("white folder", ofColor::white);
        //folder->addTextInput("** input", "nested input field");
        //folder->addSlider("** slider", 0, 100);
        //folder->addToggle("** toggle");
        //folder->addColorPicker("** picker", ofColor::fromHex(0xFFD00B));
    // let's have it open by default. note: call this only after you're done adding items //
        //folder->expand();

        //gui->addBreak();

    // add a couple range sliders //
        //gui->addSlider("position X", 0, 120, 75);
        //gui->addSlider("position Y", -40, 240, 200);
        //gui->addSlider("position Z", -80, 120, -40);

    // and a slider to adjust the gui opacity //
        //gui->addSlider("datgui opacity", 0, 100, 100);

    // and a colorpicker //
        //gui->addColorPicker("color picker", ofColor::fromHex(0xeeeeee));

    // add a wave monitor //
    // take a look inside example-TimeGraph for more examples of this component and the value plotter //
       // gui->addWaveMonitor("wave\nmonitor", 3, .2);

        //gui->addBreak();

    // add a dropdown menu //
        //vector<string> opts = {"Smoke on the Water (Intro)", "Song 2", "Song 3", "Song 4"};
        vector<string> opts = {"Play Along", "Chord Workshop"};
        menuGui->addDropdown("Select Mode", opts);
        //menuGui->addBreak();

    // add a 2d pad //
       //ofxDatGui2dPad* pad = gui->add2dPad("2d pad");

    // a button matrix //
        //gui->addMatrix("matrix", 21, true);

    // and a couple of simple buttons //
        //menuGui->addButton("click");
        //gui->addToggle("toggle fullscreen", true);

    // adding the optional header allows you to drag the gui around //
        //menuGui->addHeader(":: drag me to reposition ::");

    // adding the optional footer allows you to collapse/expand the gui //
        menuGui->addFooter()->setLabelWhenCollapsed("Main Menu");
        menuGui->collapse();

    // once the gui has been assembled, register callbacks to listen for component specific events //
        menuGui->onButtonEvent(this, &ofApp::onButtonEvent);
        menuGui->onToggleEvent(this, &ofApp::onToggleEvent);
        menuGui->onSliderEvent(this, &ofApp::onSliderEvent);
        menuGui->onTextInputEvent(this, &ofApp::onTextInputEvent);
        menuGui->on2dPadEvent(this, &ofApp::on2dPadEvent);
        menuGui->onDropdownEvent(this, &ofApp::onDropdownEvent);
        menuGui->onColorPickerEvent(this, &ofApp::onColorPickerEvent);
        menuGui->onMatrixEvent(this, &ofApp::onMatrixEvent);

        //gui->setOpacity(gui->getSlider("datgui opacity")->getScale());
    //  gui->setLabelAlignment(ofxofAppAlignment::CENTER);

    // finally let's load up the stock themes, press spacebar to cycle through them //
        themes = {  new ofxDatGuiTheme(true),
                    new ofxDatGuiThemeSmoke(),
                    new ofxDatGuiThemeWireframe(),
                    new ofxDatGuiThemeMidnight(),
                    new ofxDatGuiThemeAqua(),
                    new ofxDatGuiThemeCharcoal(),
                    new ofxDatGuiThemeAutumn(),
                    new ofxDatGuiThemeCandy()};
        tIndex = 0;
        mFullscreen = false;
}

//--------------------------------------------------------------
void ofApp::update(){

    if(reader) reader->update();
    songPlayer->update();
    video->update();
	if(video->isFrameNew()){
        mirroredPixels = video->getPixels();
        mirroredPixels.mirror(0,1);
        aruco.detectBoards(mirroredPixels);
    }
    renderer.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    //video->draw(0,0);
    //Draws the webcamfeed flipped on the y axis (mirrored)
    video->draw(CAM_WIDTH,0,-CAM_WIDTH, CAM_HEIGHT);
    overlay->drawChords();
    if(reader)reader->draw();
    vector<aruco::Marker> markers = aruco.getMarkers();

	if(showMarkers){
		for(int i=0;i<aruco.getNumMarkers();i++){
			aruco.begin(i);
            //drawMarker(0.15,ofColor::white);
            aruco::Marker currentMarker = markers[i];
           if((currentMarker.idMarker == 89)){ //Was marker 404 but mirroring it results in marker 89
               overlay->customDraw();
            }
            // Loading the 3d-model messes with the color
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

	if(showBoardImage){
        board.draw(ofGetWidth()-320,0,320,320*float(board.getHeight())/float(board.getWidth()));
    }
    if(songPlayer){
        if(songPlayer->isRunning()){
            //std::cout << "Heyho" << std::endl;
            ofDrawBitmapString("Time: " + ofToString((int) songPlayer->runningTime),(CAM_WIDTH/2)-30,10);
        }
    }
    //ofDrawBitmapString("markers detected: " + ofToString(aruco.getNumMarkers()),20,200);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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


//GUI
void ofApp::onButtonEvent(ofxDatGuiButtonEvent e)
{
    cout << "onButtonEvent: " << e.target->getLabel() << endl;
    if(e.target->is(PLAY)){
        songPlayer->play();
    }
    else if(e.target->is(PAUSE)){
        songPlayer->pause();
    }
    else if(e.target->is(RESET_CHORD)){
        reader->unlock();
    }
}

void ofApp::onToggleEvent(ofxDatGuiToggleEvent e)
{
    cout << "onToggleEvent: " << e.target->getLabel() << " " << e.checked << endl;
}

void ofApp::onSliderEvent(ofxDatGuiSliderEvent e)
{
    //cout << "onSliderEvent: " << e.target->getLabel() << " "; e.target->printValue();
    //if (e.target->is("datgui opacity")) menuGui->setOpacity(e.scale);
}

void ofApp::onTextInputEvent(ofxDatGuiTextInputEvent e)
{
    //cout << "onTextInputEvent: " << e.target->getLabel() << " " << e.target->getText() << endl;
}

void ofApp::on2dPadEvent(ofxDatGui2dPadEvent e)
{
    //cout << "on2dPadEvent: " << e.target->getLabel() << " " << e.x << ":" << e.y << endl;
}

void ofApp::onDropdownEvent(ofxDatGuiDropdownEvent e)
{
    cout << "onDropdownEvent: " << e.target->getSelected()->getName() << " Selected" << endl;

    //-----Switch into "Play Along"-----
    if(e.target->getSelected()->is(PLAY_ALONG)){
        this->makeModeGui(PLAY_ALONG);
        if(reader) {delete reader; reader = NULL; overlay->resetState();}
        if(songPlayer){
            songPlayer->play();
            int dropdownIndex = 0;
            if(songPlayer->songName == SongPlayer::SMOKE_ON_THE_WATER) dropdownIndex = 0;
            if(songPlayer->songName == SongPlayer::SEVEN_NATION_ARMY) dropdownIndex = 1;
            if(songPlayer->songName == SongPlayer::SONG_3) dropdownIndex = 2;
            if(songPlayer->songName == SongPlayer::SONG_4) dropdownIndex = 3;
            modeGui->getDropdown("Select Song")->select(dropdownIndex);
        }
    }
        //Choices in the "PA"-Mode
        if(e.target->getSelected()->is(SongPlayer::SMOKE_ON_THE_WATER)){
            if(songPlayer) {delete songPlayer; songPlayer = NULL; overlay->resetState();}
            songPlayer = new SongPlayer(overlay, SongPlayer::SMOKE_ON_THE_WATER);
            songPlayer->play();
        }
        if(e.target->getSelected()->is(SongPlayer::SEVEN_NATION_ARMY)){
            if(songPlayer) {delete songPlayer; songPlayer = NULL; overlay->resetState();}
            songPlayer = new SongPlayer(overlay, SongPlayer::SEVEN_NATION_ARMY);
            songPlayer->play();
        }

    //-----Switch into "Chord Workshop"-----
    else if(e.target->getSelected()->is(CHORD_WORKSHOP)){
        this->makeModeGui(CHORD_WORKSHOP);
        songPlayer->pause();
        if(!reader) reader = new GuitarReader(overlay);
    }
        //Choices in the "CW"-Mode
        if(e.target->getSelected()->is("Mayor")){
            reader->selectedType = GuitarOverlay::chordType::MAYOR;
        }
        if(e.target->getSelected()->is("Minor")){
            reader->selectedType = GuitarOverlay::chordType::MINOR;
        }
        if(e.target->getSelected()->is("Mayor7")){
            reader->selectedType = GuitarOverlay::chordType::MAYOR7;
        }
}

void ofApp::onColorPickerEvent(ofxDatGuiColorPickerEvent e)
{
    //cout << "onColorPickerEvent: " << e.target->getLabel() << " " << e.target->getColor() << endl;
    //ofSetBackgroundColor(e.color);
}

void ofApp::onMatrixEvent(ofxDatGuiMatrixEvent e)
{
    //cout << "onMatrixEvent " << e.child << " : " << e.enabled << endl;
    //cout << "onMatrixEvent " << e.target->getLabel() << " : " << e.target->getSelected().size() << endl;
}

void ofApp::makeModeGui(string mode)
{

        // If there is an old ModeMenu delete it
        if(modeGui){
            delete modeGui;
            modeGui = NULL;
        }
        //Instantiate the ModeMenu
        modeGui = new ofxDatGui(ofxDatGuiAnchor::TOP_RIGHT);
        modeGui->setWidth(CAM_WIDTH/4);
        //Setup the different elements for each Mode
        if(mode == PLAY_ALONG){
            vector<string> opts = {SongPlayer::SMOKE_ON_THE_WATER, SongPlayer::SEVEN_NATION_ARMY, "Song 3", "Song 4"};
            modeGui->addDropdown("Select Song", opts)->expand();
            modeGui->addButton(PLAY);
            modeGui->addButton(PAUSE);
        }
        else if(mode == CHORD_WORKSHOP){
            vector<string> opts = {"Minor", "Mayor", "Mayor7"};
            modeGui->addDropdown("Select Chord", opts)->expand();
            modeGui->addButton(RESET_CHORD);
        }

        modeGui->addFooter()->setLabelWhenCollapsed("Mode Menu");
        // once the gui has been assembled, register callbacks to listen for component specific events //
            modeGui->onButtonEvent(this, &ofApp::onButtonEvent);
            modeGui->onToggleEvent(this, &ofApp::onToggleEvent);
            modeGui->onSliderEvent(this, &ofApp::onSliderEvent);
            modeGui->onTextInputEvent(this, &ofApp::onTextInputEvent);
            modeGui->on2dPadEvent(this, &ofApp::on2dPadEvent);
            modeGui->onDropdownEvent(this, &ofApp::onDropdownEvent);
            modeGui->onColorPickerEvent(this, &ofApp::onColorPickerEvent);
            modeGui->onMatrixEvent(this, &ofApp::onMatrixEvent);


        // finally let's load up the stock themes, press spacebar to cycle through them //
            themes = {  new ofxDatGuiTheme(true),
                        new ofxDatGuiThemeSmoke(),
                        new ofxDatGuiThemeWireframe(),
                        new ofxDatGuiThemeMidnight(),
                        new ofxDatGuiThemeAqua(),
                        new ofxDatGuiThemeCharcoal(),
                        new ofxDatGuiThemeAutumn(),
                        new ofxDatGuiThemeCandy()};
            tIndex = 0;

        //Close the MainMenu
        menuGui->collapse();
}
