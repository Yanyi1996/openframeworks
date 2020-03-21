#pragma once

#include "ofMain.h"
#include "FboSource.h"

class FlyingWordSource : public ofx::piMapper::FboSource {
	public:
        void setup();
		void update();
		void draw();
        void setName(string);
        void setupFlyingWord();
        void updateFlyingWord();
        void reset();
        void drawFlyingWord(int x, int y, int w, int h);
        
		vector<ofColor> color;
		ofColor c1, c2, backColor,fontColor;
		float a, b, c, d, e;
		ofTrueTypeFont myfont;

};
