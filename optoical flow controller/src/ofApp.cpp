#include "ofApp.h"
//#include "tracking.hpp"
#include "opencv2/opencv.hpp"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(60);
    video.setDeviceID(0);
    video.setDesiredFrameRate(60);
    video.initGrabber(640, 480);
    calculatedFlow = false;

	phaseX = 0;
	phaseY = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
	phaseX += avgX * 15;
	phaseY += avgY * 15;

	video.update();		//Decode the new frame if needed

	if ( video.isFrameNew() )
        {
		if ( gray1.bAllocated ) {
			gray2 = gray1;
			calculatedFlow = true;
		}

        //Convert to ofxCv images
        ofPixels & pixels = video.getPixels();
        currentColor.setFromPixels( pixels );

        float decimate = 0.25;              //Decimate images to 25% (makes calculations faster + works like a blurr too)
        ofxCvColorImage imageDecimated1;
        imageDecimated1.allocate( currentColor.width * decimate, currentColor.height * decimate );
        imageDecimated1.scaleIntoMe( currentColor, CV_INTER_AREA );             //High-quality resize
        gray1 = imageDecimated1;

		if ( gray2.bAllocated ) {
            Mat img1 = cvarrToMat(gray1.getCvImage());
            Mat img2 = cvarrToMat(gray2.getCvImage());
            Mat flow;                        //Image for flow
            //Computing optical flow (visit https://goo.gl/jm1Vfr for explanation of parameters)
            calcOpticalFlowFarneback( img1, img2, flow, 0.7, 3, 11, 5, 5, 1.1, 0 );
            //Split flow into separate images
            vector<Mat> flowPlanes;
            split( flow, flowPlanes );
            //Copy float planes to ofxCv images flowX and flowY
            //we call this to convert back from native openCV to ofxOpenCV data types
            IplImage iplX( flowPlanes[0] );
            //cvConvert(flowX, iplX);
            flowX = &iplX;
            IplImage iplY( flowPlanes[1] );
            flowY = &iplY;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground( 255, 255, 255);	//Set the background color

	float sumX = 0;
	float sumY = 0;
	avgX = 0;
	avgY = 0;
	float numOfEntries = 0;

    if (calculatedFlow)
    {
        ofSetColor( 255, 255, 255 );
        video.draw( 0, 0);

        int w = gray1.width;
        int h = gray1.height;

        //1. Input images + optical flow
        ofPushMatrix();

        ofScale( 4, 4 );

        //Optical flow
        float *flowXPixels = flowX.getPixelsAsFloats();
        float *flowYPixels = flowY.getPixelsAsFloats();
        ofSetColor( 0, 0, 255 );
        for (int y=0; y<h; y+=5) {
            for (int x=0; x<w; x+=5) {
                float fx = flowXPixels[ x + w * y ];
                float fy = flowYPixels[ x + w * y ];
                //Draw only long vectors
                if ( fabs( fx ) + fabs( fy ) > 1 ) {
                    ofDrawRectangle( x-0.5, y-0.5, 1, 1 );
                    ofDrawLine( x, y, x + fx, y + fy );
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

//	avgX = ofClamp(avgX, -5, 5);

	//ofPushMatrix();
	//ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

	//door
	int numOfDoors = 4;
	for (int i = 0; i < numOfDoors; i++) {
		door(phaseX + i * 180 / numOfDoors, phaseY + i * 180 / numOfDoors); // we spread the "doors" of half a cycle (180 degrees).
	}

	//ofSetColor(255, 0, 0);
	//ofDrawLine(0, 0, avgX * 10, avgY * 10);
	//ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::door(float px, float py) {
	ofPushMatrix();
	ofPushStyle();
	ofSetRectMode(OF_RECTMODE_CENTER);
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	ofRotateY(px);
	ofRotateX(py);
	float s = abs(sin(ofDegToRad(px))) + 0.3; // basically ranges from 0.3 to 1.3. Get it why?
	ofScale(s, s, s);
	ofNoFill();
	ofSetColor(0);
	ofSetLineWidth(3);
	ofDrawRectangle(0, 0, 200, 200);
	ofPopStyle();
	ofPopMatrix();
}
