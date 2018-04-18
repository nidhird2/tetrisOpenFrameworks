#pragma once
#include "vector"
class gameboard {
public:
	std::vector < std::vector<bool>> board;
	std::vector< std::vector < int>> tetronimos;

	bool CheckIfCollision();
	
	



};
int const GRID_SCALE = 25;