#pragma once

#include "ofMain.h"
#include "FboSource.h"

class JumpingBarSource : public ofx::piMapper::FboSource {
	public:
        void setup();
		void update();
		void draw();
        void setName(string);
        void setupJumpingBar();
        void updateJumpingBar();
        void reset();
        void drawJumpingBar(int x, int y, int w, int h);
		void Bar(float x, float p, float a, int i);

		float phase;
		vector<ofColor> color;
		ofColor backColor;


};
