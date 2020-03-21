#pragma once

#include "ofMain.h"

class FunkyTriangle : public ofBaseApp{
  public:
	FunkyTriangle();

    void setup(glm::vec2, glm::vec2, glm::vec2);
    void update();
    void draw();

	vector <glm::vec2> points;
	int phase1,phase2;
    
};
