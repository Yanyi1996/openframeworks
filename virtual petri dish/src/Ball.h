#pragma once
#include "ofMain.h"

class Ball{

	public:
		Ball();

        //member variables
        glm::vec3 location;
        glm::vec3 velocity;
        float radius;
        float maxSpeed;
        float xoff, yoff;
        float health;
        bool isAlive;
        float cureRate;
        float chanceOfDying;

        //member functions
        void draw();
        void move();
        void borders();
        bool isInside(int x, int y);
        void cure();
};
