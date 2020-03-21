#include "ofApp.h"
#include "ofxPS3EyeGrabber.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(125);
    ofSetFrameRate(60);
	//video.setDeviceID(0);
    //video.setDesiredFrameRate(60);
    //video.initGrabber(640, 480);
    debug = true;

	

	// Set the custom ofxPS3EyeGrabber.
	video.setGrabber(std::make_shared<ofxPS3EyeGrabber>());

	// These are all settings that can be set for any ofVideoGrabber.
	// grabber.setDeviceID(0x00000000);

	// The native pixel format for the ofxPS3EyeGrabber is a Bayer pattern
	// (it will look black and white).
	//grabber.setPixelFormat(OF_PIXELS_NATIVE); // not needed
	video.setDesiredFrameRate(75);
	video.setup(640, 480);

	// These are examples of ofxPS3EyeGrabber-specific paramaters.
	// These must be set after the grabber is set up.
	video.getGrabber<ofxPS3EyeGrabber>()->setAutogain(false);
	video.getGrabber<ofxPS3EyeGrabber>()->setAutoWhiteBalance(false);

	myPartSys.setupAsGrid(30,2,150);

}

//--------------------------------------------------------------
void ofApp::update(){
	

	video.update();		//Decode the new frame if needed
	myPartSys.update();

	//Do computing only if the new frame was obtained
	if ( video.isFrameNew() ) {
		//Store the previous frame, if it exists till now
		if ( grayImage.bAllocated ) {
			grayImagePrev = grayImage;
		}

		//Getting a new frame
		image.setFromPixels( video.getPixels() );
		image.mirror(false, true);
		grayImage = image; //Convert to grayscale image

		//Do processing if grayImagePrev is initialised
		if ( grayImagePrev.bAllocated ) {
			//Get absolute difference
			diff.absDiff( grayImage, grayImagePrev );

			//We want to amplify the difference to obtain
			//better visibility of motion
			//We do it by multiplication. But to do it, we
			//need to convert diff to float image first
			diffFloat = diff;	//Convert to float image
			diffFloat *= 5.0;	//Amplify the pixel values (original = 5.0)

			//Update the accumulation buffer
			if ( !bufferFloat.bAllocated ) {
				//If the buffer is not initialized, then
				//just set it equal to diffFloat
				bufferFloat = diffFloat;
			}
			else {
				//Slow damping the buffer to zero
				bufferFloat *= 0.65; //original = 0.85
				//Add current difference image to the buffer

				bufferFloat += diffFloat;
				bufferFloat.erode(); //helps get rid of noise (remove if not needed)
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(255, 255, 255);	//Set the background color
	video.draw(0, 0);

	//Draw only if diffFloat image is ready.
	//It happens when the second frame from the video is obtained
	if (diffFloat.bAllocated) {
		//Get image dimensions
		int w = grayImage.width;
		int h = grayImage.height;

		//Set color for images drawing
		ofSetColor(255, 255, 255);

		//Draw images grayImage,  diffFloat, bufferFloat
		if (debug)
		{
			grayImage.draw(0, 0, w / 2, h / 2);
			diffFloat.draw(w / 2, 0, w / 2, h / 2);
			bufferFloat.draw(0, h / 2, w / 2, h / 2);
		}
		else image.draw(0, 0, ofGetWidth(), ofGetHeight());

		//Draw the image motion areas
		if (debug)
		{
			//Shift and scale the coordinate system
			ofPushMatrix();
			ofTranslate(w / 2, h / 2);
			ofScale(0.5, 0.5);
			//Draw bounding rectangle
			ofSetColor(0, 0, 0);
			ofNoFill();
		}

		//Get bufferFloat pixels
		float *pixels = bufferFloat.getPixelsAsFloats();

		//Scan all pixels
		for (int y = 0; y < h; y += 1)
		{
			for (int x = 0; x < w; x += 1)
			{
				//Get the pixel value
				float value = pixels[x + w * y];
				//If value exceed threshold, then draw pixel
				if (value >= 1.4) {                           //original was 0.9
					if (debug) ofDrawRectangle(x, y, 1, 1);
					//EDIT HERE: this is where you'll be activating
					//the grid locations or generating particles
					//the debug mode draws small black points in the bottom right square
					else {
						myPartSys.activateParticle(x, y);
					}
				}
			}
		}
	}

	//myPartSys.draw();

	//setup blur
	ofFbo::Settings s;
	s.width = ofGetWidth();
	s.height = ofGetHeight();
	s.internalformat = GL_RGBA;
	s.textureTarget = GL_TEXTURE_RECTANGLE_ARB;
	s.maxFilter = GL_LINEAR; GL_NEAREST;
	s.numSamples = 0;
	s.numColorbuffers = 1;
	s.useDepth = false;
	s.useStencil = false;

	gpuBlur.setup(s, false);

	//update blur
	gpuBlur.blurOffset = 40 * ofMap(mouseY, 0, ofGetHeight(), 1, 0, true);
	//gpuBlur.blurOffset = 15;
	gpuBlur.blurPasses = 5 * ofMap(mouseX, 0, ofGetWidth(), 0, 1, true);
	//gpuBlur.blurPasses = 1;
	gpuBlur.numBlurOverlays = 1;
	gpuBlur.blurOverlayGain = 255;
	//draw blur
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	gpuBlur.beginDrawScene();
	myPartSys.draw(); //stuff need to be blurred
	gpuBlur.endDrawScene();

	//blur the fbo
	//blending will be disabled at this stage
	gpuBlur.performBlur();

	//draw the "clean" scene
	//ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	//gpuBlur.drawSceneFBO();

	//overlay the blur on top
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA); //pre-multiplied alpha
	gpuBlur.drawBlurFbo();

	std::stringstream ss;

	ss << " App FPS: " << ofGetFrameRate() << std::endl;
	ss << " Cam FPS: " << video.getGrabber<ofxPS3EyeGrabber>()->getFPS() << std::endl;
	ss << "Real FPS: " << video.getGrabber<ofxPS3EyeGrabber>()->getActualFPS() << std::endl;
	ss << "      id: 0x" << ofToHex(video.getGrabber<ofxPS3EyeGrabber>()->getDeviceId());

	ofDrawBitmapStringHighlight(ss.str(), ofPoint(10, 15));

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    debug = !debug;
}
