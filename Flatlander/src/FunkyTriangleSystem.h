#pragma once

#include "ofMain.h"
#include "ofxDelaunay.h"
#include "FunkyTriangle.h"

class FunkyTriangleSystem : public ofBaseApp{
  public:
    FunkyTriangleSystem();

    void setup();
    void update();
    void draw();
	void addTri();
	void clear();
    
    vector <glm::vec2> getTriangle(int i);
    ofxDelaunay triangulation;
	vector <FunkyTriangle> tris;
	int pointNum;
};
