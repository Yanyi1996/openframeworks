#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);
	ofSetFrameRate(60);
	a = 5;
	phase = 0;
	ofNoFill();
}

//--------------------------------------------------------------
void ofApp::update(){
	int rangeX = 220;
	int rangeY = 220;

	//mouse controls off-centre location
	x = ofMap(mouseX, 0, ofGetWidth(), -rangeX, rangeX);
	y = ofMap(mouseY, 0, ofGetHeight(), -rangeY, rangeY);

	phase++;


}


//--------------------------------------------------------------
void ofApp::draw(){
	int numOfHex = 65;
	int gap = 5.5;
	for (int i = 0; i <numOfHex; i++) {
		ofColor c1 = ofColor::orangeRed;
		ofColor c2 = ofColor::mediumPurple;
        ofColor c = c1.getLerped(c2, ofMap(i, 0, numOfHex, 0, 1));
		ofSetColor(c);
		hexgon(a + i * gap, (20 - i)*(x / numOfHex), (20 - i)*(y / numOfHex),phase);
	}


}


//--------------------------------------------------------------
void ofApp::hexgon(float a, float x, float y, float p) {
	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2 + x, ofGetHeight() / 2 + y); //off-centre
	ofSetPolyMode(OF_POLY_WINDING_NONZERO);
	float s = sin(ofDegToRad(p)) + 0.2;
	ofScale(s, s, s);

	// draw hexagon
	ofBeginShape();
	ofVertex(0, -a);
	ofVertex(a*cos(ofDegToRad(30)), -a * sin(ofDegToRad(30)));
	ofVertex(a*cos(ofDegToRad(30)), a * sin(ofDegToRad(30)));
	ofVertex(0, a);
	ofVertex(-a * cos(ofDegToRad(30)), a * sin(ofDegToRad(30)));
	ofVertex(-a * cos(ofDegToRad(30)), -a * sin(ofDegToRad(30)));
	ofEndShape();
	ofPopMatrix();

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
