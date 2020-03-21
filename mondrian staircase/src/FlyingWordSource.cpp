#include "FlyingWordSource.h"

void FlyingWordSource::setup(){
	// Give our source a decent name
    name = "Flying Word FBO Source";

	// Allocate our FBO source, decide how big it should be
    allocate(400, 400);

    setupFlyingWord();

    //if you want to draw something inside setup you need to make calls to this->beginFbo() / this->endFbo as below
    /*this->beginFbo();
    ofClear(255,0,0);
    this->endFbo();*/
}

void FlyingWordSource::setName(string _name){
    name = _name;
}

// Don't do any drawing here
void FlyingWordSource::update(){
    updateFlyingWord();
}

void FlyingWordSource::reset(){
    ofClear(255); // uncomment if you want canvas to be reset on the buffer when fbo source is called again
}

// No need to take care of fbo.begin() and fbo.end() here.
// All within draw() is being rendered into fbo;
void FlyingWordSource::draw(){
    ofPushStyle();
    //ofClear(0); // remove if you never want to update the background

	//background color changes every 120 frames using modulo
	if (ofGetFrameNum() % 120 == 0) {
		backColor = color[ofRandom(0, 5)];
		fontColor = color[ofRandom(0, 5)];
	}

    drawFlyingWord(0,0,fbo->getWidth(), fbo->getHeight());

    ofPopStyle();
}

//================================================================
void FlyingWordSource::setupFlyingWord() {
	myfont.load("Calibri", 50);
	a = fbo->getHeight();
	b = e = fbo->getWidth();
	c = 0;
	d = 0;
	color = { ofColor(255),ofColor(0),ofColor(239, 28, 35), ofColor(255, 239, 1), ofColor(49, 57, 152) }; //black + mondrian three colors:red,yellow,blue
}

void FlyingWordSource::updateFlyingWord(){
	//line length changes
	a--;
	b--;
	c++;
	d++;
	e--;

	//back to initial point per fixed frames (outlines)
	if (ofGetFrameNum() % 840 == 0) {
		a = fbo->getHeight();
		b = fbo->getWidth();
		c = 0;
		c1 = color[ofRandom(0, 5)];
	}

	//back to initial point per fixed frames (centre horizontal lines)
	if (ofGetFrameNum() % 420 == 0) {
		d = 0;
		e = fbo->getWidth();
		c2 = color[ofRandom(0, 5)];
	}
}

void FlyingWordSource::drawFlyingWord(int x, int y, int w, int h){
	int H = fbo->getHeight() / 4; //the height of all rectangle is same, H, quarter of canvas height
	//leave the trail
	ofSetColor(backColor, 20);
	ofDrawRectangle(0, 0, fbo->getWidth(), fbo->getHeight());

	//three centre horizontal lines
	ofSetColor(c2);
	ofSetLineWidth(5);
	ofDrawLine(0, H, d, H); //1st line, right direction
	ofDrawLine(0, 3 * H, d, 3 * H); //3rd line, right direction
	ofDrawLine(fbo->getWidth(), 2 * H, e, 2 * H); //2nd line, left direction

	//four outlines
	ofSetColor(c1);
	ofSetLineWidth(10);
	ofDrawLine(0, fbo->getHeight(), 0, a); //up direction
	ofDrawLine(0, fbo->getHeight(), c, fbo->getHeight()); //right direction
	ofDrawLine(fbo->getWidth(), 0, b, 0); //left direction
	ofDrawLine(fbo->getWidth(), 0, fbo->getWidth(), c); //down direction

	//words
	ofSetColor(fontColor);
	myfont.drawString("Mondrian's", b, 100); //1st line
	myfont.drawString("Stairs", c - 100, 200); //2nd line
	myfont.drawString("Stairs", b, 300); //3rd line
	myfont.drawString("Mondrian's", c - 250, 400); //4th line
    
}
