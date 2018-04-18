#pragma once
#include "vector"
class gameboard {
public:
	int const HEIGHT = 10;
	int const WIDTH = 10;
	std::vector < std::vector<bool>> board;
	std::vector< std::vector < int>> tetronimos;

	bool CheckIfCollision();
	
	



};