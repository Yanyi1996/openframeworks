#include "FunkyTriangleSystem.h"

//--------------------------------------------------------------
FunkyTriangleSystem::FunkyTriangleSystem() {
	pointNum = 50;
}

//--------------------------------------------------------------
void FunkyTriangleSystem::setup(){

    for (int i=0; i<pointNum; i++){
        triangulation.addPoint(glm::vec2(ofRandomWidth(), ofRandomHeight())); // add random points in the triangulation object of ofxDelaunay
    }
    triangulation.triangulate(); // calculate the triangulation!

	for (int g = 0; g < triangulation.getNumTriangles(); g++) { // loop over the triangles
		vector <glm::vec2> pts = getTriangle(g);             // extract the vector with 3 points
		FunkyTriangle tri;
		tri.setup(pts[0], pts[1], pts[2]);
		tris.push_back(tri);
	}

}

//--------------------------------------------------------------
void FunkyTriangleSystem::update(){

	for (int i = 0; i < tris.size(); i++) {

		tris[i].update();

	}


}

//--------------------------------------------------------------
void FunkyTriangleSystem::draw(){
    ofNoFill();
	ofSetLineWidth(5);
    ofSetColor(ofColor::forestGreen);
    //triangulation.triangleMesh.drawWireframe(); //draw the wireframe for debugging purposes

    ofFill();
	for (int i = 0; i < tris.size(); i++) {

		tris[i].draw();

	}

    // what's important for us is to loop over the triangles and extract them. In this case
    // I wrote a helper function getTriangle(int i) which when you loop over all triangles
    // extracts the 3 points making each one and stores them in a vector called pts.
    // In this example I use pts to draw a triangle. You should use the data of the points
    // to create a FunkyTriangle object using your custom FunkyTriangle class. Create a
    // setup() function in the class to pass it the initial parameters. You'll also need a draw()
    // and later on an update(). Start by making 1 FunkyTriangle Object that has some behavior (it
    // goes from black to white and then back to white. Then create a vector of FunkyTriangles.
    // For the more daring, create a FunkyTriangleSystem so that you hide the vector and these loops
    // that might get a bit too complex after a while. See the code provided in class. It's very
    // similar to that, only you don't draw balls, you draw triangles.

}

//--------------------------------------------------------------
// custom function that takes an index and returns the coordinates of the triangle we refer to
vector <glm::vec2> FunkyTriangleSystem::getTriangle(int i){
    int pA = triangulation.triangleMesh.getIndex(i*3);
    int pB = triangulation.triangleMesh.getIndex(i*3+1);
    int pC = triangulation.triangleMesh.getIndex(i*3+2);

    glm::vec2 pointA = triangulation.triangleMesh.getVertex(pA);
    glm::vec2 pointB = triangulation.triangleMesh.getVertex(pB);
    glm::vec2 pointC = triangulation.triangleMesh.getVertex(pC);

    vector <glm::vec2> points;
    points.push_back(pointA);
    points.push_back(pointB);
    points.push_back(pointC);
    return points;
}

//--------------------------------------------------------------
void FunkyTriangleSystem::addTri() {
	//glm::vec2 p1 = glm::vec2(ofRandomWidth, ofRandomHeight);
	//glm::vec2 p2 = glm::vec2(ofRandomWidth, ofRandomHeight);
	//glm::vec2 p3 = glm::vec2(ofRandomWidth, ofRandomHeight);

	//FunkyTriangle tri;
	//tri.setup(p1,p2,p3);
	//tris.push_back(tri);
}

//--------------------------------------------------------------
void FunkyTriangleSystem::clear() {
	//triangulation.reset();
	//tris.clear();
}
