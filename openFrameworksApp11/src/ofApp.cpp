#include "ofApp.h"
#include "game.h"
#include <cstdlib>
//--------------------------------------------------------------
// got timing idea/code from: https://github.com/OneLoneCoder/videos/blob/master/OneLoneCoder_Tetris.cpp
void ofApp::setup() {
	tetris = game();
	ofSetBackgroundColor(ofColor::black);
	tetris.setup();
}

//--------------------------------------------------------------
void ofApp::update() {
	tetris.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
	tetris.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	tetris.keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	tetris.mousePressed(x, y, button);
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
