#pragma once
#include <array>
#include "ofMain.h"
#include <iostream>
#include <cstdlib>
#include <vector>

enum Type
{
	I_SHAPE,
	J_SHAPE,
	L_SHAPE,
	O_SHAPE,
	S_SHAPE,
	T_SHAPE,
	Z_SHAPE
};

class tetromino {
	int rotations;
	Type shape;

public:
	
	tetromino();
	Type getShape();
	int getRotation();
	void draw(int xPos, int yPos, int grid_scale);
	void rotate();
};

const bool i_positions[4][4][4] = { { { 0, 0, 0, 0 },{ 1, 1, 1, 1 },{ 0, 0, 0, 0 },{ 0, 0, 0, 0 } },
{ { 0, 0, 1, 0 },{ 0, 0, 1, 0 },{ 0, 0, 1, 0 },{ 0, 0, 1, 0 } },
{ { 0, 0, 0, 0 },{ 0, 0, 0, 0 },{ 1, 1, 1, 1 },{ 0, 0, 0, 0 } },
{ { 0,1, 0, 0 },{ 0, 1, 0, 0 },{ 0, 1, 0, 0 },{ 0, 1, 0, 0 } } };

const bool j_positions[4][4][4] = { { { 1, 0, 0, 0 },{ 1, 1, 1, 0 },{ 0, 0, 0,0 },{0, 0, 0, 0}},
{ { 0, 0, 1, 1 },{ 0, 0, 1, 0 },{0, 0, 1, 0},{ 0, 0, 0, 0 } },
{ { 0, 0, 0, 0 }, {0, 0, 0, 0 },{ 0, 1, 1, 1 },{ 0, 0, 0, 1 } },
{ { 0, 0, 0, 0 }, { 0, 1, 0, 0 },{ 0, 1, 0,0 },{ 1, 1,0,0 } } };

const bool l_positions[4][4][4] = { { {0, 0, 1, 0 },{ 1, 1, 1 ,0 },{0, 0, 0, 0 },{ 0, 0, 0, 0 } },
{ {0, 0, 1, 0 },{0, 0, 1, 0 },{ 0, 0, 1, 1 },{ 0, 0, 0, 0 } },
{ { 0, 0, 0, 0 }, {0, 0, 0, 0 },{0, 1, 1, 1 },{0, 1, 0, 0 } },
{ { 0, 0, 0, 0 }, { 1, 1, 0 ,0},{ 0, 1, 0 ,0},{ 0, 1, 0,0 } } };

const bool o_positions[4][4] = { { 0, 0, 0, 0 },{ 0, 1, 1, 0 },{ 0, 1, 1, 0 },{ 0, 1, 1, 0 } };

const bool s_positions[4][4][4] = { { { 0, 1, 1, 0 },{ 1, 1, 0, 0 },{ 0, 0, 0, 0 },{ 0, 0, 0, 0 } },
{ {0, 0, 1, 0 },{0, 0, 1, 1 },{0, 0, 0, 1 },{ 0, 0, 0, 0 } },
{ {0, 0, 0, 0 }, {0, 0, 0, 0 },{0, 0, 1, 1 },{0, 1, 1, 0 } },
{ { 0, 0, 0, 0 }, { 1, 0, 0, 0 },{ 1, 1, 0,0 },{ 0, 1, 0,0 } } };

const bool t_positions[4][4][4] = { { { 0, 1, 0,0 },{ 1, 1, 1,0 },{ 0, 0, 0,0 },{ 0, 0, 0, 0 } },
{ {0, 0, 1, 0 },{0, 0, 1, 1 },{0, 0, 1, 0 },{ 0, 0, 0, 0 } },
{ { 0, 0, 0, 0 }, {0, 0, 0, 0 },{0, 1, 1, 1 },{0, 0, 1, 0 } },
{ { 0, 0, 0, 0 }, { 0, 1, 0,0 },{ 1, 1, 0,0 },{ 0, 1, 0,0 } } };

const bool z_positions[4][4][4] = { { { 1, 1, 0,0 },{ 0, 1, 1,0 },{ 0, 0, 0,0 },{ 0, 0, 0, 0 } },
{ {0, 0, 0, 1 },{0, 0, 1, 1 },{0, 0, 1, 0 },{ 0, 0, 0, 0 } },
{ { 0, 0, 0, 0 }, {0, 0, 0, 0 },{0, 1, 1, 0 },{0, 0, 1, 1 } },
{ { 0, 0, 0, 0}, { 0, 1, 0,0 },{ 1, 1, 0,0 },{ 1, 0, 0,0 } } };


const ofColor colors[7] = {ofColor(255,0,0), ofColor(0,255,0), ofColor(0,0,255), ofColor(255,150,50), ofColor(255,255,50), ofColor(255,0,255), ofColor(0,255,255) };

