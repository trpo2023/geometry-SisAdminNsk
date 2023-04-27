#pragma once
#include <string>
const int M_PI = 3.141592653589793238;

class CircleClass
{
private:
	float xCoord = 0;
	float yCoord = 0;
	float radious = 0;

public:
	float GetXcoord();
	float GetYcoord();
	float GetRadios();

	void SetXcoord(float x);
	void SetYcoord(float y);
	void SetRadious(float rad);

	std::string name = "";
	std::string intersections[10];

	float CalculatePerimeter(float r);
	float CalculateArea(float r);
};

