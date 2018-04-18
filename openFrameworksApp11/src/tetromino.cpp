#include "ofMain.h"
#include "tetromino.h"
#include "gameboard.h"
#include <iostream>
#include <cstdlib>


tetromino::tetromino() {
	int random = rand() % 6 ;
	switch (random) {
	case(0): shape = I_SHAPE;
	case(1): shape = J_SHAPE;
	case(2): shape = L_SHAPE;
	case(3): shape = O_SHAPE;
	case(4): shape = S_SHAPE;
	case(5): shape = T_SHAPE;
	default: shape = S_SHAPE;
	}
	rotations = 1;
}

void tetromino::draw(int xPos, int yPos) {
	if (shape == O_SHAPE) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (o_positions[i][j] == true) {
					ofSetColor(0, 0, 255);
					ofDrawRectangle(xPos + GRID_SCALE * i, yPos + GRID_SCALE * j, GRID_SCALE, GRID_SCALE);
				}
			}
		}
	}
	else if (shape == I_SHAPE) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (i_positions[rotations][i][j] == true) {
					ofSetColor(0, 255, 0);
					ofDrawRectangle(xPos + GRID_SCALE * i, yPos + GRID_SCALE * j, GRID_SCALE, GRID_SCALE);
				}
			}
		}
	}
	else if (shape == J_SHAPE) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (j_positions[rotations][i][j] == true) {
					ofSetColor(255, 0, 0);
					ofDrawRectangle(xPos + (GRID_SCALE * i), yPos + (GRID_SCALE * j), GRID_SCALE, GRID_SCALE);
				}
			}
		}
	}
	else if (shape == L_SHAPE) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (l_positions[rotations][i][j] == true) {
					ofSetColor(100, 100, 100);
					ofDrawRectangle(xPos + GRID_SCALE * i, yPos + GRID_SCALE * j, GRID_SCALE, GRID_SCALE);
				}
			}
		}
	}
	else if (shape == S_SHAPE) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (s_positions[rotations][i][j] == true) {
					ofSetColor(255, 0, 255);
					ofDrawRectangle(xPos + GRID_SCALE * i, yPos + GRID_SCALE * j, GRID_SCALE, GRID_SCALE);
				}
			}
		}
	}
	else if (shape == Z_SHAPE) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (z_positions[rotations][i][j] == true) {
					ofSetColor(0, 0, 0);
					ofDrawRectangle(xPos + GRID_SCALE * i, yPos + GRID_SCALE * j, GRID_SCALE, GRID_SCALE);
				}
			}
		}
	}
	else {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (t_positions[rotations][i][j] == true) {
					ofSetColor(255, 255, 255);
					ofDrawRectangle(xPos + GRID_SCALE * i, yPos + GRID_SCALE * j, GRID_SCALE, GRID_SCALE);
				}
			}
		}
	}
}
void tetromino::rotate() {
	if (rotations == 3) {
		rotations = 0;
	}
	else {
		rotations++;
	}
}



