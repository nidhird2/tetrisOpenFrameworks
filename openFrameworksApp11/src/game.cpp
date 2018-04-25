#include "game.h"
#include <array>
#include <vector>

game::game() {
	board = std::vector <std::vector <ofColor>>(nGameboard_width, std::vector <ofColor>(nGameboard_height));
	current = tetromino();
	lines_cleared = 0;
	score_ = 0;
	xPos = nGameboard_width/2;
	yPos = 0;
}

bool game::CheckLeftCollision(int x, int y) {
	std::vector<std::vector<bool>> reference = current.getOrientation();
	if (x <= -4) {
		return true;
	} else if (x < 0) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (reference[i][j] == true && (x + i) < 0) {
					return true;
				}
			}
		}
	} else if (checkOverlap(xPos - 1, yPos)) {
		return true;
	}
	return false;
}

bool game::CheckRightCollision(int x, int y) {
	if (x > nGameboard_width) {
		return true;
	} 
	else if (x > nGameboard_width - 4) {
		std::vector<std::vector<bool>> reference = current.getOrientation();
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (reference[i][j] == true && (x + i) >= nGameboard_width) {
					return true;
				}
			}
		}
	}
	else if (checkOverlap(xPos + 1, yPos)) {
		return true;
	}
	return false;
}

bool game::CheckBottomCollision(int x, int y) {
	if (y > nGameboard_height) {
		return true;
	}
	std::vector<std::vector<bool>> reference = current.getOrientation();
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (reference[i][j] == true && (yPos + j >= nGameboard_height - 1)) {
				return true;
			}
		}
	} 
	if (checkOverlap(xPos, yPos + 1)) {
		return true;
	}
	return false;
}

bool game::IsGameOver() {
	for (int j = 0; j < nGameboard_width; j++) {
		if (board[0][j] != ofColor::white) {
			return true;
		}
	}
	return false;
}

void game::ClearLines() {

}

void game::ForceShapeDown() {
	KeyPressed(OF_KEY_DOWN);
}

void game::MakeNewShape() {
		current = tetromino();
		xPos = nGameboard_width / 2;
		yPos = 0;
}

void game::KeyPressed(int key) {
	if (key == OF_KEY_UP) {
		current.rotate();
	}
	else if (key == OF_KEY_LEFT) {
		if (!CheckLeftCollision(xPos - 1, yPos)) {
			xPos--;
		}
	}
	else if (key == OF_KEY_RIGHT) {
		if (!CheckRightCollision(xPos + 1, yPos)) {
			xPos++;
		}
	}
	else if (key == OF_KEY_DOWN) {
		if (!CheckBottomCollision(xPos, yPos + 1)) {
			yPos++;
		}
		else {
			addCurrentToBoard();
			MakeNewShape();
		}
	}
}

void game::draw() {
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++)	{
			if (board[i][j] != ofColor::white) {
				ofSetColor(board[i][j]);
				ofDrawRectangle(i*nGrid_scale, j*nGrid_scale, nGrid_scale, nGrid_scale);
			}
		}
	}
	current.draw(xPos, yPos, nGrid_scale);
}

void game::addCurrentToBoard() {
	std::vector<std::vector<bool>> reference = current.getOrientation();
	int color_index = current.getColorIndex();

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (reference[i][j] == true) {
				board[xPos + i][yPos + j] = colors[color_index];
			}
		}
	}
}

bool game::checkOverlap(int x, int y) {
	std::vector<std::vector<bool>> reference = current.getOrientation();
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (reference[i][j] == true && ((x + i) > 0) && ((x + i) < nGameboard_width) && ((y+j) < nGameboard_height) && board[x+i][y+j] != ofColor::white) {
				return true;
			}
		}
	}
	return false;
}



