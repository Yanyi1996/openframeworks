#include "JumpingBarSource.h"

void JumpingBarSource::setup(){
	// Give our source a decent name
    name = "Jumping Bar FBO Source";

	// Allocate our FBO source, decide how big it should be
    allocate(400, 400);

    setupJumpingBar();

    //if you want to draw something inside setup you need to make calls to this->beginFbo() / this->endFbo as below
    //this->beginFbo();
    //ofClear(255,0,0);
    //this->endFbo();
}

void JumpingBarSource::setName(string _name){
    name = _name;
}

// Don't do any drawing here
void JumpingBarSource::update(){
    updateJumpingBar();
}

void JumpingBarSource::reset(){
    ofClear(255); // uncomment if you want canvas to be reset on the buffer when fbo source is called again
}

// No need to take care of fbo.begin() and fbo.end() here.
// All within draw() is being rendered into fbo;
void JumpingBarSource::draw(){
    ofPushStyle();
    //ofClear(backColor); // remove if you never want to update the background

    //background color changes every 120 frames using modulo
	if (ofGetFrameNum() % 120 == 0) {
		backColor = color[ofRandom(0,5)];
	}

    drawJumpingBar(0,0,fbo->getWidth(), fbo->getHeight());

    ofPopStyle();
}

//================================================================
void JumpingBarSource::setupJumpingBar() {
	phase = 0;
	//mondrian colors:red,yellow,blue + white & black
	color = { ofColor(239, 28, 35), ofColor(255, 239, 1), ofColor(49, 57, 152), ofColor(255),ofColor(0)};
}

void JumpingBarSource::updateJumpingBar(){
	phase++;
}

void JumpingBarSource::drawJumpingBar(int x, int y, int w, int h){
	//leave trail
	ofSetColor(backColor, 20);
	ofDrawRectangle(0, 0, fbo->getWidth(), fbo->getHeight());

	//draw a group of bars
	int num = 25;
	float spacing = float(fbo->getWidth()) / num;
	for (int i = 0; i < num; i++)
	{
		Bar(spacing * i, phase + i * 15, fbo->getWidth() / (2 * num), i % color.size()); //Rect(locX, phase, width of rect, color loop)
	}
}

//--------------------------------------------------------------
void JumpingBarSource::Bar(float x, float p, float a, int i) {
	//movement of one single bar
	float percent = abs(sin(ofDegToRad(p))); //length changes like sin from 0 to 1
	float len = percent * fbo->getHeight();
	ofSetColor(color[i]);
	ofDrawRectangle(x, 0, a, len); //Rect(locX, locY, width, length)
}
