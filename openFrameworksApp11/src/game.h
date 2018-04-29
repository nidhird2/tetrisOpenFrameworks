#pragma once
#include <array>
#include "ofMain.h"
#include "tetromino.h"


class game {
public:
	std::vector<std::vector<ofColor>> board;
	int lines_cleared;
	int score_;
	tetromino current;
	tetromino upcoming;
	int xPos;
	int yPos;
public:
	game();
	bool ifInLeftBound();
	bool ifInRightBound();
	bool checkBottomCollision(int x, int y);
	bool isGameOver();
	void clearLines();
	bool checkIfFullLine(int j_index);
	void forceShapeDown();
	void makeNewShape();
	void keyPressed(int key);
	void draw();
	void drawBoundary();
	void addCurrentToBoard();
	bool checkOverlap(int x, int y);
	void drawGameInfo();
};

int const nGameboard_width = 10;
int const nGameboard_height = 18;
int const boundary_weight = 1;
int const boundary_scale = 10;
//ofColor const boundary_color = ofColor::white;
int const nGrid_scale = 25;