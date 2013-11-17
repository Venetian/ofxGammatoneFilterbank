#include "testApp.h"
#include "sys/stat.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	secondsToLoad = 30.0;//sets how many seconds are loaded of the correlogram
	//see the correlogram class for the parameters such as number of gammatone filters and frequency range 
	
	//the data can be stored here
	//but change the boolean outputdata in correlogram class to true
	if (cgrammer.outputData){
		std::string makeDirName = "../bin/data/gammatoneTestData";
		int status = mkdir(makeDirName.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		cout << "status: " << status << endl;
	}
	
	std::string wavFile = "../bin/data/bach_short1.wav";//or whichever other file you choose 
	//use key command 'o' to open a new file
	//this will both load the data and do the gammatone analysis and load the file in the ofSoundPlayer instance
	
	
	//eg
	//std::string wavFile = "/Users/andrew/Music/Station To Station/02 Golden Years.wav";
	
	//stores the data, but you need to change 'outputData' boolean in cgrammer class
	dataFile = "../bin/data/gammatoneTestData/gtoneOutputdata.acg";
	
	loadFile(wavFile);
	
//	cgrammer.openFile(wavFile, dataFile, secondsToLoad);
///	player.loadSound(wavFile);	

//	frameNumber = 0;

	player.setVolume(0.75f);
}

//--------------------------------------------------------------
void testApp::update(){
	ofSoundUpdate();

}

//--------------------------------------------------------------
void testApp::draw(){
	//need to use the number of samples in the file
	//and max number stored in auxilliary
	
	
	/*
	double currentSample = player.getPosition() * cgrammer.wavSize;//in samples
	//need this as ratio of how many were actually loaded
	if (cgrammer.loadedSamplesSize > 0)
		frameNumber = round(cgrammer.acg.nframes()*currentSample/cgrammer.loadedSamplesSize);
	else 
		frameNumber = 0;

	//frameNumber = round(player.getPosition() * cgrammer.acg.nframes());
	
	cgrammer.drawFrame(frameNumber);
	*/
	
	cgrammer.drawFrameAtPosition(player.getPosition());
	
	ofSetColor(255);
	ofDrawBitmapString(ofToString(frameNumber), ofGetWidth()-20, 20);
	ofDrawBitmapString(textInfo, 20, 20);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	switch (key) {
		case ' ':
			startPlaying();
			break;
		case 'o':
			chooseNewFile();
			break;
		default:
			frameNumber++;
			break;
	}

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){
	//player.setSpeed((float)y/ofGetHeight());
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}



/////////

void testApp::loadFile(std::string wavFile){
	textInfo = "please wait";
	draw();
	
	player.loadSound(wavFile);
	cgrammer.openFile(wavFile, dataFile, 60.0);
	textInfo = wavFile;
}

void testApp::startPlaying(){
	player.play();
}

void testApp::chooseNewFile(){
	string URL;

	// openFile(string& URL) returns 1 if a file was picked
	// returns 0 when something went wrong or the user pressed 'cancel'
	int response = ofxFileDialogOSX::openFile(URL);
	if(response){
		// now you can use the URL 
		loadFile(URL);
		//soundFileName = URL;//"URL to open: \n "+URL;
	} else {
		std::cout << "OPEN cancelled" << std::endl;
	}
}

