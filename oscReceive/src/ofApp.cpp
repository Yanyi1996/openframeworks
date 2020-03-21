#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// listen on the given port
	cout << "listening for osc messages on port " << PORT << "\n";
	receiver.setup(PORT);

	mouseX = 0;
	mouseY = 0;
	mouseButtonState = "";

	ofBackground(30, 30, 130);
	ofSetFrameRate(60);
	phase = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    if (messageBuffer.size()>maxBufferSize) messageBuffer.pop_back();

	// check for waiting messages
	while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(m);

		// 1. mobile phone controls arc
		//if (m.getAddress() == "/gyrosc/accel") {
			// moving is controlled by messageBuffer gyroscope
			//phase += m.getArgAsFloat(0)*5;

			//mouseX = m.getArgAsFloat(1);
			//mouseY = m.getArgAsFloat(2);
		//}

		// 2. remote paint receiver
		if (m.getAddress() == "/mouse/position") {
			mouseX = m.getArgAsInt(0);
			mouseY = m.getArgAsInt(1);
		}

		else if (m.getAddress() == "/coords") {
			for (int i = 0; i < m.getNumArgs(); i += 2) {
				posX.push_back(m.getArgAsInt(i));
				posY.push_back(m.getArgAsInt(i + 1));
			}
		}

		// check for mouse button message
		else if (m.getAddress() == "/mouse/button") {
			//the single argument is a string
			mouseButtonState = m.getArgAsString(1);
		}
		else if (m.getAddress() == "/test") {
			string msg_string;
            myNum = m.getArgAsInt(0);
            myNum2 = m.getArgAsFloat(1);
            myString = m.getArgAsString(2);
            myTime = m.getArgAsFloat(3);
            msg_string = m.getAddress() + " " + ofToString(myNum) + " " + ofToString(myNum2) + " " + myString + " " + ofToString(myTime);// + " " + msg_string;
            messageBuffer.push_front(msg_string);
		}
        else {
            // unrecognized message: display on the bottom of the screen
            messageBuffer.push_front(m.getAddress() + ": UNRECOGNIZED MESSAGE");
        }
	}
}


//--------------------------------------------------------------
void ofApp::draw(){
	string buf;
	buf = "listening for osc messages on port" + ofToString(PORT);
	ofDrawBitmapString(buf, 10, 20);

	// draw mouse state
	buf = "mouse: " + ofToString(mouseX, 4) +  " " + ofToString(mouseY, 4);
	ofDrawBitmapString(buf, 430, 20);
	ofDrawBitmapString(mouseButtonState, 580, 20);

    // read the buffer
	for(int i = 0; i < messageBuffer.size(); i++){
		ofDrawBitmapString(messageBuffer[i], 10, 40 + 15 * i);
	}

	// 1. draw arcs
	//int numOfLines = 40;
	//float spacing = 8; // spacing between arcs

	//for (int i = 0; i < numOfLines; i++)
	//{
	//	int position = phase + spacing * i;
	//	float phaseDiff = 8;
	//	arc(phase + phaseDiff * i, spacing + spacing * i);
	//}

	// 2. draw painter's line
	if (posX.size() > 0) {
		for (int i = 0; i < posX.size() - 1; i++) {
			ofDrawLine(posX[i], posY[i], posX[i + 1], posY[i + 1]);
		}
	}
}

//--------------------------------------------------------------
void ofApp::arc(float p, float radius) {
	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() + 1);

	ofPath path;
	float startAngle = 180;
	float endAngle = ofMap(sin(ofDegToRad(p)), -1, 1, 180, 360) + 1;
	path.arc(0, 0, radius, radius, startAngle, endAngle);
	path.setCircleResolution(100);
	path.setStrokeWidth(3);
	path.setFilled(false);

	//optional cool colors :)
	ofColor red = ofColor::red;
	ofColor blue = ofColor::blue;
	float percent = ofMap(endAngle, startAngle, 360, 0, 1, true);
	ofColor c = red.getLerped(blue, percent);
	path.setColor(c);
	//end of optional colors

	path.draw();
	ofPopMatrix();
}
