#include "game.h"
#include <array>
#include <vector>
#include <string>
#include <fstream>

game::game() {
	board = std::vector <std::vector<ofColor>>(nGameboard_width, std::vector <ofColor>(nGameboard_height));
	current = tetromino();
	upcoming = tetromino();
	lines_cleared = 0;
	score_ = 0;
	xPos = (nGameboard_width - nTetromino_size) / 2;
	yPos = 0 - (nTetromino_size/2);
	nPieceCount = 1;
	isPaused = false;
	isGameOver = false;
	needDirections = false;
	isBeginning = true;
	loadHighScores();
}

void game::setup() {
	backgroundMusic.load("tetrismusic.wav");
	levelUpSound.load("powerUpSound.wav");
	tone.load("tone1.wav");
	verdana.load("verdana.ttf", 10, true, true);
	verdana.setLineHeight(18.0f);
	verdana.setLetterSpacing(1.037);
	verdana30.load("verdana.ttf", 30, true, true);
	verdana30.setLineHeight(34.0f);
	verdana30.setLetterSpacing(1.035);
	backgroundMusic.setLoop(true);
	backgroundMusic.play();
	pauseButton.set(1.3 * ((nGameboard_width*nGrid_scale) + (boundary_scale*boundary_weight)),
		0.2 * nGameboard_height * nGrid_scale, 2 * nGrid_scale, nGrid_scale);
	directionsButton.set(1.3 * ((nGameboard_width*nGrid_scale) + (boundary_scale*boundary_weight)),
		0.3 * nGameboard_height * nGrid_scale, 2 * nGrid_scale, nGrid_scale);
	restartButton.set(.4 * ((nGameboard_width*nGrid_scale) + (boundary_scale*boundary_weight)),
		0.3 * nGameboard_height * nGrid_scale, 2 * nGrid_scale, nGrid_scale);
	exitButton.set(.4 * ((nGameboard_width*nGrid_scale) + (boundary_scale*boundary_weight)),
		0.4 * nGameboard_height * nGrid_scale, 2 * nGrid_scale, nGrid_scale);
}
void game::update() {
	if (!isPaused && !isGameOver && !needDirections && !isBeginning) {
		this_thread::sleep_for(30ms);
		nSpeedCount++;
		if (nSpeedCount == nSpeed) {
			nSpeedCount = 0;
			// Update difficulty every 50 pieces
			if (nPieceCount % 50 == 0) {
				if (nSpeed >= 10) {
					levelUpSound.play();
					nSpeed--;
				}
			}
			keyReleased(OF_KEY_DOWN);
		}
		clearLines();
		if (checkIfGameOver()) {
			isGameOver = true;
		}
	}
}
void game::draw() {
	ofSetBackgroundColor(ofColor::black);
	if (!isPaused && !isGameOver && !needDirections && !isBeginning) {
		drawGame();
	}
	else if (isBeginning) {
		drawBeginningScreen();
	}
	else if (isPaused) {
		drawPauseScreen();
	} 
	else if (needDirections) {
		drawDirections();
	}
	else {
		drawGameOverScreen();
	}
}
void game::keyReleased(int key) {
	if (isBeginning) {
		isBeginning = false;
		return;
	}
	if (key == OF_KEY_UP) {
		current.rotate();
		if (!ifInLeftBound() || !ifInRightBound() || checkOverlap(xPos, yPos)) {
			current.rotate();
			current.rotate();
			current.rotate();
		}
	}
	else if (key == OF_KEY_LEFT && ifInLeftBound() && !checkOverlap(xPos - 1, yPos)) {
		xPos--;
	}
	else if (key == OF_KEY_RIGHT && ifInRightBound() && !checkOverlap(xPos + 1, yPos)) {
		xPos++;
	}
	else if (key == OF_KEY_DOWN) {
		if (!checkIfAtBottom(xPos, yPos)) {
			yPos++;
		}
		else {
			tone.play();
			addCurrentToBoard();
			makeNewShape();
		}
	}
	else if (key == ' ') {
		while (!checkIfAtBottom(xPos, yPos)) {
			keyReleased(OF_KEY_DOWN);
		}
	}
}


void game::mousePressed(int x, int y, int button) {
	if (pauseButton.inside(x, y)) {
		isPaused = !isPaused;
	} else if(directionsButton.inside(x, y)) {
		needDirections = !needDirections;
	}
	else if (restartButton.inside(x, y)) {
		reset();
	} 
	else if (exitButton.inside(x, y)) {
		ofExit();
	}
}

void game::reset() {
	board = std::vector <std::vector<ofColor>>(nGameboard_width, std::vector <ofColor>(nGameboard_height));
	current = tetromino();
	upcoming = tetromino();
	lines_cleared = 0;
	score_ = 0;
	xPos = (nGameboard_width - nTetromino_size) / 2;
	yPos = 0 - (nTetromino_size / 2);
	nPieceCount = 1;
	isPaused = false;
	isGameOver = false;
	needDirections = false;
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

bool game::checkIfAtBottom(int x, int y) {
	if (y >= nGameboard_height) {
		return true;
	}
	std::vector<std::vector<bool>> reference = current.getOrientation();
	
	for (int i = 0; i < reference.size(); i++) {
		for (int j = 0; j < reference[i].size(); j++) {
			if (reference[i][j] == true && (y + 1 + j >= nGameboard_height)) {
				return true;
			}
		}
	} 
	if(checkOverlap(x, y + 1)) {
		return true;
	}
	return false;
}

bool game::checkIfGameOver() {
	for (int i = 0; i < nGameboard_width; i++) {
		if (board[i][0] != ofColor::white) {
			return true;
		}
	}
	//if (checkOverlap(xPos, yPos)) {
	//	return true;
	//}
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

void game::makeNewShape() {
	nPieceCount++;
	current = upcoming;
	upcoming = tetromino();
	xPos = (nGameboard_width - nTetromino_size) / 2;
	yPos = 0 - (nTetromino_size / 2);
}

void game::drawGame() {
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++)	{
			if (board[i][j] != ofColor::white) {
				ofSetColor(board[i][j]);
				ofDrawRectangle((nGrid_scale*i) + (boundary_scale *boundary_weight), nGrid_scale*j, 
					nGrid_scale, nGrid_scale);
			}
		}
	}
	drawProjection();
	current.draw(xPos, yPos, nGrid_scale, boundary_scale *boundary_weight);
	drawBoundary();
	drawGameInfo();
	drawPauseButton();
	drawDirectionsButton();
}

void game::addCurrentToBoard() {
	std::vector<std::vector<bool>> reference = current.getOrientation();
	int color_index = current.getColorIndex();

	for (int i = 0; i < reference.size(); i++) {
		for (int j = 0; j < reference[i].size(); j++) {
			if (reference[i][j] == true) {
				if (xPos + i < 0 || yPos + j < 0) {
					isGameOver = true;
					return;
				}
				board[xPos + i][yPos + j] = colors[color_index];
			}
		}
	}
}

bool game::checkOverlap(int x, int y) {
	std::vector<std::vector<bool>> reference = current.getOrientation();
	for (int i = 0; i < reference.size(); i++) {
		for (int j = 0; j < reference[i].size(); j++) {
			if (reference[i][j] == true && ((x + i) >= 0) && ((x + i) < nGameboard_width && (y +j) >= 0) && 
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
	verdana.drawString("Lines cleared: " + std::to_string(lines_cleared), 
		1.25 * ((nGameboard_width*nGrid_scale) + (boundary_scale*boundary_weight)),
		0.45 * nGameboard_height * nGrid_scale);
	verdana.drawString("Score: " + std::to_string(score_),
		1.25 * ((nGameboard_width*nGrid_scale) + (boundary_scale*boundary_weight)),
		0.50 * nGameboard_height * nGrid_scale);

	upcoming.draw(1.20 * nGameboard_width, 0.6 * nGameboard_height, nGrid_scale, 0);

	verdana.drawString("Upcoming: ",
		1.25 * ((nGameboard_width*nGrid_scale) + (boundary_scale*boundary_weight)),
		0.55 * nGameboard_height * nGrid_scale);
}

void game::drawProjection() {
	int x = xPos;
	int y = yPos;
	while (!checkIfAtBottom(x, y)) {
		y++;
	}
	current.drawTranslucent(x, y, nGrid_scale, boundary_scale *boundary_weight);

}
void game::drawBeginningScreen() {
	ofSetColor(ofColor::white);
	verdana.drawString("Welcome to...", 0.5 * ((nGameboard_width*nGrid_scale) + (boundary_scale*boundary_weight)),
		0.25 * nGameboard_height * nGrid_scale);
	ofSetColor(ofColor::red);
	verdana30.drawString("T", 0.35 * ((nGameboard_width*nGrid_scale) + (boundary_scale*boundary_weight)),
		0.35 * nGameboard_height * nGrid_scale);
	ofSetColor(ofColor::blue);
	verdana30.drawString("E", 0.45 * ((nGameboard_width*nGrid_scale) + (boundary_scale*boundary_weight)),
		0.35 * nGameboard_height * nGrid_scale);
	ofSetColor(ofColor::green);
	verdana30.drawString("T", 0.55 * ((nGameboard_width*nGrid_scale) + (boundary_scale*boundary_weight)),
		0.35 * nGameboard_height * nGrid_scale);
	ofSetColor(ofColor::yellow);
	verdana30.drawString("R", 0.65* ((nGameboard_width*nGrid_scale) + (boundary_scale*boundary_weight)),
		0.35 * nGameboard_height * nGrid_scale);
	ofSetColor(ofColor::orange);
	verdana30.drawString("I", 0.75 * ((nGameboard_width*nGrid_scale) + (boundary_scale*boundary_weight)),
		0.35 * nGameboard_height * nGrid_scale);
	ofSetColor(ofColor::mediumPurple);
	verdana30.drawString("S", 0.83* ((nGameboard_width*nGrid_scale) + (boundary_scale*boundary_weight)),
		0.35 * nGameboard_height * nGrid_scale);
	ofSetColor(ofColor::white);
	verdana.drawString("press any key to start...", 0.40 * ((nGameboard_width*nGrid_scale) + 
		(boundary_scale*boundary_weight)), 0.45 * nGameboard_height * nGrid_scale);

}
void game::drawPauseScreen() {
	drawPauseButton();
	ofSetColor(ofColor::white);
	verdana.drawString("G A M E  P A U S E D", 0.25 * ((nGameboard_width*nGrid_scale) + (boundary_scale*boundary_weight)),
		0.20 * nGameboard_height * nGrid_scale);
	drawRestartButton();
	drawExitButton();
	drawHighScores();
}
void game::drawGameOverScreen() {
	updateHighScores();
	ofSetColor(ofColor::white);
	verdana.drawString("G A M E  O V E R", 0.25 * ((nGameboard_width*nGrid_scale) + (boundary_scale*boundary_weight)),
		0.20 * nGameboard_height * nGrid_scale);
	verdana.drawString("YOUR SCORE: "+ std::to_string(score_), 0.25 * ((nGameboard_width*nGrid_scale) + (boundary_scale*boundary_weight)),
		0.25 * nGameboard_height * nGrid_scale);
	drawHighScores();
	drawRestartButton();
	drawExitButton();
}


void game::drawDirections() {
	ofSetBackgroundColor(ofColor::lightGrey);
	drawDirectionsButton();
	ofSetColor(ofColor::blue);
	verdana.drawString("Objective: Keep the board empty by placing blocks.", 0 ,0.20 * nGameboard_height * nGrid_scale);
	verdana.drawString("Everytime a row fills up on the board, it will be", 0, 0.25 * nGameboard_height * nGrid_scale);
	verdana.drawString("erased and your score will increase. The game", 0, 0.30 * nGameboard_height * nGrid_scale);
	verdana.drawString("ends when the block reaches the top of the screen.", 0, 0.35 * nGameboard_height * nGrid_scale);
	ofSetColor(ofColor::red);
	verdana.drawString("CONTROLS:", 0, 0.40 * nGameboard_height * nGrid_scale);
	ofSetColor(ofColor::darkGreen);
	verdana.drawString("UP ARROW KEY: rotates the piece if possible", 0, 0.45 * nGameboard_height * nGrid_scale);
	ofSetColor(ofColor::orange);
	verdana.drawString("LEFT ARROW KEY: shifts pieces left if possible",0, 0.50 * nGameboard_height * nGrid_scale);
	ofSetColor(ofColor::orchid);
	verdana.drawString("RIGHT ARROW KEY: shifts piece right if possible", 0, 0.55 * nGameboard_height * nGrid_scale);
	ofSetColor(ofColor::darkGoldenRod);
	verdana.drawString("DOWN ARROW KEY: shifts piece down if possible", 0, 0.60 * nGameboard_height * nGrid_scale);
	ofSetColor(ofColor::darkMagenta);
	verdana.drawString("SPACEBAR: moves piece as far down as possible", 0, 0.65 * nGameboard_height * nGrid_scale);
}

void game::drawPauseButton() {
	ofSetColor(ofColor::magenta);
	ofRect(pauseButton);
	ofSetColor(ofColor::white);
	verdana.drawString("PAUSE", 1.3* ((nGameboard_width*nGrid_scale) + (boundary_scale*boundary_weight)) +
		(nGrid_scale / 2), (0.2 * nGameboard_height * nGrid_scale) + (nGrid_scale / 2));
}


void game::drawDirectionsButton() {
	ofSetColor(ofColor::coral);
	ofRect(directionsButton);
	ofSetColor(ofColor::white);
	if (!needDirections) {
		verdana.drawString("HELP", 1.3 * ((nGameboard_width*nGrid_scale) + (boundary_scale*boundary_weight)) +
			(nGrid_scale/2), (0.3 * nGameboard_height * nGrid_scale) + (nGrid_scale / 2));
	}
	else {
		verdana.drawString("EXIT", 1.3 * ((nGameboard_width*nGrid_scale) + (boundary_scale*boundary_weight)) +
			(nGrid_scale / 2),(0.3 * nGameboard_height * nGrid_scale) + (nGrid_scale / 2));
	}
}


void game::drawRestartButton() {
	ofSetColor(ofColor::cornflowerBlue);
	ofRect(restartButton);
	ofSetColor(ofColor::white);
	verdana.drawString("RESTART", .4 * ((nGameboard_width*nGrid_scale) + (boundary_scale*boundary_weight)),
		(0.3 * nGameboard_height * nGrid_scale) + (nGrid_scale / 2));
}
void game::drawExitButton() {
	ofSetColor(ofColor::orangeRed);
	ofRect(exitButton);
	ofSetColor(ofColor::white);
	verdana.drawString("EXIT", .4 * ((nGameboard_width*nGrid_scale) + (boundary_scale*boundary_weight)) 
		+ (nGrid_scale / 2),(0.4 * nGameboard_height * nGrid_scale) + (nGrid_scale / 2));
}

void game::drawHighScores() {
	updateHighScores();
	ofSetColor(ofColor::white);
	verdana.drawString("high scores: ", 0.3 * ((nGameboard_width*nGrid_scale) + (boundary_scale*boundary_weight)),
		0.5 * nGameboard_height * nGrid_scale);
	int index = 0;
	for (int i = high_scores.size() - 1; i >= 0; i--) {
		if (high_scores[i] == score_) {
			ofSetColor(ofColor::red);
		}
		else {
			ofSetColor(ofColor::white);
		}
		std::string current = std::to_string(high_scores[i]);
		int y_index = (0.5 + (0.05 * (1 + index)))  * nGameboard_height * nGrid_scale;
		verdana.drawString(current, 0.3 * ((nGameboard_width*nGrid_scale) + (boundary_scale*boundary_weight)), y_index);
		index++;
	}
}

void game::loadHighScores() {
	high_scores.clear();
	std::string line;
	std::ifstream file("bin/data/highscores.txt");

	if (file.is_open()) {
		while (getline(file, line)) {
			high_scores.push_back(std::stoi(line));
		}
		file.close();
	}
}
void game::saveHighScores() {

}

void game::updateHighScores() {
	std::sort(high_scores.begin(), high_scores.end());
	if (score_ > high_scores[0]) {
		high_scores[0] = score_;
		std::sort(high_scores.begin(), high_scores.end());
	}
}





