#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxDelaunay.h"
//#include "ofxCv.h"

using namespace cv;

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	ofVideoPlayer myPlayer;
	ofVideoGrabber video;		//Declare the video player object
	ofxCvColorImage image;

	ofxCvGrayscaleImage grayImage;
	ofxCvGrayscaleImage inverted;
	ofxCvGrayscaleImage blurred;
	ofxCvGrayscaleImage mask;

	ofxDelaunay triangulation;

	vector <glm::vec2> getTriangle(int i);
    vector<Point2f> corners;
};

