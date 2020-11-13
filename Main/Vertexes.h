#pragma once
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class vertex
{

public:
	float coord_x;
	float coord_y;

	vertex(float x, float y) {
		coord_x = x;
		coord_y = y;
	}

	float distanceTo(vertex point) {
		return sqrt((this->coord_x - point.coord_x)*(this->coord_x - point.coord_x) + (this->coord_y - point.coord_y)*(this->coord_y - point.coord_y));
	}

};