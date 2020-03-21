#pragma once
#include "ofMain.h"

class Snake : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void addLocation(int, int);

	deque<glm::vec2> s;


};