#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);
    ofSetBackgroundAuto(false);
    ofSetFrameRate(60);
	ofSetLineWidth(0.8);
	//ofEnableBlendMode(ofBlendMode(OF_BLENDMODE_SCREEN));

	color.push_back(ofColor(255, 0, 0));
	color.push_back(ofColor(0, 255, 0));
	color.push_back(ofColor(0, 0, 255));
    
    sampleRate     = 44100; /* Sampling Rate */
    bufferSize    = 512; /* Buffer Size. you have to fill this buffer with sound using the for loop in the audioOut method */
    
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    //sets up the soundStream object with default devices
    auto devices = soundStream.getMatchingDevices("default");
    //you can also list input/output devices with soundStream.printDeviceList()
    soundSettings.setOutListener(this);
    soundSettings.sampleRate = sampleRate;
    soundSettings.numOutputChannels = 2;
    soundSettings.numInputChannels = 0;
    soundSettings.bufferSize = bufferSize;
    soundStream.setup(soundSettings);
    
    phase = 0;
    freqMod1 = 0;
	freqMod2 = 0;
    ampMod = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
        newMod1 = ofMap(freqMod1, -1, 1, 1,10);
		newMod2 = ofMap(ampMod, -1, 1, 20, 300);
		freqMod2 = abs(sin(phase));

        phase+=5;

		cout << "freqMod: " << freqMod1 << "  " << "ampMod: " << ampMod << endl;

}

//--------------------------------------------------------------
void ofApp::draw(){

	//visual control audio
	ofSetColor(0,0,0,30);
	ofFill();
	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

	int numOfCurves = 10;
	ofNoFill();
	ofSetColor(255*abs(freqMod1),250,200);

	for (int i = 0; i < numOfCurves; i++) {
		curve(i);
	}

}


//--------------------------------------------------------------
void ofApp::curve(int num) {
	ofBeginShape();
	for (int w = -20; w < ofGetWidth() + 20; w += 5) {
		int h = ofGetHeight() / 2;
		h += newMod2*sin(w * 0.03 + ofGetFrameNum() * 0.07 + num * TWO_PI / newMod1) * pow(abs(sin(w * 0.001 + ofGetFrameNum() * freqMod2)), 5);
		ofCurveVertex(w, h);
	}
	
	ofEndShape();
}
//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer & buffer){

    for (unsigned int i = 0; i < buffer.getNumFrames(); i++) { //loop through

		double wave1, wave2;

		ampMod = osc2.sinewave(1);
		freqMod1 = osc2.sinewave(osc3.square(freqMod2));

		//wave = osc1.sinewave(100 + osc2.sinewave(1) * 100);
		wave1 = osc1.sinewave(25 + ampMod * 100);
		wave2 = osc1.sinebuf4(25 + freqMod1 * 150);

         //wave = osc1.sinewave(440 * osc2.sinewave(freqMod*100));
         //wave *= ampMod;

		 buffer[i*buffer.getNumChannels()] = wave1 * wave2; //left
		 buffer[i*buffer.getNumChannels() + 1] = wave1 * wave2; //right
     }    
}
void ofApp::exit() {
    ofSoundStreamClose();
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
