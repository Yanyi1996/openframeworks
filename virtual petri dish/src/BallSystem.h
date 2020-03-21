#pragma once
#include "ofMain.h"
#include "Ball.h"

class BallSystem{

	public:
	    BallSystem();
	    void setup(int _numOfBalls);
	    void update();
	    void draw();
        void addBall(int x, int y);
        void infectBall(int mX, int mY);
        void removeDeadBalls();
        void checkInfections();
        vector<Ball> balls;
		int numOfBalls;
        vector <glm::vec3> getPoints();
        Ball getNearestBall(glm::vec3 p);
};
