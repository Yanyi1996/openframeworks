#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#define HOST "localhost" //modify to receiver's address
#define PORT 6448

//--------------------------------------------------------
class ofApp : public ofBaseApp {

	public:

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void mouseMoved(int x, int y);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseDragged(int x, int y, int button);

		ofxOscSender sender;
		vector<int> posX, posY;

};
