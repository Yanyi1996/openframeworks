#pragma once

#include "ofMain.h"
#include "ofxVoiceController.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
       void audioIn(ofSoundBuffer & input);
		void keyPressed(int key);
		void keyReleased(int key);

    ofxVoiceController voiceController;
    ofSoundStream soundStream;
    
		
};
