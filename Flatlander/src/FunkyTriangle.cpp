#include "FunkyTriangle.h"

//-------------------------------------------------------
FunkyTriangle::FunkyTriangle()
{
	phase1 = ofRandom(0,360);
	phase2 = 0;
}

//--------------------------------------------------------
void FunkyTriangle::setup(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3) {
	points.push_back(p1);
	points.push_back(p2);
	points.push_back(p3);
}

//--------------------------------------------------------
void FunkyTriangle::update() {
	phase1++;
	phase2++;
}

//--------------------------------------------------------------
void FunkyTriangle::draw() {
	//ofSetColor(ofColor::fromHsb(ofRandom(255), 255, 150));
	float n = ofMap(sin(ofDegToRad(phase1)), -1, 1, 0, 1);
	ofColor r = ofColor::orangeRed;
	ofColor g = ofColor::lightSkyBlue;
	ofColor p = r.getLerped(g, n);
	ofSetColor(p);
	ofDrawTriangle(points[0], points[1], points[2]);

	int transparency = ofMap(sin(ofDegToRad(phase1)), -1, 1, 255, 200);
	ofSetColor(ofColor::darkorange, transparency);
	int numRect = 10;
	float c = abs(cos(ofDegToRad(phase2)));
    for (int i = 0; i < numRect; i++) {
		glm::vec2 p1 = glm::vec2(((points[0].x - points[1].x) / numRect)*i + points[1].x, ((points[0].y - points[1].y) / numRect)*i + points[1].y);
		glm::vec2 p2 = glm::vec2(((points[0].x - points[2].x) / numRect)*i + points[2].x, ((points[0].y - points[2].y) / numRect)*i + points[2].y);
		glm::vec2 p3 = glm::vec2(((points[0].x - points[1].x) / numRect)*(i + c) + points[1].x, ((points[0].y - points[1].y) / numRect)*(i+c) + points[1].y);
		glm::vec2 p4 = glm::vec2(((points[0].x - points[2].x) / numRect)*(i + c) + points[2].x, ((points[0].y - points[2].y) / numRect)*(i + c) + points[2].y);

		ofBeginShape();
		ofVertex(p1);
		ofVertex(p2);
		ofVertex(p4);
		ofVertex(p3);
		ofEndShape();
	}

}

