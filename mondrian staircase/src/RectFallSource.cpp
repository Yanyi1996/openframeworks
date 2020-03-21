#include "RectFallSource.h"

void RectFallSource::setup(){
	// Give our source a decent name
    name = "RectFall FBO Source";

	// Allocate our FBO source, decide how big it should be
    allocate(400, 400);

    setupRectFall();

    //if you want to draw something inside setup you need to make calls to this->beginFbo() / this->endFbo as below
    //this->beginFbo();
    //ofClear(255,0,0);
    //this->endFbo();
}

void RectFallSource::setName(string _name){
    name = _name;
}

// Don't do any drawing here
void RectFallSource::update(){
    updateRectFall();
}

void RectFallSource::reset(){
    ofClear(0); // uncomment if you want canvas to be reset on the buffer when fbo source is called again
}

// No need to take care of fbo.begin() and fbo.end() here.
// All within draw() is being rendered into fbo;
void RectFallSource::draw(){
    ofPushStyle();
    ofClear(0); // remove if you never want to update the background

    //fall is back to initial location every 360 frames using modulo
    if (ofGetFrameNum()%360==0) {
		moveY = 0;
    }

    drawRectFall(0,0,fbo->getWidth(), fbo->getHeight());

    ofPopStyle();
}

//================================================================
void RectFallSource::setupRectFall() {
	a = 13;
	stepSize = 13;
	moveY = 0;
	color = { ofColor(239, 28, 35), ofColor(255, 239, 1), ofColor(49, 57, 152) }; //mondrian three colors:red,yellow,blue

	spacingX = fbo->getWidth() / numX;
	spacingY = fbo->getHeight() / numY;
	startingX = spacingX / 2;
	startingY = spacingY / 2;

	//perlin noise
	for (int x = 0; x < numX; x++) {
		for (int y = 0; y < numY; y++) {
			noiseSeeds[x][y] = ofRandom(0, 1000);
		}
	}
}

void RectFallSource::updateRectFall(){
	moveY += 2; //Y-axis move speed
}

void RectFallSource::drawRectFall(int x, int y, int w, int h){
	for (int x = 0; x < numX; x++) {
		for (int y = 0; y < numY; y++) {
			//draw 20x20 squares
			int locX = startingX + spacingX * x + ofSignedNoise(noiseSeeds[x][y]) * stepSize;
			int locY = startingY + spacingY * y + ofSignedNoise(noiseSeeds[x][y] + 30) * stepSize + moveY;
			int len = a * ofNoise(noiseSeeds[x][y]);
			ofSetColor(color[ofRandom(0, 3)]);
			ofFill();
			ofSetRectMode(OF_RECTMODE_CENTER);
			ofDrawRectangle(locX, locY - fbo->getHeight(), len, len);

			noiseSeeds[x][y] += 0.005;
		}
	}
}
