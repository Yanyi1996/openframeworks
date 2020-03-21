#pragma once
#include "ofMain.h"
#include "Rule.h"
#include "LSystem.h"
#include "Turtle.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void mousePressed(int x, int y, int button);

		vector<LSystem> lsys;
		LSystem Lsnow;
        vector<Rule> ruleset1, ruleset2, ruleset3, ruleset4; // The ruleset (an array of Rule objects)
        vector<Turtle> turtle;
		Turtle snowTurtle;
		vector<glm::vec2> snow;

		int total_iterations;
		int r = 0;
		float length, angle;
		float time = 0;
};
