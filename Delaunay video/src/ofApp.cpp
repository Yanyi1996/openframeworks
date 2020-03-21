#include "ofApp.h"
using namespace cv;
#include "opencv2/opencv.hpp"

//--------------------------------------------------------------
void ofApp::setup(){
    //ofSetFrameRate(60);
    //video.setDeviceID(0);
    //video.setDesiredFrameRate(60);
    //video.initGrabber(ofGetWidth(),ofGetHeight());
	myPlayer.load("video.mp4");
	//myPlayer.play();
}

//--------------------------------------------------------------
void ofApp::update(){
	//video.update();	//Decode the new frame if needed
	myPlayer.update(); // get all the new frames

	//Do computing only if the new frame was obtained
	if ( myPlayer.isFrameNew() ) {
		//Getting a new frame
		image.setFromPixels( myPlayer.getPixels() );

		//Convert to grayscale image
		grayImage = image;

		//Smoothing image
		blurred = grayImage;
		blurred.blurGaussian( 5 );

		//Thresholding for obtaining binary image
		mask = blurred;
		mask.threshold( ofMap(mouseX, 0, ofGetWidth(), 0, 200) );

        //Getting an inverted mask of image to use in contour finder
        inverted = mask;
        inverted.invert();

        //#### FIND INTERESTING POINTS #####
		Mat imageCV;
        imageCV = cvarrToMat(blurred.getCvImage());
        goodFeaturesToTrack(imageCV, corners, 5000, 0.01, 4); //param 3 is how many points you want to get

		triangulation.reset();
		for (int i = 0; i < corners.size(); i++) {
			triangulation.addPoint(ofPoint(corners[i].x, corners[i].y)); //loop over the corners vector adding each corner to the triangulation
		}
		triangulation.triangulate();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
		ofBackground(255, 255, 255);	//Set the background color

		ofSetColor( 255, 255, 255 );	//Set color for images drawing

        int w = image.width;
        int h = image.height;
		//Original decimated image
		//image.draw(0, 0, w, h);

        //blurred immage
		//blurred.draw( w/2, 0, w/2, h/2);

		//Thresholded image
		//mask.draw( w, 0, w/2, h/2);
		//Inverted image
		//inverted.draw( w/2*3, 0, w/2, h/2);

        //ofTranslate(ofGetWidth()/2-w/2, h/2+10);
        //ofSetColor(0);
        //ofNoFill();
        //ofDrawRectangle(0,0,w,h);

        //draw the interesting points in RED
        //ofSetColor(255,0,0);
        //ofFill();
		//for (int i=0; i<corners.size(); i++) {
        //    ofDrawEllipse(corners[i].x, corners[i].y, 3,3);
        //}

		myPlayer.draw(0,0);
		myPlayer.play();

		//draw triangles
		for (int g = 0; g < triangulation.getNumTriangles(); g++) { // loop over the triangles
			vector <glm::vec2> pts = getTriangle(g);             // extract the vector with 3 points
			// when the length of triangle is smaller than a certain number, it will be drawn
			if ((length(pts[0]-pts[1]) < 50) && (length(pts[0] - pts[2]) < 50) && (length(pts[1] - pts[2]) < 50)) {
				glm::vec2 centre = (pts[0] + pts[1] + pts[2]) / pts.size(); // get centre point of triangle
				ofColor c = image.getPixels().getColor(centre.x, centre.y); //get the pixel color in centre point of every triangle
				ofSetColor(c);
				ofDrawTriangle(pts[0], pts[1], pts[2]);
			}
		}
}

//--------------------------------------------------------------
// custom function that takes an index and returns the coordinates of the triangle we refer to
vector <glm::vec2> ofApp::getTriangle(int i) {
	int pA = triangulation.triangleMesh.getIndex(i * 3);
	int pB = triangulation.triangleMesh.getIndex(i * 3 + 1);
	int pC = triangulation.triangleMesh.getIndex(i * 3 + 2);

	glm::vec2 pointA = triangulation.triangleMesh.getVertex(pA);
	glm::vec2 pointB = triangulation.triangleMesh.getVertex(pB);
	glm::vec2 pointC = triangulation.triangleMesh.getVertex(pC);

	vector <glm::vec2> points;
	points.push_back(pointA);
	points.push_back(pointB);
	points.push_back(pointC);
	return points;
}
