#pragma once
#include "ofMain.h"
#include "BallSystem.h"
#include "ofxVoronoi.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void mousePressed(int x, int y, int button);
		void keyPressed(int key);
		BallSystem ballSys;

		ofxVoronoi voronoi;
		bool isBorder(glm::vec3 _pt);
		void drawVoronoi();

		int mode;

};
