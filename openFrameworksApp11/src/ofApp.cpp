#include "ofApp.h"
#include "game.h"
#include <cstdlib>
//--------------------------------------------------------------
void ofApp::setup() {
	tetris = game();
	frameNumber = 0;
	ofSetFrameRate(60);
	ofSetBackgroundColor(ofColor::black);
}

//--------------------------------------------------------------
void ofApp::update() {
	tetris.draw();
	if ((ofGetElapsedTimeMillis() - frameNumber > SPEED)) {
		tetris.ForceShapeDown();
	}
	frameNumber = ofGetElapsedTimeMillis();
}

//--------------------------------------------------------------
void ofApp::draw() {
	//tetromino new_shape = tetromino();
	//new_shape.draw(150, 0, 15);

	//game1.current.draw(150, 0, 30);
	tetris.current.draw(tetris.xPos, tetris.yPos, nGrid_scale);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	//game1.draw();
	//tetris.KeyPressed(key);
	//game1.draw();



}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	tetris.KeyPressed(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}