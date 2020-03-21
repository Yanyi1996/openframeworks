#pragma once

#include "ofMain.h"
#include "FboSource.h"

class BallSource : public ofx::piMapper::FboSource {
	public:
        void setup();
		void update();
		void draw();
        void setName(string);
        void setupBall();
        void updateBall();
        void reset();
        void drawBall(int x, int y, int w, int h);

		vector<ofColor> color;
		ofColor ballColor, lineColor;
		int x, vx, vy;
		float g, t, locX, locY;

};
