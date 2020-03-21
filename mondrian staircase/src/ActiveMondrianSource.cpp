#include "ActiveMondrianSource.h"

void ActiveMondrianSource::setup(){
	// Give our source a decent name
    name = "Active Mondrian FBO Source";

	// Allocate our FBO source, decide how big it should be
    allocate(400, 400);

    setupMondrian();

    //if you want to draw something inside setup you need to make calls to this->beginFbo() / this->endFbo as below
    /*this->beginFbo();
    ofClear(255,0,0);
    this->endFbo();*/
}

void ActiveMondrianSource::setName(string _name){
    name = _name;
}

// Don't do any drawing here
void ActiveMondrianSource::update(){
    updateMondrian();
}

void ActiveMondrianSource::reset(){
    ofClear(255); // uncomment if you want canvas to be reset on the buffer when fbo source is called again
}

// No need to take care of fbo.begin() and fbo.end() here.
// All within draw() is being rendered into fbo;
void ActiveMondrianSource::draw(){
    ofPushStyle();
    //ofClear(255); // remove if you never want to update the background

    //background color changes every 120 frames using modulo
	if (ofGetFrameNum() % 480 == 0) {
		backColor = ofColor(0);
		lineColor = ofColor(255);
	}
	else if (ofGetFrameNum() % 240 == 0) {
		backColor = ofColor(255);
		lineColor = ofColor(0);
	}

    drawMondrian(0,0,fbo->getWidth(), fbo->getHeight());
    ofPopStyle();
}

//================================================================
void ActiveMondrianSource::setupMondrian() {
	color = { ofColor(239, 28, 35), ofColor(255, 239, 1), ofColor(49, 57, 152) };//mondrian three colors:red,yellow,blue
    
}

void ActiveMondrianSource::updateMondrian(){
	//change parameters per 60 frames
	if (ofGetFrameNum() % 60 == 0) {
		//location y-axis is always on the stair (stair 1 ~ stair 4)
		n1 = ofRandom(0, 4);
		n2 = ofRandom(0, 4);

		//location x-axis
		locX1 = ofRandom(0, fbo->getWidth());
		locX2 = ofRandom(0, fbo->getWidth());

		//width of colorful rectangle
		width1 = ofRandom(10, 300);
		width2 = ofRandom(10, 300);

		//pick it from three typical mondrian colors
		c1 = color[ofRandom(0, 3)];
		c2 = color[ofRandom(0, 3)];
	}
    
}

void ActiveMondrianSource::drawMondrian(int x, int y, int w, int h){
	int H = fbo->getHeight() / 4; //the height of all rectangle is same, H, quarter of canvas height
	//leave trail
	ofSetColor(backColor, 20);
	ofDrawRectangle(0, 0, fbo->getWidth(), fbo->getHeight());

	//draw four white/black rectangles with black/white outlines
	ofNoFill();
	ofSetLineWidth(16);
	ofSetColor(lineColor);
	for (int i = 0; i < 4; i++) {
		ofDrawRectangle(0, H*i, fbo->getWidth(), H);
	}

	//draw filled colorful rectangle
	ofSetLineWidth(8);
	ofFill();
	ofSetColor(c1);
	ofDrawRectangle(locX1, n1*H, width1, H); //rect1
	ofSetColor(c2);
	ofDrawRectangle(locX2, n2*H, width2, H); //rect2
	//draw black/white outline
	ofNoFill();
	ofSetColor(lineColor);
	ofDrawRectangle(locX1, n1*H, width1, H); //rect1 outline
	ofDrawRectangle(locX2, n2*H, width2, H); //rect2 outline

	//draw vertical black/white line
	ofDrawLine(locX1, 0, locX1, fbo->getHeight()); //line1, associated with rect1
	ofDrawLine(locX2 + width2, 0, locX2 + width2, fbo->getHeight()); //line2, associated with rect2

}
