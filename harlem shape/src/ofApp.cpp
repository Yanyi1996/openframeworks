#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);
	ofSetBackgroundAuto(false);
	ofSetFrameRate(60);
	stepSize = 80;

	spacingX = ofGetWidth() / numX;
	spacingY = ofGetHeight() / numY;
	startingX = spacingX / 2;
	startingY = spacingY / 2;

	for (int x = 0; x < numX; x++) {
		for (int y = 0; y < numY; y++) {
			noiseSeeds[x][y]= ofRandom(0, 1000);
		}
	}

	goCrazy = false;

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(0, 0, 0, 20);
	ofDrawRectangle(0, 0, 2000, 1000); // leave the trail

	for (int x = 0; x < numX; x++) {
		for (int y = 0; y < numY; y++) {

			if (goCrazy) {
				int locX = startingX + spacingX * x + ofSignedNoise(noiseSeeds[x][y]) * stepSize;
				int locY = startingY + spacingY * y + ofSignedNoise(noiseSeeds[x][y] + 50) * stepSize;
				int width = ofRandom(100,130) * ofNoise(noiseSeeds[x][y]);
				int height = ofRandom(100,130) * ofNoise(noiseSeeds[x][y]);

				ofColor c1 = ofColor(ofColor::deepSkyBlue);
				ofColor c2 = ofColor(ofColor::aliceBlue);
				ofColor CrazyColor1 = c1.getLerped(c2, ofNoise(noiseSeeds[x][y]));
				ofSetColor(CrazyColor1);
				ofSetLineWidth(ofNoise(noiseSeeds[x][y])*0.5);
				ofNoFill();
				ofDrawEllipse(locX, locY, width, height);

				ofColor c3 = ofColor(ofColor::whiteSmoke);
				ofColor c4 = ofColor(ofColor::ghostWhite);
				ofColor CrazyColor2 = c3.getLerped(c4, ofNoise(noiseSeeds[x][y]));
				ofSetColor(CrazyColor2);
				ofFill();
				ofDrawEllipse(locX+2, locY+2, width*0.05, height*0.05);

			}

			else if (!goCrazy) {
				int locX = startingX + spacingX * x;
				int locY = startingY + spacingY * y;
				ofColor c1 = ofColor(ofColor::forestGreen);
				ofColor c2 = ofColor(ofColor::deepSkyBlue);
				ofColor notCrazyColor = c1.getLerped(c2, ofNoise(noiseSeeds[x][y]));
				ofSetColor(notCrazyColor);
				int lineStep = 25;
				ofDrawLine(locX, locY, locX + ofSignedNoise(noiseSeeds[x][y])*lineStep, locY + ofSignedNoise(noiseSeeds[x][y])*lineStep);
			}

			noiseSeeds[x][y] += 0.005;
			
		}
	}
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	// move
	if (key == 'm') {
		goCrazy = true;
	}

	//stop
	else if (key == 's') {
		goCrazy = false;
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
