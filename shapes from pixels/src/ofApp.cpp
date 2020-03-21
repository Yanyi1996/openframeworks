#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(255);
	//ofSetBackgroundAuto(false);
	ofSetFrameRate(60);
	vidGrabber.listDevices();
	vidGrabber.setDeviceID(0);
	vidGrabber.setDesiredFrameRate(30);
	vidGrabber.initGrabber(1280,720);

	spacing = 10;
	startPos = spacing / 2;


}

//--------------------------------------------------------------
void ofApp::update(){
	vidGrabber.update();
	pixels = vidGrabber.getPixels();
	pixels.mirror(false, true);

}

//--------------------------------------------------------------
void ofApp::draw() {
	//ofSetCircleResolution(30);
	int numX = ofGetWidth() / spacing;
	int numY = ofGetHeight() / spacing;
	int maxSize = ofMap(mouseX, 0, ofGetWidth(), 0, spacing * 2);

	for (int x = 0; x < numX; x++) {
		for (int y = 0; y < numY; y++) {
			int locX = startPos + spacing * x;
			int locY = startPos + spacing * y;

			ofColor c = pixels.getColor(locX, locY);
			int brightness = c.getBrightness();
			ofSetColor(c);

			float radius = ofMap(brightness, 0, 255, maxSize, 0);
			//ofPushMatrix();
			//ofTranslate(locX,locY);
			ofDrawCircle(locX, locY, radius);
			//ofPopMatrix();
		}
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
