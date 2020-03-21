#include "Snake.h"

void Snake::setup() {

}
//---------------------
void Snake::update() {

}

//---------------------
void Snake::draw() {
	if (s.size()>1){
		for (int i = 0; i < s.size() - 1; i++) {
			ofDrawLine(s[i], s[i + 1]);
		}
	}
	

	
}

//---------------------
void Snake::addLocation(int x, int y) {
	
		s.push_front(glm::vec2(x,y));
	
		if (s.size() > 250) {
			s.pop_back();
		}

}
