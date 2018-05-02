#pragma once
#include <array>
#include "ofMain.h"
#include "tetromino.h"


class game {
private:
	std::vector<std::vector<ofColor>> board;
	int lines_cleared;
	int score_;
	tetromino current;
	tetromino upcoming;
	int xPos;
	int yPos;
	int nPieceCount;
	ofRectangle pauseButton;
	ofRectangle directionsButton;
	ofRectangle restartButton;
	ofRectangle exitButton;
	ofSoundPlayer backgroundMusic;
	ofSoundPlayer levelUpSound;
	ofSoundPlayer tone;
	bool isPaused;
	bool isGameOver;
	bool needDirections;
	bool isBeginning;
	int nSpeed = 20;
	int nSpeedCount = 0;
public:
	game(); 
	void setup();
	void update();
	void draw();
	void keyReleased(int key);
	void mousePressed(int x, int y, int button);
private:
	void reset();
	bool ifInLeftBound();
	bool ifInRightBound();
	bool checkIfAtBottom(int x, int y);
	bool checkIfGameOver();
	void clearLines();
	bool checkIfFullLine(int j_index);
	void makeNewShape();
	void drawBeginningScreen();
	void drawGame();
	void drawPauseScreen();
	void drawGameOverScreen();
	void drawDirections();
	void drawPauseButton();
	void drawDirectionsButton();
	void drawRestartButton();
	void drawExitButton();
	void drawBoundary();
	void addCurrentToBoard();
	bool checkOverlap(int x, int y);
	void drawGameInfo();
	void drawProjection();
};

int const nGameboard_width = 10;
int const nGameboard_height = 18;
int const boundary_weight = 1;
int const boundary_scale = 10;
//ofColor const boundary_color = ofColor::white;
int const nGrid_scale = 30;