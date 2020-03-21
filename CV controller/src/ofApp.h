#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxOpenCv.h"
using namespace cv;

#define HOST "localhost" //modify to receiver's address
#define PORT 6448

//--------------------------------------------------------
class ofApp : public ofBaseApp {

	public:

		void setup();
		void update();
		void draw();

		ofVideoGrabber video;
		bool calculatedFlow;
		float avgX;
		float avgY;
		float phaseX;
		float phaseY;

		ofxCvColorImage currentColor;		//First and second original images
		ofxCvGrayscaleImage gray1, gray2;	//Decimated grayscaled images
		ofxCvFloatImage flowX, flowY;		//Resulted optical flow in x and y axes

		ofxOscSender sender;
		vector<int> posX, posY;

};
