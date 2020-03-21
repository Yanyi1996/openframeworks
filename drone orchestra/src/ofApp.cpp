#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetFrameRate(60);
    
    sampleRate = 44100;
    bufferSize = 512;
    
    // settings for ofxMaxim.
    maxiSettings::setup(sampleRate, 2, bufferSize);
    
    //sets up the soundStream object with default devices
    auto devices = soundStream.getMatchingDevices("default");
    //you can also list input/output devices with soundStream.printDeviceList()
    soundSettings.setOutListener(this);
    soundSettings.sampleRate = sampleRate;
    soundSettings.numOutputChannels = 2;
    soundSettings.numInputChannels = 0;
    soundSettings.bufferSize = bufferSize;
    soundStream.setup(soundSettings);

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}
//--------------------------------------------------------------
void ofApp::exit() {
    ofSoundStreamClose();
}
//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer & buffer){
    
    for (unsigned int i = 0; i < buffer.getNumFrames(); i++) { //loop through the
        double wave1, wave2, wave3;

        // ==== EXAMPLE 1 ====
        // frequency moves from 440 to -440 every second (440 and -440 sound the same)
        //wave = osc1.sinewave(440 * osc2.sinewave(1));

        // ==== EXAMPLE 2 ====
        // frequency moves from 340 to 540 in one second.
        //  * carrier freq = 440
        //  * modulation freq = 1
        //  * modulation index = 100
        //wave = osc1.sinewave(440 + osc2.sinewave(1) * 100);

		//wave = osc1.sinewave(600 + osc2.sinewave(1));
		//wave = osc1.sinewave(800 + osc2.sinewave(1000));
		//wave = osc1.sinewave(600 + osc2.sinewave(1)*200);
		//wave = osc1.sinewave(400 + osc2.sinewave(20)*100);
		wave1 = osc1.sawn(100+ osc2.sinewave(1)*100);


        // ==== EXAMPLE 3 ====
        // frequency moves from from 340 to 540 in ever increasing speeds
        //  * carrier freq = 440
        //  * modulation freq = goes from 0 to 100 in 5 seconds and suddenly drops to 0
        //  * modulation index = 100
		
		//wave = osc1.sinewave(440 + osc2.sinewave(osc3.phasor(0.2, 0, 10)) * 100);
        //wave = osc1.sinewave(440 + osc2.sinewave( 200 ) * osc3.phasor(0.2,0,100)); //0.2*5=1 every five seconds
		wave2 = osc1.sawn(250 + osc2.sinewave(osc3.triangle(.25)) * 200); //triangle(5): five triangle waves in one second cycle
		
        buffer[i*buffer.getNumChannels()    ]= wave1+wave2; //left
        buffer[i*buffer.getNumChannels() + 1]= wave1+wave2; //right

    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
