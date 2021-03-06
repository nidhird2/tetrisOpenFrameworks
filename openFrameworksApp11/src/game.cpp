#include "game.h"
#include <array>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

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

/**
 * Loads all sounds and fonts. Sets the background music in a loop. Also sets the locations for the pause, directions,
 * restart, and exits positions (These positions are based off boundary and grid sizes).
 */
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
	//backgroundMusic.play();
	pauseButton.set(1.3 * ((nGameboard_width*nGrid_scale) + (boundary_scale*boundary_weight)),
		0.2 * nGameboard_height * nGrid_scale, 2 * nGrid_scale, nGrid_scale);
	directionsButton.set(1.3 * ((nGameboard_width*nGrid_scale) + (boundary_scale*boundary_weight)),
		0.3 * nGameboard_height * nGrid_scale, 2 * nGrid_scale, nGrid_scale);
	restartButton.set(.4 * ((nGameboard_width*nGrid_scale) + (boundary_scale*boundary_weight)),
		0.3 * nGameboard_height * nGrid_scale, 2 * nGrid_scale, nGrid_scale);
	exitButton.set(.4 * ((nGameboard_width*nGrid_scale) + (boundary_scale*boundary_weight)),
		0.4 * nGameboard_height * nGrid_scale, 2 * nGrid_scale, nGrid_scale);
}
/**
 * If the game is playing, it will force the current piece down after a small pause. It will also increase the speed if
 * the amount of pieces reaches a multiple of nPieceCount.
 */
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

/**
 * Draws the corresponding screen, based off the current stage of the game (beginning, paused, needs directions, game
 * over, or game in session.
 */
void game::draw() {
	ofSetBackgroundColor(ofColor::black);
	if (isGameOver) {
		drawGameOverScreen();
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
		drawGame();
	}
}
/**
 * Handles user input. If it is the beginning, then any key will trigger the game to start. Otherwise: right key will
 * move current tetromino right if possible, left key will move current left if possible, and up key will rotate if
 * possible. The down arrow key will move the piece down, if possible. If it is not possible, the piece will be added
 * to the board and a new piece will be generated. The space key will move the piece as far down as possible (a.k.a.
 * "hard drop"). If any other key is pressed during gameplay, nothing will happen.
 * @param key that was pressed by the user.
 */
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

/**
 *  Checks if the click was inside any of the buttons and takes the appropriate action. For pause and directions
 *  buttons, it will opposite its corresponding boolean. For restart, it will call the reset method, and for exit,
 *  it will first write all the high scores into a text file (see: saveHighScores()) and then exit the application.
 * @param x coordinate of the mouse at the click
 * @param y coordinate of the mouse at the click
 * @param button
 */
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
		saveHighScores();
		ofExit();
	}
}

/**
 * Loads the high scores from a local text file. The file must be located under bin/data and named "highscores".
 * If the file is anywhere else, please change the file location in the method.
 * This method reads in the (five) scores line by line and stores it in the local high_scores vector. If the file is
 * unable to be opened, the method will stores five zeroes in high_scores.
 */
void game::loadHighScores() {
	high_scores.clear();
	std::string line;
	std::ifstream high_score_file("bin/data/highscores.txt");

	if (high_score_file.is_open()) {
		while (getline(high_score_file, line)) {
			high_scores.push_back(std::stoi(line));
		}
		high_score_file.close();
	}
	else {
		high_scores = std::vector<int>(5, 0);
	}
}
/**
 * Saves high scores into the same text file that the scores were read from. Overwrites the current file and stores
 * the (five) scores line by line into the text file. If unable to locate the file, this method will do nothing.
 */
void game::saveHighScores() {
	ofstream high_score_file("bin/data/highscores.txt", std::ofstream::trunc);

	if (high_score_file.is_open()) {
		for (int i = 0; i < high_scores.size(); i++) {
			high_score_file << high_scores[i] << endl;
		}
	}
}
/**
 * Draws the high scores, from highest to lowest, onto the middle of the screen. It will first update the scores and
 * check if the current score qualifies. After, it will proceed to write a label ""high scores: " and then write the
 * top five scores, from lowest to highest, line-by-line. If the current score made the high score list, it will be
 * listed in red. Otherwise, all of the text will be in white.
 */
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

/**
 * Draws the game by drawing the game board, the current tetromino's location, its projection, the game boundary, game
 * information, and the pause and directions buttons.
 */
void game::drawGame() {
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
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

/**
 * Draws welcome screen. Welcomes the user to tetris and prompts the user to press any key to start the game. Each
 * letter in tetris are each written in a different color.
 */
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
	verdana.drawString("press any key to start...", 0.40 *((nGameboard_width*nGrid_scale)+(boundary_scale*boundary_weight)),
					   0.45 * nGameboard_height * nGrid_scale);

}

/**
 * Lets the user know the game is paused. This screen also includes the restart and exit buttons. The high scores are
 * also shown in this screen.
 */
void game::drawPauseScreen() {
	drawPauseButton();
	ofSetColor(ofColor::white);
	verdana.drawString("G A M E  P A U S E D", 0.25 * ((nGameboard_width*nGrid_scale)+(boundary_scale*boundary_weight)),
					   0.20 * nGameboard_height * nGrid_scale);
	drawRestartButton();
	drawExitButton();
	drawHighScores();
}
/**
 * Changes the background color, writes a small game objective and game controls to the screen. Includes the directions
 * button (must be pressed by the user to exit the screen).
 */
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
	verdana.drawString("up arrow key: rotates the piece if possible", 0, 0.45 * nGameboard_height * nGrid_scale);
	ofSetColor(ofColor::orange);
	verdana.drawString("left arrow key: shifts pieces left if possible",0, 0.50 * nGameboard_height * nGrid_scale);
	ofSetColor(ofColor::orchid);
	verdana.drawString("right arrow key: shifts piece right if possible", 0, 0.55 * nGameboard_height * nGrid_scale);
	ofSetColor(ofColor::darkGoldenRod);
	verdana.drawString("down arrow key: shifts piece down if possible", 0, 0.60 * nGameboard_height * nGrid_scale);
	ofSetColor(ofColor::darkMagenta);
	verdana.drawString("space bar: moves piece as far down as possible", 0, 0.65 * nGameboard_height * nGrid_scale);
}

/**
 * The game over screen notifies the user the game is over and their final score. It also includes a list of the high
 * scores, and the restart and exit buttons.
 */
void game::drawGameOverScreen() {
	ofSetColor(ofColor::white);
	verdana.drawString("G A M E  O V E R", 0.25 * ((nGameboard_width*nGrid_scale) + (boundary_scale*boundary_weight)),
					   0.20 * nGameboard_height * nGrid_scale);
	verdana.drawString("YOUR SCORE: "+ std::to_string(score_), 0.25 * ((nGameboard_width*nGrid_scale) + (boundary_scale*boundary_weight)),
					   0.25 * nGameboard_height * nGrid_scale);
	drawHighScores();
	drawRestartButton();
	drawExitButton();
}

/**
 * Draws the pauseButton in the location that was specified in the setUp method, also types a label for the button.
 */
void game::drawPauseButton() {
	ofSetColor(ofColor::magenta);
	ofRect(pauseButton);
	ofSetColor(ofColor::white);
	verdana.drawString("PAUSE", 1.3* ((nGameboard_width*nGrid_scale) + (boundary_scale*boundary_weight)) +
								(nGrid_scale / 2), (0.2 * nGameboard_height * nGrid_scale) + (nGrid_scale / 2));
}

/**
 * Draws the directionsButton in the location that was specified in the setUp method, also types a label ("HELP" or
 * "EXIT" ) for the button, based on whether or not the game is currently on the directions screen.
 */
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

/**
 * Draws the restartButton in the location that was specified in the setUp method, also types a label for the button.
 */
void game::drawRestartButton() {
	ofSetColor(ofColor::cornflowerBlue);
	ofRect(restartButton);
	ofSetColor(ofColor::white);
	verdana.drawString("RESTART", .4 * ((nGameboard_width*nGrid_scale) + (boundary_scale*boundary_weight)),
					   (0.3 * nGameboard_height * nGrid_scale) + (nGrid_scale / 2));
}

/**
 * Draws the exitButton in the location that was specified in the setUp method, also types a label for the button.
 */
void game::drawExitButton() {
	ofSetColor(ofColor::orangeRed);
	ofRect(exitButton);
	ofSetColor(ofColor::white);
	verdana.drawString("EXIT", .4 * ((nGameboard_width*nGrid_scale) + (boundary_scale*boundary_weight))
							   + (nGrid_scale / 2),(0.4 * nGameboard_height * nGrid_scale) + (nGrid_scale / 2));
}

/**
 * Draws the game board boundary by drawing 2 vertical and 1 horizontal lines. Boundary is calculated by the
 * boundary_weight, boundary_scale, and nGrid_scale.
 */
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

/**
 * Draws the amount of the lines cleared, the current score, and the upcoming tetromino piece to the screen.
 */
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

/**
 * Draws the hypothesized location of the current tetromino if the piece dropped all the way down to the bottom. The
 * "projection" is translucent so as to not confuse the user with the actual location of the piece.
 */
void game::drawProjection() {
	int x = xPos;
	int y = yPos;
	while (!checkIfAtBottom(x, y)) {
		y++;
	}
	current.drawTranslucent(x, y, nGrid_scale, boundary_scale *boundary_weight);

}

/**
 * Resets the game by creating a new board, new current/upcoming pieces, setting score/line_cleared to zero, and setting
 * all booleans to false. The only thing that is not reset is high_scores.
 */
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

/**
 * Checks if the current score qualifies for a high score, and changes and sorts the list appropriately.
 */
void game::updateHighScores() {
	std::sort(high_scores.begin(), high_scores.end());

	if (score_ > high_scores[0] && !(std::find(high_scores.begin(), high_scores.end(), score_) != high_scores.end())) {
		high_scores[0] = score_;
	}
	std::sort(high_scores.begin(), high_scores.end());
}

/**
 * Checks if game is over by seeing if there is a block in the topmost row of the game board.
 * @return whether or not game is finished
 */
bool game::checkIfGameOver() {
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

/**
 * Clears any full lines in the game board and shifts all rows down. Also updates the current score and lines cleared.
 * Score formula is in this method.
 */
void game::clearLines() {
	int number_cleared = 0;
	for (int j = nGameboard_height - 1; j >= 0; j--) {
		if (checkIfFullLine(j)) {
			number_cleared++;
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
	if (number_cleared >= 1) {
		score_ += number_cleared * number_cleared * nScore_multiplier;
	}
}

/**
 * Checks if at the given index, the row in the game board is full.
 * @param j_index of row to be checked
 * @return whether or not the row is full
 */
bool game::checkIfFullLine(int j_index) {
	for (int i = 0; i < nGameboard_width; i++) {
		if (board[i][j_index] == ofColor::white) {
			return false;
		}
	}
	return true;
}

/**
 * Tries to add current tetromino to the board. If piece is unable to be added, the method will set isGameOver to true
 * and exit, otherwise, it will add the colors of the tetromino into the board.
 */
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

/**
 * Check if the current tetromino, its xPos and yPos, are within the game board's left boundary if the piece were to be
 * move left.
 * @return whether or not piece the piece is in the game board's left boundary if moved left
 */
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

/**
 * Check if the current tetromino, its xPos and yPos, are within the game board's right boundary if the piece were to be
 * move right.
 * @return whether or not piece the piece is in the game board's right boundary if moved right
 */
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

/**
 * Checks if the current tetromino, at a specified coordinate, would be at the bottom most position possible the x
 * coordinate.
 * @param x coordinate of a coordinate
 * @param y coordinate of a coordinate
 * @return whether or not current is at the bottom at the given x and y
 */
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

/**
 * Checks if the current tetromino would overlap with another at a given location on the board.
 * @param x coordinate
 * @param y coordinate
 * @return whether or not there would be overlap at a location
 */
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

/**
 * Makes a new shape by setting current equal to upcoming, and setting upcoming to be a new tetromino. Also increments
 * nPieceCount and resets xPos and yPos.
 */
void game::makeNewShape() {
	nPieceCount++;
	current = upcoming;
	upcoming = tetromino();
	xPos = (nGameboard_width - nTetromino_size) / 2;
	yPos = 0 - (nTetromino_size / 2);
}





