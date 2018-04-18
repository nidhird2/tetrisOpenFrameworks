#include "tetromino.h"
#include "ofMain.h"
#include <cstdlib>

tetromino::tetromino() {
	rotations = 0;
	int rando = rand() % 7;
	switch (rando) {
	case(0): shape = I_SHAPE;
	case(1): shape = J_SHAPE;
	case(2): shape = L_SHAPE;
	case(3): shape = O_SHAPE;
	case(4): shape = S_SHAPE;
	case(5): shape = T_SHAPE;
	default: shape = Z_SHAPE;
	}
	
}

void tetromino::draw(int xPos, int yPos) {
	if (shape == O_SHAPE) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				ofSetColor(200, 30, 30);
				ofDrawRectangle(100, 100, 10, 10);
			}
		}
	}

}



