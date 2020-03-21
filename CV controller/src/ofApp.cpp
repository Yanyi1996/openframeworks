#include "ofApp.h"
//#include "tracking.hpp"
#include "opencv2/opencv.hpp"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(40, 100, 40);
	// open an outgoing connection to HOST:PORT
	sender.setup(HOST, PORT);

	ofSetFrameRate(60);
	video.setDeviceID(0);
	video.setDesiredFrameRate(60);
	video.initGrabber(640, 480);
	calculatedFlow = false;

}

//--------------------------------------------------------------
void ofApp::update(){

	video.update();		//Decode the new frame if needed

	if (video.isFrameNew())
	{
		if (gray1.bAllocated) {
			gray2 = gray1;
			calculatedFlow = true;
		}

		//Convert to ofxCv images
		ofPixels & pixels = video.getPixels();
		currentColor.setFromPixels(pixels);

		float decimate = 0.25;              //Decimate images to 25% (makes calculations faster + works like a blurr too)
		ofxCvColorImage imageDecimated1;
		imageDecimated1.allocate(currentColor.width * decimate, currentColor.height * decimate);
		imageDecimated1.scaleIntoMe(currentColor, CV_INTER_AREA);             //High-quality resize
		gray1 = imageDecimated1;

		if (gray2.bAllocated) {
			Mat img1 = cvarrToMat(gray1.getCvImage());
			Mat img2 = cvarrToMat(gray2.getCvImage());
			Mat flow;                        //Image for flow
			//Computing optical flow (visit https://goo.gl/jm1Vfr for explanation of parameters)
			calcOpticalFlowFarneback(img1, img2, flow, 0.7, 3, 11, 5, 5, 1.1, 0);
			//Split flow into separate images
			vector<Mat> flowPlanes;
			split(flow, flowPlanes);
			//Copy float planes to ofxCv images flowX and flowY
			//we call this to convert back from native openCV to ofxOpenCV data types
			IplImage iplX(flowPlanes[0]);
			//cvConvert(flowX, iplX);
			flowX = &iplX;
			IplImage iplY(flowPlanes[1]);
			flowY = &iplY;
		}
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	// display instructions
	string buf;
	buf = "sending osc messages to" + string(HOST) + ofToString(PORT);
	ofDrawBitmapString(buf, 10, 20);
	ofDrawBitmapString("move the mouse to send osc message [/mouse/position <x> <y>]", 10, 50);
	ofDrawBitmapString("click to send osc message [/mouse/button <button> <\"up\"|\"down\">]", 10, 65);
	ofDrawBitmapString("press A to send osc message [/test 1 3.5 hello <time>]", 10, 80);

	ofBackground(255, 255, 255);	//Set the background color

	float sumX = 0;
	float sumY = 0;
	avgX = 0;
	avgY = 0;
	float numOfEntries = 0;

	if (calculatedFlow)
	{
		ofSetColor(255, 255, 255);
		video.draw(0, 0);

		int w = gray1.width;
		int h = gray1.height;

		//1. Input images + optical flow
		ofPushMatrix();

		ofScale(4, 4);

		//Optical flow
		float *flowXPixels = flowX.getPixelsAsFloats();
		float *flowYPixels = flowY.getPixelsAsFloats();
		ofSetColor(0, 0, 255);
		for (int y = 0; y < h; y += 5) {
			for (int x = 0; x < w; x += 5) {
				float fx = flowXPixels[x + w * y];
				float fy = flowYPixels[x + w * y];
				//Draw only long vectors
				if (fabs(fx) + fabs(fy) > 1) {
					ofDrawRectangle(x - 0.5, y - 0.5, 1, 1);
					ofDrawLine(x, y, x + fx, y + fy);
				}

				sumX += fx;
				sumY += fy;
				numOfEntries++;
			}
		}
		ofPopMatrix();
	}

	if (numOfEntries > 0) {
		avgX = sumX / numOfEntries;
		avgY = sumY / numOfEntries;
	}

	// send package to processing
	ofxOscMessage m;
	m.setAddress("/processing/squarePosition");
	m.addFloatArg(avgX);
	m.addFloatArg(avgY);
	sender.sendMessage(m, false);
}




