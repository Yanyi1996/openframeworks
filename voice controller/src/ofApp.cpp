#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetFrameRate(60);
    ofSoundStreamSettings settings;
     settings.setInListener(this);
     settings.sampleRate = 44100;
     settings.numOutputChannels = 0;
     settings.numInputChannels = 2;
     settings.bufferSize = 512;
     soundStream.setup(settings);
}

//--------------------------------------------------------------
void ofApp::update(){
    voiceController.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    cout << voiceController.classLabel << endl;
    if (voiceController.classLabel=="0") ofBackground(0);
    else if (voiceController.classLabel=="1") ofBackground(255,0,0);
    else if (voiceController.classLabel=="2") ofBackground(0,0,255);
}

//--------------------------------------------------------------
void ofApp::audioIn(ofSoundBuffer & input){
    voiceController.audioIn(input);
}
//--------------------------------------------------------------

void ofApp::keyPressed(int key){
    if(key=='r'){
        voiceController.startRecording();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key=='r'){
        voiceController.stopRecording();
    }
}

//--------------------------------------------------------------
