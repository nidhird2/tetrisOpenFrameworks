#pragma once
#include <array>
#include "ofMain.h"
#include "tetromino.h"


class game {
public:
	std::vector<std::vector<ofColor>> board;
	int lines_cleared;
	int score_;
	bool make_new_shape;
	tetromino current;
	int xPos;
	int yPos;
public:
	game();
	bool CheckLeftCollision(int x, int y);
	bool CheckRightCollision(int x, int y);
	bool CheckBottomCollision(int x, int y);
	bool IsGameOver();
	void ClearLines();
	void ForceShapeDown();
	void MakeNewShape();
	void KeyPressed(int key);
	void draw();
	void addCurrentToBoard();
};

int const nGameboard_width = 10;
int const nGameboard_height = 18;
int const nGrid_scale = 25;