#include "game.h"
#include <array>
#include <vector>

game::game() {
	board = std::vector <std::vector<ofColor>>(nGameboard_width, std::vector <ofColor>(nGameboard_height));
	current = tetromino();
	lines_cleared = 0;
	score_ = 0;
	xPos = nGameboard_width/2;
	yPos = 0;
}

bool game::ifInLeftBound() {
	std::vector<std::vector<bool>> reference = current.getOrientation();

	if (xPos - 1 < 0) {
		for (int i = 0; i < reference.size(); i++) {
			for (int j = 0; j < reference[i].size(); j++) {
				if (reference[i][j] == true && (xPos - 1 + i) < 0) {
					return false;
				}
			}
		}
	} 
	return true;
}

bool game::ifInRightBound() {
	std::vector<std::vector<bool>> reference = current.getOrientation();

	if (xPos + 1 > nGameboard_width) {
		return false;
	} else if (xPos + 1 > nGameboard_width - reference.size()) {
		for (int i = 0; i < reference.size(); i++) {
			for (int j = 0; j < reference[i].size(); j++) {
				if (reference[i][j] == true && (xPos + 1 + i) >= nGameboard_width) {
					return false;
				}
			}
		}
	} 
	return true;
}

bool game::checkBottomCollision(int x, int y) {
	if (y >= nGameboard_height) {
		return true;
	}
	std::vector<std::vector<bool>> reference = current.getOrientation();
	
	for (int i = 0; i < reference.size(); i++) {
		for (int j = 0; j < reference[i].size(); j++) {
			if (reference[i][j] == true && (yPos + j >= nGameboard_height - 1)) {
				return true;
			}
		}
	} 
	if(checkOverlap(xPos, yPos + 1)) {
		return true;
	}
	return false;
}

bool game::isGameOver() {
	for (int i = 0; i < nGameboard_width; i++) {
		if (board[i][0] != ofColor::white) {
			return true;
		}
	}
	return false;
}

void game::clearLines() {
	int line_to_be_removed = findFullLineIndex();
	while (line_to_be_removed >= 0) {
		for (int j = line_to_be_removed; j >= 1; j--) {
			for (int i = 0; i<nGameboard_width; i++) {
				board[i][j] = board[i][j - 1];
			}
		}
		for (int i = 0; i < nGameboard_width; i++) {
			board[i][0] = 0;
		}
	}
}

int game::findFullLineIndex() {
	int full_line_index = -1;
	bool streak = true;
	for (int j = 0; j < nGameboard_height; j++) {
		streak = true;
		for (int i = 0; i < nGameboard_width; i++) {
			if (board[i][j] != ofColor::white) {
				streak = false;
				break;
			}
			if (streak) {
				return j;
			}
		}
	}
	return -1;
}


void game::forceShapeDown() {
	keyPressed(OF_KEY_DOWN);
}

void game::makeNewShape() {
		current = tetromino();
		xPos = nGameboard_width / 2;
		yPos = 0;
}

void game::keyPressed(int key) {
	if (key == OF_KEY_UP) {
		current.rotate();
		if (!ifInLeftBound() || !ifInRightBound() || checkOverlap(xPos, yPos)) {
			current.rotate();
			current.rotate();
			current.rotate();
		}
	}
	else if (key == OF_KEY_LEFT && ifInLeftBound() && !checkOverlap(xPos - 1, yPos)){
			xPos--;
	}
	else if (key == OF_KEY_RIGHT && ifInRightBound() && !checkOverlap(xPos + 1, yPos)) {
			xPos++;
	}
	else if (key == OF_KEY_DOWN) {
		if (!checkBottomCollision(xPos, yPos + 1)) {
			yPos++;
		}else {
			addCurrentToBoard();
			makeNewShape();
		}
	}
	else if (key == ' ') {
		while (!checkBottomCollision(xPos, yPos)) {
			keyPressed(OF_KEY_DOWN);
		}
	}
}

void game::draw() {
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++)	{
			if (board[i][j] != ofColor::white) {
				ofSetColor(board[i][j]);
				ofDrawRectangle(nGrid_scale*(i + boundary_weight), nGrid_scale*(j + boundary_weight), nGrid_scale, nGrid_scale);
			}
		}
	}
	current.draw(xPos + boundary_weight, yPos + boundary_weight, nGrid_scale);
}

void game::addCurrentToBoard() {
	std::vector<std::vector<bool>> reference = current.getOrientation();
	int color_index = current.getColorIndex();

	for (int i = 0; i < reference.size(); i++) {
		for (int j = 0; j < reference[i].size(); j++) {
			if (reference[i][j] == true) {
				board[xPos + i][yPos + j] = colors[color_index];
			}
		}
	}
}

bool game::checkOverlap(int x, int y) {
	std::vector<std::vector<bool>> reference = current.getOrientation();
	for (int i = 0; i < reference.size(); i++) {
		for (int j = 0; j < reference[i].size(); j++) {
			if (reference[i][j] == true && ((x + i) >= 0) && ((x + i) < nGameboard_width) && ((y+j) < nGameboard_height) && (board[x+i][y+j] != ofColor::white)) {
				return true;
			}
		}
	}
	return false;
}
void game::drawBoundary() {
	ofSetColor(ofColor::white);
	//draws vertical boundaries
	for (int j = 0; j < nGameboard_height + boundary_weight; j++) {
		ofDrawRectangle(0, j * nGrid_scale, nGrid_scale, nGrid_scale);
		ofDrawRectangle((nGameboard_width + boundary_weight) * nGrid_scale, j * nGrid_scale, nGrid_scale, nGrid_scale);
	}
	//draw bottom boundary
	for (int i = 0; i <= nGameboard_width + boundary_weight ; i++) {
		ofDrawRectangle(i * nGrid_scale, nGrid_scale * (nGameboard_height + boundary_weight), 
			nGrid_scale, nGrid_scale);
	}
}



