#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetFrameRate(60);

	for (int j = 0; j < 3; j++) {
		LSystem L;
		Turtle T;
		lsys.push_back(L);
		turtle.push_back(T);
	}

    //***tree 1: setting the ruleset, axiom and initializing the L-System
    Rule rule1('F', "F[+F]F[-F][F]");
    //total_iterations = 5;
    //length = ofGetHeight()/4;
    //angle = 20;
    ruleset1.push_back(rule1);

    //***tree 2: setting the ruleset, axiom and initializing the L-System
    Rule rule2('X', "F[+X]F[-X]+X");
    Rule rule3('F', "FF");
    ruleset2.push_back(rule2);
	ruleset2.push_back(rule3);
    //total_iterations = 7;
    //length = ofGetHeight()/2;
    //angle = 20;

    //***tree 3: setting the ruleset, axiom and initializing the L-System
    Rule rule4('X', "F-[[X]+X]+F[+FX]-X");
    Rule rule5('F', "FF");
    ruleset3.push_back(rule4);
	ruleset3.push_back(rule5);
    //total_iterations = 5;
    //length = ofGetHeight()/4;
    //angle = 22.5;

	//snowflake
	Rule rule6('F', "F - F + F + F - F");
	ruleset4.push_back(rule6);
	int snowIterations = 4;
	int snowLength = 80;
	int snowAngle = 90;
	Lsnow.setup("F - F - F - F", ruleset4);
	//generating snow L-system
	snowTurtle.setup(Lsnow.getSentence(), snowLength, snowAngle);
	for (int i = 0; i < snowIterations; i++) {
		Lsnow.generate();
		snowTurtle.setToDo(Lsnow.getSentence());
		snowTurtle.changeLen(0.5);
	}
	//generate random initial location of snowflake
	for (int i = 0; i < 20; i++) {
		snow.push_back(glm::vec2(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight())));
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	length = ofMap(mouseY, ofGetHeight(), 0, ofGetHeight()/8, ofGetHeight()/2.5,true);
	angle = ofMap(mouseX, 0, ofGetWidth(), 5, 55, true);
	total_iterations = ofMap(mouseX, 0, ofGetWidth(), 3, 7, true);

	r++;
	time += 0.5;
}

//--------------------------------------------------------------
void ofApp::draw(){
	//snows
	for (int i = 0; i < snow.size(); i++) {
		ofPushMatrix();
		ofTranslate(snow[i].x+20*i*ofSignedNoise(time),snow[i].y + 20 *i* ofSignedNoise(time));
		ofScale(0.04, 0.04);
		ofRotate(r);
		snowTurtle.render(false);
		ofPopMatrix();
	}

	//setting the L-system
	lsys[0].setup("F", ruleset1);
	lsys[1].setup("X", ruleset2);
	lsys[2].setup("X", ruleset3);

	//generating the L-system
	for (int j = 0; j < lsys.size(); j++) {
		turtle[j].setup(lsys[j].getSentence(), length, angle);
		for (int i = 0; i < total_iterations; i++) {
			lsys[j].generate();
			turtle[j].setToDo(lsys[j].getSentence());
			turtle[j].changeLen(0.5);
		}
		ofPushMatrix();
		ofTranslate((j+1)*ofGetWidth() / 4, ofGetHeight());
		ofRotate(-90);
		turtle[j].render(true);
		ofPopMatrix();
	}


}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}
