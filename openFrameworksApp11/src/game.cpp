#include "game.h"
#include <array>
#include <vector>
#include <string>

game::game() {
	board = std::vector <std::vector<ofColor>>(nGameboard_width, std::vector <ofColor>(nGameboard_height));
	current = tetromino();
	upcoming = tetromino();
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
	if (checkOverlap(xPos, yPos)) {
		return true;
	}
	return false;
}

void game::clearLines() {
	for (int j = nGameboard_height - 1; j >= 0; j--) {
		if (checkIfFullLine(j)) {
			lines_cleared++;
			for (int current = j; current >= 1; current--) {
				for (int i = 0; i<nGameboard_width; i++) {
					board[i][current] = board[i][current - 1];
				}
			}
			for (int i = 0; i < nGameboard_width; i++) {
				board[i][0] = ofColor::white;
			}
			if(j != nGameboard_height) {
				j++;
			}
		}
	}
}

bool game::checkIfFullLine(int j_index) {
	for (int i = 0; i < nGameboard_width; i++) {
		if (board[i][j_index] == ofColor::white) {
			return false;
		}
	}
	return true;
}


void game::forceShapeDown() {
	keyPressed(OF_KEY_DOWN);
}

void game::makeNewShape() {
		current = upcoming;
		upcoming = tetromino();
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
				ofDrawRectangle((nGrid_scale*i) + (boundary_scale *boundary_weight), nGrid_scale*j, 
					nGrid_scale, nGrid_scale);
			}
		}
	}
	current.draw(xPos, yPos, nGrid_scale, boundary_scale *boundary_weight);
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
			if (reference[i][j] == true && ((x + i) >= 0) && ((x + i) < nGameboard_width) && 
				((y+j) < nGameboard_height) && (board[x+i][y+j] != ofColor::white)) {
				return true;
			}
		}
	}
	return false;
}
void game::drawBoundary() {
	ofSetColor(ofColor::white);
	//draws vertical boundaries
	int right_most_index = (nGrid_scale * nGameboard_width) + (boundary_scale * boundary_weight);
	for (int j = 0; j < nGameboard_height; j++) {
		ofDrawRectangle(0, j * nGrid_scale, boundary_scale * boundary_weight, nGrid_scale);
		ofDrawRectangle(right_most_index, j * nGrid_scale, boundary_scale * boundary_weight, nGrid_scale);
		
	}
	//draw bottom boundary
	for (int i = 0; i < nGameboard_width; i++) {
		int current_x_index = (i * nGrid_scale) + (boundary_weight * boundary_scale);
		ofDrawRectangle(current_x_index , nGrid_scale * nGameboard_height , nGrid_scale, 
			boundary_scale * boundary_weight);
	}
	//draw corners
	ofDrawRectangle(0, nGameboard_height*nGrid_scale, boundary_scale * boundary_weight, 
		boundary_scale * boundary_weight);
	ofDrawRectangle(right_most_index, nGameboard_height*nGrid_scale, boundary_scale * boundary_weight,
		boundary_scale * boundary_weight);
}
void game::drawGameInfo() {
	ofDrawBitmapString("Lines cleared: " + std::to_string(lines_cleared), 
		1.25 * ((nGameboard_width*nGrid_scale) + (boundary_scale*boundary_weight)),
		0.45 * nGameboard_height * nGrid_scale);
	ofDrawBitmapString("Score: " + std::to_string(score_),
		1.25 * ((nGameboard_width*nGrid_scale) + (boundary_scale*boundary_weight)),
		0.50 * nGameboard_height * nGrid_scale);

	upcoming.draw(1.20 * nGameboard_width, 0.6 * nGameboard_height, nGrid_scale, 0);

	ofDrawBitmapString("Upcoming: ",
		1.25 * ((nGameboard_width*nGrid_scale) + (boundary_scale*boundary_weight)),
		0.55 * nGameboard_height * nGrid_scale);
}



