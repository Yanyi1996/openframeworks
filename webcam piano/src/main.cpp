#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){
	ofGLWindowSettings settings;
	settings.setSize(640, 480);
	ofCreateWindow(settings);
	return ofRunApp(std::make_shared<ofApp>());

	ofSetupOpenGL(640,480, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new ofApp());

}
