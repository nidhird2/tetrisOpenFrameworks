#pragma once
#include "tetromino.h"
#include <cstdlib>


tetromino::tetromino() {
	int random = 2;
	switch (random) {
		case(0):
			shape = O_SHAPE;
			break;
		case(1): 
			shape = I_SHAPE;
			break;
		case(2):
			shape = J_SHAPE;
			break;
		case(3):
			shape = L_SHAPE;
			break;
		case(4): 
			shape = S_SHAPE;
			break;
		case(5): 
			shape = Z_SHAPE;
			break;
		default: 
			shape = T_SHAPE;
			break;
	}
	rotations = 1;
}

Type tetromino::getShape() {
	return shape;
}

int tetromino::getRotation() {
	return rotations;
}
void tetromino::draw(int xPos, int yPos, int grid_scale) {
	if (shape == O_SHAPE) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (o_positions[i][j] == true) {
					ofSetColor(colors[0]);
					ofDrawRectangle(grid_scale*(xPos + i), grid_scale*(yPos + j), grid_scale, grid_scale);
				}
			}
		}
	}
	else if (shape == I_SHAPE) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (i_positions[rotations][i][j] == true) {
					ofSetColor(colors[1]);
					ofDrawRectangle(grid_scale*(xPos + i), grid_scale*(yPos + j), grid_scale, grid_scale);
				}
			}
		}
	}
	else if (shape == J_SHAPE) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (j_positions[rotations][i][j] == true) {
					ofSetColor(colors[2]);
					ofDrawRectangle(grid_scale*(xPos + i), grid_scale*(yPos + j), grid_scale, grid_scale);
				}
			}
		}
	}
	else if (shape == L_SHAPE) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (l_positions[rotations][i][j] == true) {
					ofSetColor(colors[3]);
					ofDrawRectangle(grid_scale*(xPos + i), grid_scale*(yPos + j), grid_scale, grid_scale);
				}
			}
		}
	}
	else if (shape == S_SHAPE) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (s_positions[rotations][i][j] == true) {
					ofSetColor(colors[4]);
					ofDrawRectangle(grid_scale*(xPos + i), grid_scale*(yPos + j), grid_scale, grid_scale);
				}
			}
		}
	}
	else if (shape == Z_SHAPE) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (z_positions[rotations][i][j] == true) {
					ofSetColor(colors[5]);
					ofDrawRectangle(grid_scale*(xPos + i), grid_scale*(yPos + j), grid_scale, grid_scale);
				}
			}
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (t_positions[rotations][i][j] == true) {
					ofSetColor(colors[6]);
					ofDrawRectangle(grid_scale*(xPos + i), grid_scale*(yPos + j), grid_scale, grid_scale);
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



