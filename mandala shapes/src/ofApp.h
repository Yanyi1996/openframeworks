#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void star(float x, float y, float radius1, float radius2, int npoints);
		void mandala(int index);

		vector<float> locX, locY, radius1, radius2, moveX, speedX, moveY, speedY;
		float angleStep, rotAngle;
		vector<int> resolution, red, green;
		float noOfStars;

		
};
