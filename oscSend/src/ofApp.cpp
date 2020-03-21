#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(40, 100, 40);
	// open an outgoing connection to HOST:PORT
	sender.setup(HOST, PORT);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	// display instructions
	string buf;
	buf = "sending osc messages to" + string(HOST) + ofToString(PORT);
	ofDrawBitmapString(buf, 10, 20);
	ofDrawBitmapString("move the mouse to send osc message [/mouse/position <x> <y>]", 10, 50);
	ofDrawBitmapString("click to send osc message [/mouse/button <button> <\"up\"|\"down\">]", 10, 65);
	ofDrawBitmapString("press A to send osc message [/test 1 3.5 hello <time>]", 10, 80);

	// display lines
	/*if (posX.size() > 0) {
		for (int i = 0; i < posX.size() - 1; i++) {
			ofDrawLine(posX[i], posY[i], posX[i + 1], posY[i + 1]);
		}
	}*/
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	//if(key == 'a' || key == 'A'){
	//	ofxOscMessage m;
	//	m.setAddress("/test");
	//	m.addIntArg(1);
	//	m.addFloatArg(3.5f);
	//	m.addStringArg("hello");
	//	m.addFloatArg(ofGetElapsedTimef());
	//	sender.sendMessage(m, false);
	//}

	//else if (key == 'c' || key == 'C') {
	//	posX.clear();
	//	posY.clear();
	//}

	//else if (key == 's' || key == 'S') {
	//	ofxOscMessage m;
	//	m.setAddress("/coords");
	//	for (int i = 0; i < posX.size(); i++) {
	//		m.addIntArg(posX[i]);
	//		m.addIntArg(posY[i]);
	//	}
	//	sender.sendMessage(m, false);
	//}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
	ofxOscMessage m;
	m.setAddress("/processing/squarePosition");
	m.addIntArg(x);
	m.addIntArg(y);
	sender.sendMessage(m, false);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	/*ofxOscMessage m;
	m.setAddress("/mouse/button");
	m.addIntArg(button);
	m.addStringArg("down");
	sender.sendMessage(m, false);*/
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	/*ofxOscMessage m;
	m.setAddress("/mouse/button");
	m.addIntArg(button);
	m.addStringArg("up");
	sender.sendMessage(m, false);*/
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
	/*posX.push_back(mouseX);
	posY.push_back(mouseY);*/
}


