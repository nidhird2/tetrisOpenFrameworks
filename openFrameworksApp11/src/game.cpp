#include "game.h"
#include <array>

game::game() {
	board = std::vector <std::vector <ofColor>>(nGameboard_width, std::vector <ofColor>(nGameboard_height));
	current = tetromino();
	lines_cleared = 0;
	score_ = 0;
	xPos = nGameboard_width/2;
	yPos = 0;
}

bool game::CheckIfCollision(int x, int y) {
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
	yPos++;
}

void game::MakeNewShape() {
	if (make_new_shape) {
		current = tetromino();
		xPos = nGameboard_width / 2;
		yPos = 0;
		make_new_shape = false;
	}
}

void game::KeyPressed(int key) {


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
}

void game::addCurrentToBoard() {
	Type shape = current.getShape();
	bool reference[4][4];
	int color_index = -1;
	switch (shape) {
	case(O_SHAPE):
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				reference[i][j] = o_positions[i][j];
			}
		}
		color_index = 0;
		break;
	case(I_SHAPE):
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				reference[i][j] = i_positions[current.getRotation()][i][j];
			}
		}
		color_index = 1;
		break;
	case(J_SHAPE):
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				reference[i][j] = j_positions[current.getRotation()][i][j];
			}
		}
		color_index = 2;
		break;
	case(L_SHAPE):
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				reference[i][j] = l_positions[current.getRotation()][i][j];
			}
		}
		color_index = 3;
		break;
	case(S_SHAPE):
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				reference[i][j] = s_positions[current.getRotation()][i][j];
			}
		}
		break;
		color_index = 4;
	case(Z_SHAPE):
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				reference[i][j] = z_positions[current.getRotation()][i][j];
			}
		}
		color_index = 5;
		break;
	default:
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				reference[i][j] = t_positions[current.getRotation()][i][j];
			}
		}
		color_index = 6;
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (reference[i][j] == true) {
				board[xPos + i][yPos + j] = colors[color_index];
			}
		}
	}
}
void canGoDown() {
}





