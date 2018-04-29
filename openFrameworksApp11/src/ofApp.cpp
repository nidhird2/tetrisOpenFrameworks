#include "ofApp.h"
#include "game.h"
#include <cstdlib>
//--------------------------------------------------------------
// got timing idea/code from: https://github.com/OneLoneCoder/videos/blob/master/OneLoneCoder_Tetris.cpp
void ofApp::setup() {
	tetris = game();
	ofSetBackgroundColor(ofColor::black);
}

//--------------------------------------------------------------
void ofApp::update() {
	this_thread::sleep_for(30ms);
	nSpeedCount++;
	if (nSpeedCount == nSpeed) {
		nSpeedCount = 0;
		// Update difficulty every 50 pieces
		if (tetris.nPieceCount % 50 == 0) {
			if (nSpeed >= 10) nSpeed--;
		}
		tetris.forceShapeDown();
	}
	tetris.clearLines();
	if (tetris.isGameOver()) {
		ofExit();
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	tetris.drawBoundary();
	tetris.draw();
	tetris.drawGameInfo();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	tetris.keyPressed(key);
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
