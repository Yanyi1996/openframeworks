#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(125);
    ballSys.setup(15);

	mode = 1;
}

//--------------------------------------------------------------
void ofApp::update(){
    ballSys.update();

	voronoi.clear();
	voronoi.setBounds(ofRectangle(-1, -1, ofGetWidth(), ofGetHeight()));
	voronoi.setPoints(ballSys.getPoints());
	voronoi.generate();
}

//--------------------------------------------------------------
void ofApp::draw(){
	if (mode == 1) {
		ballSys.draw();
	}
	else if (mode == 2) {
		drawVoronoi();
	}

    ofDrawBitmapString("Total Agents: " + ofToString(ballSys.balls.size()), 10, 20);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    ballSys.infectBall(x,y);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'a') {
		ballSys.addBall(mouseX, mouseY);
	}

	else if (key == '1') {
		mode = 1;
	}

	else if (key == '2') {
		mode = 2;
	}
}

//--------------------------------------------------------------
void ofApp::drawVoronoi() {
	ofPushStyle();
	vector <ofxVoronoiCell> cells = voronoi.getCells();
	for (int i = 0; i < cells.size(); i++) {
		// DRAW CELL SURFACE
		int value = ballSys.getNearestBall(cells[i].centroid).health;
		float pc = ofMap(value, 0, 255, 0, 1);
		ofColor c1 = ofColor(255, 140, 0);
		ofColor c2 = ofColor(0, 0, 100);
		ofSetColor(c1.getLerped(c2, pc));

		ofFill();
		ofBeginShape();
		for (int j = 0; j < cells[i].points.size(); j++) {

			glm::vec3 thisPt = cells[i].points[j];
			ofVertex(thisPt);
		}
		glm::vec3 firstPoint = cells[i].points[cells[i].points.size() - 1];
		ofVertex(firstPoint);
		ofEndShape();

		// DRAW CELL BORDERS
		if (mode == 2) {
			ofSetColor(125);
			for (int j = 0; j < cells[i].points.size(); j++) {
				glm::vec3 lastPt = cells[i].points[cells[i].points.size() - 1];
				if (j > 0) {
					lastPt = cells[i].points[j - 1];
				}
				glm::vec3 thisPt = cells[i].points[j];

				if (!isBorder(lastPt) || !isBorder(thisPt)) {
					ofDrawLine(lastPt, thisPt);
				}
			}
			//ofSetColor(0);
			//ofDrawCircle(cells[i].pt, 2);
		}
	}
	ofPopStyle();
}
//--------------------------------------------------------------
bool ofApp::isBorder(glm::vec3 _pt) {
	ofRectangle bounds = voronoi.getBounds();

	return (_pt.x == bounds.x || _pt.x == bounds.x + bounds.width
		|| _pt.y == bounds.y || _pt.y == bounds.y + bounds.height);
}
