#pragma once

#include "ofMain.h"
#include "FboSource.h"

class RectFallSource : public ofx::piMapper::FboSource {
	public:
        void setup();
		void update();
		void draw();
        void setName(string);
        void setupRectFall();
        void updateRectFall();
        void reset();
        void drawRectFall(int x, int y, int w, int h);

		static const int numX = 20;
		static const int numY = 20;
		float noiseSeeds[numX][numY];
		float stepSize;
		int a, moveY, spacingX, spacingY, startingX, startingY;
		vector<ofColor> color;

};
