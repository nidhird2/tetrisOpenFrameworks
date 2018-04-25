#include "ofApp.h"
#include "game.h"
#include <cstdlib>
//--------------------------------------------------------------
// got timing idea/code from: https://github.com/OneLoneCoder/videos/blob/master/OneLoneCoder_Tetris.cpp
void ofApp::setup() {
	tetris = game();
	ofSetBackgroundColor(ofColor::black);
	tetris.draw();
}

//--------------------------------------------------------------
void ofApp::update() {
	this_thread::sleep_for(50ms);
	nSpeedCount++;
	if (nSpeedCount == nSpeed) {
		nSpeedCount = 0;
		tetris.ForceShapeDown();
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	tetris.draw();
	//tetris.current.draw(tetris.xPos,tetris.yPos,nGrid_scale);
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