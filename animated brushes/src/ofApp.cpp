#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(255);
	ofSetBackgroundAuto(false);
	ofSetFrameRate(60);
	ofSetColor(255, 224, 236, 100);
	ofNoFill();
	angle = 0;
	angleSpeed = 0.01;
	angleACC = 0.05;
	shapeLength = 100;
	ofSetLineWidth(1);
	locX = 0;
	locY = 0;

}

//--------------------------------------------------------------
void ofApp::update(){
	if (drawIsOn == true) {
		angle = angle + angleSpeed;

		//case1: if one point is fixed as centre of the canvas, calculate line point location
		locX = shapeLength * cos(angle);
		locY = shapeLength * sin(angle);

		//casa2: if start point is mouse location
		//locX = mouseX + shapeLength * cos(angle);
		//locY = mouseY + shapeLength * sin(angle);

	}
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	//move to center of canvas 
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

	if (drawIsOn == true) {
		// fix canvas and draw line
		ofPushMatrix();
		ofRotate(angle);

		//1. fixed start point to draw lines
		//ofDrawLine(0, 0, locX, locY);
		
		//2. start point of line is the mouse location
		//ofDrawLine(mouseX, mouseY, locX, locY); 
		
		//3. random bezier line as animated brush
		ofDrawBezier(ofRandom(0, 10), ofRandom(0,10), ofRandom(0,100), ofRandom(50,150), locX + ofRandom(5,200), locY + ofRandom(0,300), locX * ofRandom(1, 1.5), locY * ofRandom(0.8, 1.2));
		
		//4. random bezier area as animated brush
		//ofDrawBezier(0,0,ofRandom(0, 50), ofRandom(0, 50), locX + ofRandom(5, 50), locY + ofRandom(0, 100), locX * ofRandom(2, 2.5), locY * ofRandom(2, 3));
		
		ofPopMatrix();
	}
	

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	glReadBuffer(GL_FRONT);  // needed on windows, when using ofSetAutoBackground(false)

	if (key == 'r' || key == 'R') {
		ofBackground(255); // clear background
	}

	else if (key == OF_KEY_DOWN) {
		shapeLength = shapeLength - ofRandom(50, 150);
	}
	else if (key == OF_KEY_UP) {
		shapeLength = shapeLength + ofRandom(50,150);
	}
	else if (key == OF_KEY_LEFT) {
		angleSpeed = angleSpeed + angleACC;
	}
	else if (key == OF_KEY_RIGHT) {
		angleSpeed = angleSpeed - angleACC;
	}
	else if (key == 's' || key == 'S') {
		ofSaveScreen(ofToString(ofGetFrameNum()) + ".png");
	}
	else if (key == ' ') {
		ofSetColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255), ofRandom(10, 60));
	}
	else if (key == '1') {
		ofSetColor(40,235,235,100);
	}
	else if (key == '2') {
		ofSetColor(196, 18, 83, 100);
	}
	else if (key == '3') {
		ofSetColor(268, 237, 50, ofRandom(50,100));
	}

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
	if (ofGetMousePressed()) {
		drawIsOn = true;
	}

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	drawIsOn = false;

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
