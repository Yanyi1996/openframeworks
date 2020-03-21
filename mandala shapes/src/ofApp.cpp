#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	ofBackground(0);
	ofSetBackgroundAuto(false);
	ofSetLineWidth(0.3);
	angleStep = 0.05;
	rotAngle = 0;
	noOfStars = 20;
}

//--------------------------------------------------------------
void ofApp::update() {
      rotAngle = rotAngle + angleStep;
      if (rotAngle > 20 || rotAngle < -20) {
		 angleStep= angleStep * -1;
      }
	  for (int i = 0; i < resolution.size(); i++) {
		  moveX[i] = moveX[i] + speedX[i];
		  moveY[i]= moveY[i] + speedY[i];
	  }

}

//--------------------------------------------------------------
void ofApp::draw(){
	for (int i = 0; i < resolution.size(); i++) {
		ofPushMatrix();
		ofTranslate(-ofGetWidth() / 2 + locX[i] + moveX[i], -ofGetHeight() / 2 + locY[i] + moveY[i]); // when click the mouse, mandala will appear at the mouse position
		mandala(i);
		ofPopMatrix();
	}
}       

//--------------------------------------------------------------
void ofApp::mandala(int index) {
	for (int i = noOfStars; i > 0; i--) {
		ofPushMatrix();
		ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
		int blue = ofMap(i, 0, noOfStars, 0, 255, true);
		ofSetColor(red[index], green[index], blue, ofRandom(100,255));
		ofNoFill();
		ofRotateDeg(rotAngle* i);
		ofScale(i / noOfStars, i / noOfStars);
		star(0, 0, radius1[index], radius2[index], resolution[index]);
		ofPopMatrix();
	}


}

//--------------------------------------------------------------
void ofApp::star(float x, float y, float radius1, float radius2, int npoints) {
	float angle = 360.0 / npoints;
	float halfAngle = angle / 2.0;

	ofSetPolyMode(OF_POLY_WINDING_NONZERO);
	ofBeginShape();
	for (float a = 0; a < 360.0; a += angle)
	{
		float sx = x + cos(ofDegToRad(a)) * radius2;
		float sy = y + sin(ofDegToRad(a)) * radius2;
		ofVertex(sx, sy);
		sx = x + cos(ofDegToRad(a + halfAngle)) * radius1;
		sy = y + sin(ofDegToRad(a + halfAngle)) * radius1;
		ofVertex(sx, sy);
	}
	ofEndShape();
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
   if (button == 0) {
	  resolution.push_back(ofMap(mouseX, 0, ofGetWidth(), 3, 20, true));
	  locX.push_back(mouseX);
	  locY.push_back(mouseY);
	  radius1.push_back(ofRandom(199, 201));
	  radius2.push_back(ofMap(mouseY, 0, ofGetHeight(), 50, 400, true));
	  moveX.push_back(0);
	  moveY.push_back(0);
	  speedX.push_back(ofRandom(-30,30));
	  speedY.push_back(ofRandom(-30, 30));
	  red.push_back(ofRandom(0, 255));
	  green.push_back(ofRandom(0, 255));
   }

   else if (button == 2) {
	   if (resolution.size() > 0) {
		   resolution.pop_back();
		   locX.pop_back();
		   locY.pop_back();
		   radius1.pop_back();
		   radius2.pop_back();
		   speedX.pop_back();
		   speedY.pop_back();
		   red.pop_back();
		   green.pop_back();
	   }
   }
	
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
