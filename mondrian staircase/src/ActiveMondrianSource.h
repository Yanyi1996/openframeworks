#pragma once

#include "ofMain.h"
#include "FboSource.h"

class ActiveMondrianSource : public ofx::piMapper::FboSource {
	public:
        void setup();
		void update();
		void draw();
        void setName(string);
        void setupMondrian();
        void updateMondrian();
        void reset();
        void drawMondrian(int x, int y, int w, int h);

		int n1, n2, width1, width2;
		float locX1, locX2;
		vector<ofColor> color;
		ofColor c1, c2, backColor, lineColor;

};
