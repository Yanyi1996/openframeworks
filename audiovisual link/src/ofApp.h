#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    // Audio output and input methods
    
        // Audio output and input methods
        // Audio output and input methods
        int sampleRate;
        int bufferSize;
        void audioOut(ofSoundBuffer & buffer);
        void exit();
        ofSoundStreamSettings soundSettings;
        ofSoundStream soundStream;
    
        maxiOsc osc1, osc2, osc3, osc4;

        float phase;
		void curve(int num);
        float freqMod1, freqMod2;
        float ampMod;
		float newMod1, newMod2;

		vector <ofColor> color;

};
