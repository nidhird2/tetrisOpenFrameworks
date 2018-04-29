#pragma once
#include "tetromino.h"
#include <cstdlib>
#include <vector>


tetromino::tetromino() {
	int random = rand() % 7;
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
void tetromino::draw(int xPos, int yPos, int grid_scale, int x_shift_val) {
	std::vector<std::vector<bool>> reference = getOrientation();
		for (int i = 0; i < nTetromino_size; i++) {
			for (int j = 0; j < nTetromino_size; j++) {
				if (reference[i][j] == true) {
					ofSetColor(colors[getColorIndex()]);
					ofDrawRectangle((xPos + i) * grid_scale + x_shift_val, (yPos + j) * grid_scale, grid_scale, grid_scale);
				}
			}
		}
}
void tetromino::rotate() {
	if (rotations == 0) {
		rotations = 3;
	}
	else {
		rotations--;
	}
}
std::vector<std::vector<bool>> tetromino::getOrientation() {
	std::vector<std::vector<bool>> reference(5, std::vector<bool>(5));
	switch (shape) {
	case(O_SHAPE):
		for (int i = 0; i < nTetromino_size; i++) {
			for (int j = 0; j < nTetromino_size; j++) {
				reference[i][j] = o_positions[i][j];
			}
		}
		break;
	case(I_SHAPE):
		for (int i = 0; i < nTetromino_size; i++) {
			for (int j = 0; j < nTetromino_size; j++) {
				reference[i][j] = i_positions[rotations][i][j];
			}
		}
		break;
	case(J_SHAPE):
		for (int i = 0; i < nTetromino_size; i++) {
			for (int j = 0; j < nTetromino_size; j++) {
				reference[i][j] = j_positions[rotations][i][j];
			}
		}
		break;
	case(L_SHAPE):
		for (int i = 0; i < nTetromino_size; i++) {
			for (int j = 0; j < nTetromino_size; j++) {
				reference[i][j] = l_positions[rotations][i][j];
			}
		}
		break;
	case(S_SHAPE):
		for (int i = 0; i < nTetromino_size; i++) {
			for (int j = 0; j < nTetromino_size; j++) {
				reference[i][j] = s_positions[rotations][i][j];
			}
		}
		break;
	case(Z_SHAPE):
		for (int i = 0; i < nTetromino_size; i++) {
			for (int j = 0; j < nTetromino_size; j++) {
				reference[i][j] = z_positions[rotations][i][j];
			}
		}
		break;
	default:
		for (int i = 0; i < nTetromino_size; i++) {
			for (int j = 0; j < nTetromino_size; j++) {
				reference[i][j] = t_positions[rotations][i][j];
			}
		}
	}
	return reference;
}
int tetromino::getColorIndex() {
	switch (shape) {
	case(O_SHAPE):
		return 0;
	case(I_SHAPE):
		return 1;
	case(J_SHAPE):
		return 2;
	case(L_SHAPE):
		return 3;
	case(S_SHAPE):
		return 4;
	case(Z_SHAPE):
		return 5;
	default:
		return 6;
	}
}




