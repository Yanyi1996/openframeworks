#include "BallSource.h"

void BallSource::setup(){
	// Give our source a decent name
    name = "Jumping Ball FBO Source";

	// Allocate our FBO source, decide how big it should be
    allocate(400, 400);

    setupBall();

    //if you want to draw something inside setup you need to make calls to this->beginFbo() / this->endFbo as below
    //this->beginFbo();
    //ofClear(255,0,0);
    //this->endFbo();
}

void BallSource::setName(string _name){
    name = _name;
}

// Don't do any drawing here
void BallSource::update(){
    updateBall();
}

void BallSource::reset(){
    ofClear(0); // uncomment if you want canvas to be reset on the buffer when fbo source is called again
}

// No need to take care of fbo.begin() and fbo.end() here.
// All within draw() is being rendered into fbo;
void BallSource::draw(){
    ofPushStyle();
    //ofClear(backColor); // remove if you never want to update the background

	//reset location every 180 frames using modulo
	if (ofGetFrameNum() % 180 == 0) {
		locX = x;
		locY = fbo->getHeight();
		t = 1;
	}

    drawBall(0,0,fbo->getWidth(), fbo->getHeight());

    ofPopStyle();
}

//================================================================
void BallSource::setupBall() {
	//mondrian colors:red,yellow,blue + white & black
	color = { ofColor(239, 28, 35), ofColor(255, 239, 1), ofColor(49, 57, 152), ofColor(255)};

	x = 20;
	vx = 20;
	vy = 80;
	g = 9.8; //gravity
	t = 1;

}

void BallSource::updateBall(){
	locX = x + vx * t;
	locY = fbo->getHeight() - (vy * t - 0.5*g*t*t);
	t = t + 0.1;
}

void BallSource::drawBall(int x, int y, int w, int h){
	//leave trail
	ofSetColor(0, 20);
	ofDrawRectangle(0, 0, fbo->getWidth(), fbo->getHeight());

	ballColor = color[ofRandom(0, 4)];
	ofSetColor(ballColor);
	ofFill();
	ofDrawCircle(locX, locY, 10);
	ofSetLineWidth(2);
	lineColor = color[ofRandom(0, 4)];
	ofNoFill();
	ofDrawCircle(locX, locY, 10);

}

